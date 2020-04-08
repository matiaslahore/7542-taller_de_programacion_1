//
// Created by fede on 1/11/19.
//

#ifndef MAP_TRACKPARTDATA_H
#define MAP_TRACKPARTDATA_H

#include <string>

#ifndef MAP_TRACKTYPE
#define MAP_TRACKTYPE
typedef enum {
    empty,
    downRight,
    downLeft,
    upRight,
    upLeft,
    horizontal,
    vertical,
    finishH,
    finishV,
    public1Up,
    public1Down,
    public1Left,
    public1Right
} trackPartType;
#endif

class Track;

class TrackPartData {
private:
    trackPartType type = empty;
    int trackElemID = 0;
    int posX = 0;
    int posY = 0;

public:
    void loadType(trackPartType elem);
    void loadPos(int row, int col);
    void loadPosClient(int row, int col);
    trackPartType getType() const;
    int getPosX();
    int getPosY();
    void setID(int ID);
    int getID();
    std::string serialize();

    bool validateConnection(trackPartType previous);

    void setType(trackPartType t);
};


#endif //MAP_TRACKPARTDATA_H
