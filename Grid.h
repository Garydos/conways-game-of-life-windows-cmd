#ifndef GUARD_GRID_H
#define GUARD_GRID_H

#include "Tile.h"

#include <map>
#include <vector>
#include <iostream>

class Grid {
private:
    friend std::ostream& operator<<(std::ostream&, const Grid&);
    std::map<Tile, int> grid;
    int gridWidth;
    int gridHeight;
    int relativeX;
    int relativeY;

    void resetToDefault();
    void cleanGrid();
    void initNeighbors();
    void calcNeighbors();
    int numLiveNeighbors(const Tile&);
    std::vector<Tile> getDeadNeighbors(const Tile&);
    void advanceGridTurn();
public:
    Grid();
    Grid(const std::vector<Tile>&);

    void next();
    void addTiles(const std::vector<Tile>&);
    void setGridWidth(int);
    void setGridHeight(int);
    void setRelativeX(int);
    void setRelativeY(int);
};

std::ostream& operator<<(std::ostream&, const Grid&);

#endif // GUARD_GRID_H
