#ifndef GUARD_TILE_H
#define GUARD_TILE_H

#include "Point.h"
#include "State.h"

#include <iostream>

class Tile : public Point {
private:
    friend std::ostream& operator<<(std::ostream&, const Tile&);
    State state;

public:
    Tile() {}
    Tile(int x, int y, State state)
        : state(state) { setX(x); setY(y); }

    State getState() const;

    void setState(State);

    bool operator<(const Tile&) const;
};

std::ostream& operator<<(std::ostream&, const Tile&);

#endif // GUARD_TILE_H
