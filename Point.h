#ifndef GUARD_POINT_H
#define GUARD_POINT_H

#include <iostream>
#include <string>

class Point {
private:
    friend std::ostream& operator<<(std::ostream&, const Point&);
    int x;
    int y;

public:
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    int getX() const;
    int getY() const;

    void setX(int);
    void setY(int);

    bool isNeighbor(const Point&) const;
    bool operator<(const Point&) const;
    bool operator==(const Point&) const;

    //operator std::string();
};

std::ostream& operator<<(std::ostream&, const Point&);

#endif // GUARD_POINT_H
