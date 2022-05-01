#ifndef PROBLEM_H
#define PROBLEM_H
#include <stdlib.h>
#include <iostream>
#include <math.h>

int* moveUp(int state[3][3]); // swaps the 0 with the number above it
int* moveDown(int state[3][3]); // swaps the 0 with the number below it
int* moveRight(int state[3][3]); // swaps the 0 with the number to its right 
int* moveLeft(int state[3][3]); // swaps the 0 with the number to its left

class problem{
    public:
        int initialState[3][3];
        int goalState[3][3];
        problem();
        problem(int init[3][3]);

        void displayState(const int state[3][3]); // displays the the current state
        int findMisplacedTilesCNT(int state[3][3]); // returns the number of numbers in the state that are not in the correct place
        double findEuclideanDistance(int x, int y, int state[3][3]); // checks the number in position x,y and returns its euclidean distance to its goal location
        double findEuclideanDistanceHeuristic(int state[3][3]); // returns the sum of the euclidean distances of all the numbers in the state array

        typedef int* (*OperatorFunctions) (int state[3][3]); 
        int numOperators = 4; 
        OperatorFunctions Operators[4] = {moveRight, moveLeft, moveUp, moveDown}; // array of operators

};

#endif
