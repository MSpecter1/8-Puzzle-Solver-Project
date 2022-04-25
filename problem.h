#ifndef PROBLEM_H
#define PROBLEM_H
#include <iostream>
#include <stdlib.h>

using namespace std;

class problem{
    public:
        int initialState[3][3];
        int goalState[3][3];

        problem();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
};

#endif
