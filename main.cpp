/***|***|****|
Program: robot.cpp / robot.h
Course: Object Oriented Programming and Data Structures
Trimester: 2410
#include "robot.h"
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    simulateBattlefield("simulation.txt");
    return 0;
}
