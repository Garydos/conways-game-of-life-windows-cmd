#include "Point.h"
#include "Tile.h"
#include "Grid.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
    Tile t1(1, 0, Alive);
    Tile t2(2, 1, Alive);
    Tile t3(0, 2, Alive);
    Tile t4(1, 2, Alive);
    Tile t5(2, 2, Alive);

    vector<Tile> tileVec;
    tileVec.push_back(t1);
    tileVec.push_back(t2);
    tileVec.push_back(t3);
    tileVec.push_back(t4);
    tileVec.push_back(t5);

    Grid grid(tileVec);

    int waitingTurns = 15;
    int count = 0;
    while (1) {
        if (count >= waitingTurns) {
            count = 0;
            grid.addTiles(tileVec);
        }

        string temp;
        cout << grid << endl;
        //cout << "Enter something to continue" << endl;
        //cin >> temp;
        cout << endl << endl << endl;
        grid.next();
        count++;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system("cls");
    }
}
