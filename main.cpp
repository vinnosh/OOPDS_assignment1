/***|***|****|
Program: robot.cpp / robot.h
Course: Object Oriented Programming and Data Structures
Trimester: 2410
Name: Vinnosh Rau A/L Samudram , Suah Min Yew , Uzair Akhyar
ID: 1211108264 , 1221303768 , 1211102576
Lecture Section: TC4L
Tutorial Section: TT7L
Email: 1211108264@soffice.mmu.edu.my , 1221303768@soffice.mmu.edu.my , 1211102576@soffice.mmu.edu.my
Phone: 012-2185040 , 011-23637292 , 010-3644346
***|***|****/
#include "robot.h"
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    simulateBattlefield("simulation.txt");
    return 0;
}
