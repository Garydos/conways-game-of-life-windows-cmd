#include "Tile.h"

State Tile::getState() const {
    return state;
}

void Tile::setState(State state) {
    this->state = state;
}

bool Tile::operator<(const Tile& t) const {
    if (state == t.state) {
        return (Point)(*this) < t;
    }
    return state < t.state;
}

std::ostream& operator<<(std::ostream& out, const Tile& t) {
    out << "{ " << t.getX() << " , " << t.getY() << " , "
        << ((bool)t.state ? "Alive" : "Dead") << " }";
}
