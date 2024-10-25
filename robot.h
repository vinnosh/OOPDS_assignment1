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
#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <list>

using namespace std;

class Robot {
protected:
    int posX;
    int posY;
    int kills;
    int lives;
    string name;

public:
    Robot(int x, int y, string n);
    virtual ~Robot() {}

    int getX() const;
    int getY() const;
    int getKills() const;
    int getLives() const;
    string getName() const;

    void addKill();
    void loseLife();

    virtual string getType() const = 0;
    virtual void move() = 0;
    virtual void fire(list<Robot*>& robots) = 0;
    virtual void look(list<Robot*>& robots) = 0;

    void move(int x, int y);
};

class Robocop : virtual public Robot {
public:
    Robocop(int x, int y, string n);
    string getType() const override;
    void move() override;
    void fire(list<Robot*>& robots) override;
    void look(list<Robot*>& robots) override;
};

class BlueThunder : public Robot {
public:
    BlueThunder(int x, int y, string n);
    string getType() const override;
    void fire(list<Robot*>& robots) override;
    void move() override;
    void look(list<Robot*>& robots) override;
};

class Terminator : virtual public Robot {
public:
    Terminator(int x, int y, string n);
    string getType() const override;
    void move() override;
    void fire(list<Robot*>& robots) override;
    void look(list<Robot*>& robots) override;
};

class Madbot : public Robot {
public:
    Madbot(int x, int y, string n);
    string getType() const override;
    void move() override;
    void fire(list<Robot*>& robots) override;
    void look(list<Robot*>& robots) override;
};

class RoboTank : public Robot {
public:
    RoboTank(int x, int y, string n);
    string getType() const override;
    void move() override;
    void fire(list<Robot*>& robots) override;
    void look(list<Robot*>& robots) override;
};

class UltimateRobot : public Robot {
public:
    UltimateRobot(int x, int y, string n);
    string getType() const override;
    void move() override;
    void fire(list<Robot*>& robots) override;
    void look(list<Robot*>& robots) override;
};

class TerminatorRoboCop : public Robocop, public Terminator {
public:
    TerminatorRoboCop(int x, int y, string n);
    string getType() const override;
    void move() override;
    void fire(list<Robot*>& robots) override;
    void look(list<Robot*>& robots) override;
};

void readRobotDetails(const string& line, string& robotType, string& robotName);
void printBattlefield(int M, int N, const list<Robot*>& robots);
void simulateSteps(int steps, int M, int N, list<Robot*>& robots, queue<Robot*>& robotQueue);
void simulateBattlefield(const string& inputFilename);

#endif
