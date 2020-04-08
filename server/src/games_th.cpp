//
// Created by fperezboco on 17/11/19.
//

#include "../include/games_th.h"
#include "../include/model/micromachines_th.h"
#include "../include/game_loop_th.h"
#include "../../common/include/lock.h"
#include <unistd.h>

#define PLAYERTOASSIGN -1
#define PLAYERBEINGASSIGNED -2
#define REFRESHPLAYERSTIME 200000  // us
#define LAPS_CONFIG "laps"

void GamesTh::run() {
    while (running) {
        mapNewClients();
        usleep(REFRESHPLAYERSTIME);
        deleteMapperThreads();
        stopGameIfAllEnded();
        gameEndedPlayersToMainMenu();
        joinEndedGames();
    }
}

// process new player create/join in new thread
void GamesTh::mapNewClients() {
    int i = 0;
    Lock l(m);

    for (auto & newPlayer : players) {
        if (newPlayer.second == PLAYERTOASSIGN) {
            newPlayer.second = PLAYERBEINGASSIGNED;
            std::thread * th;
            mapperThreadList.emplace(i, false);
            th = new std::thread(&GamesTh::processPlayer,
                                 this,
                                 newPlayer.first,
                                 std::ref(mapperThreadList.at(i)));
            mapperThreads.emplace(i, th);
            i++;
        }
    }
}

// joins mapper thread if finished
void GamesTh::deleteMapperThreads() {
    Lock l(m);

    auto it2 = mapperThreads.begin();
    for (auto it1 = mapperThreadList.begin(); it1 != mapperThreadList.end();) {
        if (it1->second){
            (it2->second)->join();
            delete it2->second;
            mapperThreads.erase(it2++);
            mapperThreadList.erase(it1++);
        } else {
            ++it1, ++it2;
        }
    }
}

void GamesTh::stopAllThreads() {
    Lock l(m);
    
    for (auto game : games) {
        game.second->stop();
        game.second->join();
        game.second->cleanPlayers();
    }
    games.clear();

    for (auto gameLoop : gameLoops) {
        gameLoop.second->stop();
        gameLoop.second->join();
    }
    gameLoops.clear();

    players.clear();

    for (auto mapperThread : mapperThreads) {
        mapperThread.second->join();
    }
    mapperThreads.clear();
}

void GamesTh::stop() {
    running = false;
    stopAllThreads();
}

// decides if creates or joins
void GamesTh::processPlayer(ClientTh * player, bool & finished) {
    TrackList tracks;
    tracks.readTracks();
    bool selected = false;
    while (!selected) {
        while (player->getState() == mainMenu) {
            printf("menu\n");
            player->sendAllTrackNames(tracks.serialize());
            player->setAvailableGames(serializeGames());
            player->sendAvailableGames();
            player->setPlayerMode();
            usleep(REFRESHPLAYERSTIME);
        }
        player->sendGameState(player->getState());
        selected = player->receiveMatchSelection();
    }
    if (!player->stillTalking()) return;
    player->setPlayerMode(); //actualizo el player mode, por si cambiaron de create a join o al reves
    if (player->getState() == creating) {
        printf("create\n");
        createGame(player);
        finished = true;
    } else if (player->getState() == joining) {
        printf("join\n");
        addPlayer(player);
        finished = true;
    }
}

// Creates new game and adds player to it
void GamesTh::createGame(ClientTh * player) {
    auto * game = new MicroMachinesTh(config);
    auto * gameLoop = new GameLoopTh(*game);
    player->setMatch();
    player->sendModifiers(game->modifiersSerialized());
    game->addPlayer(player);

    gamesNumber++;
    players[player] = gamesNumber;
    player->setState(waitingPlayers);
    game->setTrack(player->getTrackSelected());
    game->setTotalNumberPlayers(player->getNumberPlayersSelected());
    game->createCars();
    player->setCar(game->getNextCar());
    player->sendCarData();
    player->sendLapsData(config.getAsString(LAPS_CONFIG));

    games.emplace(gamesNumber, game);
    gameLoops.emplace(gamesNumber, gameLoop);
    games[gamesNumber]->start();
    gameLoops[gamesNumber]->start();
}

// Adds player to existent match. Receives match sent by user in setMatch()
void GamesTh::addPlayer(ClientTh *player) {
    player->setMatch();
    int gameIndex = player->getGameNumber();
    player->setCar(games[gameIndex]->getNextCar());
    games[gameIndex]->addPlayer(player);
    players[player] = gameIndex;
    player->sendTrackData(games[gameIndex]->trackSerialized());
    player->sendModifiers(games[gameIndex]->modifiersSerialized());
    player->sendCarData();
    player->sendLapsData(config.getAsString(LAPS_CONFIG));
    player->setState(waitingPlayers);
}

// Sends available games
std::string GamesTh::serializeGames() {
    std::string gamesStr = "N,";
    for (auto game : games) {
        if (game.second->isAnAvailableMatch())
            gamesStr += std::to_string(game.first) + ",";
    }

    if (!gamesStr.empty()) {
        gamesStr.back() = '\n';
    }
    return gamesStr;
}

// Adds player sent by acceptorThread to a list for processing it.
void GamesTh::setPlayerToAssign(ClientTh * player) {
    players.emplace(player, PLAYERTOASSIGN);
}

void GamesTh::removePlayer(ClientTh *player) {
    auto gameIt = games.find(players[player]);
    if (gameIt != games.end()) {
        gameIt->second->removePlayer(player);
    }
    players.erase(player);
}

// If all players are in WaitingEnd state stops game
void GamesTh::stopGameIfAllEnded() {
    Lock l(m);
    for (auto & game : games) {
        if (game.second->allPlayersWaitingEnd()) {
            usleep(PODIUMVIEWTIME); // Duermo para visualizar el podio
            game.second->setAllPlayersGameStates(gameEnded);
        }
    }
}

// Checks if any player ended and resets it to main menu.
void GamesTh::gameEndedPlayersToMainMenu() {
    Lock l(m);
    for (auto & player : players) {
        if (player.first->getState() == gameEnded) {
            player.first->clean();
            player.first->sendGameState(mainMenu);
            player.second = PLAYERTOASSIGN;
        }
    }
}

void GamesTh::joinEndedGames() {
    Lock l(m);

    for (auto loop = gameLoops.begin(); loop != gameLoops.end();) {
        if (!(loop->second->isRunning())) {
            int aux = loop->first;
            games[aux]->stop();
            loop->second->join();
            games[aux]->join();
            gameLoops.erase(loop++);
            games.erase(aux);
        } else {
            loop++;
        }
    }
}