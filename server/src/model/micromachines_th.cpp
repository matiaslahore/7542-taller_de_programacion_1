#include "../../include/model/micromachines_th.h"
#include "../../../common/include/lock.h"
#include "../../../common/include/socket_error.h"
#include "../../include/model/cars/car.h"
#include <Box2D/Box2D.h>
#include <unistd.h>

#define DEGTORAD 0.0174532925199432957f
#define SPEED_REDUCTION_FACTOR 0.9
#define SPEED_STOP 0.1
#define SPEED_INCREASE_FACTOR 2
#define SPEED_BOOST_TICKS 50
#define REFRESHTIME 5000000  // us
#define MAX_MODIFIERS_THROWN 30
#define HEALTH_GIFT 25
#define ROCK_HEALTH_REDUCTION 75
#define LAPS_CONFIG "laps"

MicroMachinesTh::MicroMachinesTh(Config &config) : config(config) {
    tracks.readTracks();
    world = new b2World(b2Vec2(0, 0));
    world->SetDestructionListener(&destruction_listener);
    modifierTypes = {"healthBox", "boost", "stones", "oil", "mud"};
    this->laps = config.getAsInt(LAPS_CONFIG) + 1;
}

void MicroMachinesTh::setTrack(std::string trackStr) {
    track = tracks.getTrack(trackStr);
}

void MicroMachinesTh::createCars() {
    //Agrego todos los autos disponibles en un mapa de autos
    cars[blue] = Car::createRedCar(world,
                                    getStartingPoint(0),
                                    getStartingCarRot(0),
                                    getStartID(0), config);
    cars[white] = Car::createYellowCar(world,
                                      getStartingPoint(1),
                                      getStartingCarRot(1),
                                      getStartID(1), config);
    if (numberPlayers > 2)
        cars[black] = Car::createWhiteCar(world,
                                      getStartingPoint(2),
                                      getStartingCarRot(2),
                                      getStartID(2), config);
    if (numberPlayers > 3)
        cars[yellow] = Car::createBlackCar(world,
                                        getStartingPoint(3),
                                        getStartingCarRot(3),
                                        getStartID(3), config);
    if (numberPlayers > 4)
        cars[red] = Car::createBlueCar(world,
                                  getStartingPoint(4),
                                  getStartingCarRot(4),
                                  getStartID(4), config);
    itCar = cars.begin();
}

void MicroMachinesTh::run() {
    while(running) {
        usleep(REFRESHTIME);
    }
}

void MicroMachinesTh::stop() {
    running = false;
}

void MicroMachinesTh::update() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->updateCar();
    }
}

Car * MicroMachinesTh::getNextCar() {
    Car * car = itCar->second;
    ++itCar;
    return car;
}

void MicroMachinesTh::addPlayer(ClientTh *client) {
    Lock l(m);
    players.push_back(client);
}

std::string MicroMachinesTh::trackSerialized() {
    return track.serialize();
}

void MicroMachinesTh::removePlayer(ClientTh *client) {
    Lock l(m);
    removePlayerFromVector(client);
}

void MicroMachinesTh::removePlayerFromVector(ClientTh *player) {
    int index_to_remove = -1;

    for (size_t i = 0; i < players.size(); i++) {
        if (players[i] == player) {
            index_to_remove = i;
            break;
        }
    }
    if (index_to_remove != -1) {
        players.erase(players.begin() + index_to_remove);
    }
}

int MicroMachinesTh::getPlayersNumber() {
    Lock l(m);
    return players.size();
}

void MicroMachinesTh::setAllPlayersGameStates(GameState state) {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->setState(state);
    }
}

void MicroMachinesTh::updatePlayersState() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->processNextAction();
        int x = players[i]->getCarPosX();
        int y = players[i]->getCarPosY();
        if (!track.isOnTrack(x, y))
            players[i]->modifySpeedByFactor(SPEED_REDUCTION_FACTOR);
        if (modifiers.isOnBoost(x, y)) {
            players[i]->setBoost(SPEED_BOOST_TICKS);
            players[i]->modifySpeedByFactor(SPEED_INCREASE_FACTOR);
            modifiersThrown--;
        }
        if (players[i]->getBoost() > 0) {
            players[i]->modifySpeedByFactor(SPEED_INCREASE_FACTOR);
        }
        if (modifiers.isOnHealth(x, y)) {
            players[i]->giftHealth(HEALTH_GIFT);
            modifiersThrown--;
        }
        if (modifiers.isOnMud(x, y)) {
            players[i]->modifySpeedByFactor(SPEED_STOP);
            modifiersThrown--;
        }
        if (modifiers.isOnOil(x, y)) {
            players[i]->modifySpeedByFactor(SPEED_STOP);
            modifiersThrown--;
        }
        if (modifiers.isOnStones(x, y)) {
            players[i]->modifySpeedByFactor(SPEED_STOP);
            players[i]->reduceHealth(ROCK_HEALTH_REDUCTION);
            modifiersThrown--;
        }
        if(players[i]->getState() == playing && players[i]->updateHealth()) {
            int ID = players[i]->getCarLastTrackID();
            Point newPos(track.getTrackPartPoint(ID));
            newPos = newPos + Point(BLOCKSIZE/2,BLOCKSIZE*(1.1));
            players[i]->newCarPosition(newPos);
        }
    }
}

// Checks if cars jump track parts and updates laps
void MicroMachinesTh::monitorTrack() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        int x = players[i]->getCarPosX();
        int y = players[i]->getCarPosY();
        int lastID = players[i]->getCarLastTrackID();
        int currentID = track.getTrackPart(x, y).getID();
        if (currentID == lastID || !track.isOnTrack(x,y)) {
            // sigue en el mismo o está fuera de pista
        } else if (track.jumpedTrackPart(x, y, lastID)) {
            // está en pista y salteó pedazos
            players[i]->newCarPosition(track.getTrackPartPoint(lastID) +
                        Point(BLOCKSIZE/2,BLOCKSIZE*(1.1)));
            players[i]->updateLastTrackID(lastID);
        } else {
            // avanzó al siguiente
            if (currentID == 0 && lastID == track.getPartsNumber() - 1) {
                players[i]->updateLaps();
            }
            players[i]->updateLastTrackID(currentID);
        }
    }
}

void MicroMachinesTh::updateWinners() {
    for (auto & player : players) {
        //Si alcanzó la cantidad de vueltas y no contiene el elemento, le cambio el estado y agrego a los ganadores
        std::string color = player->carColor();
        if (player->getLaps() == laps &&
        (std::find(winners.begin(), winners.end(), color) == winners.end())) {
            player->setState(waitingEnd);
            player->sendGameState(waitingEnd);
            winners.push_back(color);
        }
        player->setWinners(winners);
    }
}

void MicroMachinesTh::sendWinners() {
    //Mando los ganadores cuando termine la carrera
    for (auto & player : players) {
        if (player->getState() == waitingEnd || player->getState() == gameEnded) {
            player->sendWinners();
        }
    }
}

void MicroMachinesTh::cleanPlayers() {
    Lock l(m);
    players.clear();
}

void MicroMachinesTh::changeCarState(char *new_command) {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++)
        for (int j = 0; j < 10; ++j)
            players[i]->receiveActionPlugin(new_command);
}

void MicroMachinesTh::sendNewStateToPlayers() {
    Lock l(m);
    for (size_t i = 0; i < players.size(); i++) {
        players[i]->sendAllCarsToPlayer(players);
    }
}

void MicroMachinesTh::sendModifiersToPlayers() {
    Lock l(m);
    if (track.hasGrandstands()) {
        for (size_t i = 0; i < players.size(); i++) {
            players[i]->sendModifiers(modifiersSerialized());
        }
    }
}

Point MicroMachinesTh::getStartingPoint(int position) {
    return track.getCarStartingPos(position);
}

int MicroMachinesTh::getStartID(int order) {
    return track.getStartingID(order);
}

uint16_t MicroMachinesTh::getStartingCarRot(int position) {
    return track.getCarStartingRotation(position);
}

bool MicroMachinesTh::somePlayersInMainMenu() {
    for (auto & player : players) {
        if (player->getState() == mainMenu) {
            return true;
        }
    }
    return false;
}

bool MicroMachinesTh::allPlayersWaitingEnd() {
    for (auto & player : players) {
        if (player->getState() != waitingEnd) {
            return false;
        }
    }
    return true;
}

bool MicroMachinesTh::allPlayersGameEnded() {
    for (auto & player : players) {
        if (player->getState() != gameEnded) {
            return false;
        }
    }
    return true;
}

std::string MicroMachinesTh::modifiersSerialized() {
    return modifiers.serialize();
}

void MicroMachinesTh::throwModifier() {
    Lock l(m);
    if (modifiersThrown < MAX_MODIFIERS_THROWN && track.hasGrandstands()) {
        Grandstand gs = track.getRandomGrandstand();
        direction dir = setModifierDirection(gs.getType());
        int x = gs.getPosX() + BLOCKSIZE/2;
        int y = gs.getPosY() + BLOCKSIZE/2;
        modifiers.append(x, y, modifierTypes[rand() % modifierTypes.size()], dir);
        modifiersThrown++;
    }
}

void MicroMachinesTh::updateModifiersPosition() {
    Lock l(m);
    modifiers.updateDistance();
}

direction MicroMachinesTh::setModifierDirection(trackPartType type) {
    if (type == public1Up) return down;
    if (type == public1Down) return up;
    if (type == public1Left) return right;
    if (type == public1Right) return left;
    return down;
}

Config MicroMachinesTh::getConfig() {
    return config;
}

bool MicroMachinesTh::isAnAvailableMatch() {
    for (auto & player : players) {
        if (player->getState() != waitingPlayers) {
            return false;
        }
    }
    return true;
}

void MicroMachinesTh::setTotalNumberPlayers(int number) {
    numberPlayers = number;
}

int MicroMachinesTh::getTotalNumberPlayers() {
    Lock l(m);
    return numberPlayers;
}
