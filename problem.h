#ifndef PROBLEM_H
#define PROBLEM_H
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

int t1(int state);
int t2(int state);

int* moveUp(int state[3][3]);
int* moveDown(int state[3][3]);
int* moveRight(int state[3][3]);
int* moveLeft(int state[3][3]);

class problem{
    public:
        int initialState[3][3];
        int goalState[3][3];
        problem();
        problem(int init[3][3]);

        void displayState(const int state[3][3]);
        int findMisplacedTilesCNT(int state[3][3]);
        double findEuclideanDistance(int x, int y, int state[3][3]);
        double findEuclideanDistanceHeuristic(int state[3][3]);

        //TEST
        int init = 0;
        int goal = 10;
        int test1(int state){if (state<goal){return state+1;} else return state;}
        int test2(int state){if (state<goal){return state*2;} else return state;}
        
        typedef int (*OperatorTestFunctions) (int state);
        int numTestOperators = 2;
        OperatorTestFunctions TestOperators[2] = {t1, t2};
        //

        typedef int* (*OperatorFunctions) (int state[3][3]);
        int numOperators = 4;
        OperatorFunctions Operators[4] = {moveRight, moveLeft, moveUp, moveDown};

};

#endif
