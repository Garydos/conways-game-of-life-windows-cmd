#include "Point.h"

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int x) {
    this->x = x;
}

void Point::setY(int y) {
    this->y = y;
}


bool Point::isNeighbor(const Point& p) const {
    int relativeX = p.x - x;
    int relativeY = p.y - y;

    if (relativeX <= 1 && relativeX >= -1
        && relativeY <= 1 && relativeY >= -1
        && !(relativeX == 0 && relativeY == 0)) {
        return true;
    }
    return false;
}

bool Point::operator<(const Point& p) const {
    if (y == p.y){
        return x < p.x;
    }
    return y < p.y;
}

bool Point::operator==(const Point& p) const {
    return y == p.y && x == p.x;
}

std::ostream& operator<<(std::ostream& stream, const Point& p) {
    return stream << "{ " << p.x << " , " << p.y << " }";
}

//Point::operator std::string() {
//    std::string temp ="{ ";
//    temp += std::to_string(x);
//    temp += " , ";
//    temp += std::to_string(y);
//    temp += " }";
//    return temp;
//}
