//
// Created by fede on 1/11/19.
//

#include "../include/Track.h"
#include "../include/TrackPartData.h"

// Loads type of element
void TrackPartData::loadType(trackPartType elem) {
    type = elem;
}

/* Loads into cardinal meters.
 * Display coordinates: (0,0) starts
 * in top-left corner.
 * Cardinal coordinates: (0,0) starts
 * in bottom-left corner.*/
void TrackPartData::loadPos(int row, int col) {
    posX = col*BLOCKSIZE;
    posY = (row - 1)*BLOCKSIZE;  //-1 for "display coordinates"
}

void TrackPartData::loadPosClient(int row, int col) {
    posX = row; //al cliente ya le llega la fila y columna en metros
    posY = col;
}

// Returns track element type
trackPartType TrackPartData::getType() const{
    return type;
}

// Gets left corner position of track element in meters
int TrackPartData::getPosX() {
    return posX;
}

// Gets bottom corner position of track element in meters
int TrackPartData::getPosY() {
    return posY;
}

// Sets ID to recognize track elements traverse order
void TrackPartData::setID(int ID) {
    trackElemID = ID;
}

int TrackPartData::getID() {
    return trackElemID;
}

/* Converts part to string for serialization */
std::string TrackPartData::serialize() {
    return std::to_string(posX) +
           "," +
           std::to_string(posY) +
           "," +
           std::to_string(type);
}

void TrackPartData::setType(trackPartType t) {
    type = t;
}