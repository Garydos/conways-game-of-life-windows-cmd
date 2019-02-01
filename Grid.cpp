#include "Grid.h"
#include "Point.h"

#include <vector>
#include <map>
#include <iostream>

using std::vector;
using std::map;
using std::cout;
using std::endl;

typedef vector<Tile>::const_iterator cVecIter;
typedef vector<Tile>::const_iterator vecIter;
typedef map<Tile, int>::const_iterator cMapIter;
typedef map<Tile, int>::iterator mapIter;

void Grid::resetToDefault() {
    gridWidth = 20;
    gridHeight = 20;
    relativeX = -5;
    relativeY = -5;
}

Grid::Grid() {
    resetToDefault();
}

Grid::Grid(const vector<Tile>& tiles) {
    resetToDefault();
    addTiles(tiles);

//    for (cVecIter i = tiles.begin(); i != tiles.end(); i++) {
//        grid[*i] = 0;
//    }
//    cleanGrid();
//    initNeighbors();
}

void Grid::cleanGrid() {
    cMapIter i = grid.begin();
    while (i != grid.end()) {
        if (!(i->first.getState())) {
            grid.erase(i);
            i = grid.begin();
        }
        else {
            i++;
        }
    }
}

int Grid::numLiveNeighbors(const Tile& t) {
    int liveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                Tile tempTile(t.getX() + i,
                              t.getY() + j,
                              Alive);
                mapIter isInGrid = grid.find(tempTile);
                if (isInGrid != grid.end()) {
                    liveNeighbors++;
                }
            }
        }
    }
    return liveNeighbors;
}

void Grid::initNeighbors() {
    for (mapIter i = grid.begin(); i != grid.end(); i++) {
        i->second = 0;
        Point iPoint = (Point)i->first;
        for (cMapIter j = grid.begin(); j != grid.end(); j++) {
            if (iPoint.isNeighbor((Point)j->first)) {
                i->second++;
            }
        }
    }
}

vector<Tile> Grid::getDeadNeighbors(const Tile& t) {
    vector<Tile> ret;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                Tile tempTile(t.getX() + i,
                              t.getY() + j,
                              Alive);
                mapIter isInGrid = grid.find(tempTile);
                if (isInGrid == grid.end()) {
                    tempTile.setState(Dead);
                    ret.push_back(tempTile);
                }
            }
        }
    }
    return ret;
}

void Grid::calcNeighbors() {
    map<Tile, int> deadTiles;
    for (mapIter tile = grid.begin(); tile != grid.end(); tile++) {
        tile->second = numLiveNeighbors(tile->first);
        vector<Tile> deadNeighbors = getDeadNeighbors(tile->first);
        for (vecIter dead = deadNeighbors.begin();
            dead != deadNeighbors.end(); dead++) {
            deadTiles[*dead] = numLiveNeighbors(*dead);
        }
    }

    for (mapIter i = deadTiles.begin(); i != deadTiles.end(); i++) {
        grid[i->first] = i->second;
    }
}

void Grid::advanceGridTurn() {
    vector<Tile> deadTiles;
    vector<Tile> aliveTiles;

    mapIter i = grid.begin();
    while (i != grid.end()) {
        if (i->first.getState()) {
            if (i->second < 2 || i->second > 3) {
                Tile temp = i->first;
                grid.erase(temp);
                temp.setState(Dead);
                deadTiles.push_back(temp);

                i = grid.begin();
            }
            else {
                i++;
            }
        }
        else {
            if (i->second == 3) {
                Tile temp = i->first;
                grid.erase(temp);
                temp.setState(Alive);
                aliveTiles.push_back(temp);

                i = grid.begin();
            }
            else {
                i++;
            }
        }
    }

    for (vecIter i = aliveTiles.begin(); i != aliveTiles.end(); i++) {
        grid[*i] = numLiveNeighbors(*i);
    }
}

void Grid::next() {
    calcNeighbors();
    advanceGridTurn();
    cleanGrid();
    initNeighbors();
}

void Grid::addTiles(const vector<Tile>& tiles) {
    for (cVecIter i = tiles.begin(); i != tiles.end(); i++) {
        grid[*i] = 0;
    }
    cleanGrid();
    initNeighbors();
}

void Grid::setGridWidth(int width) {
    gridWidth = width;
}
void Grid::setGridHeight(int height) {
    gridHeight = height;
}
void Grid::setRelativeX(int x) {
    relativeX = x;
}
void Grid::setRelativeY(int y) {
    relativeY = y;
}

std::ostream& operator<<(std::ostream& out, const Grid& grd) {
//    for (cMapIter i = grd.grid.begin(); i != grd.grid.end(); i++) {
//        i++;
//        if (i != grd.grid.end()) {
//            i--;
//            out << i->first << " : " << i->second << endl;
//        }
//        else {
//            i--;
//            out << i->first << " : " << i->second;
//        }
//    }
//    return out;
    char drawGrid[grd.gridHeight][grd.gridWidth];
    for (int j = 0; j < grd.gridHeight; j++) {
        for (int i = 0; i < grd.gridWidth; i++) {
            drawGrid[j][i] = '-';
        }
    }

    for (cMapIter i = grd.grid.begin(); i != grd.grid.end(); i++) {
        int relativeX = i->first.getX() - grd.relativeX;
        int relativeY = i->first.getY() - grd.relativeY;

        if (relativeX >= 0 && relativeX < grd.gridWidth
            && relativeY >= 0 && relativeY < grd.gridHeight) {
            drawGrid[relativeY][relativeX] = '0';
        }
    }

    for (int j = 0; j < grd.gridHeight; j++) {
        for (int i = 0; i < grd.gridWidth; i++) {
            out << drawGrid[j][i];
        }
        if (j + 1< grd.gridHeight) {
            out << endl;
        }
    }

    return out;
}
