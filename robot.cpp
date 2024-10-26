/***|***|****|
Program: robot.cpp / robot.h
Course: Object Oriented Programming and Data Structures
Trimester: 2410
***|***|****/
#include "robot.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <queue>
#include <set>
#include <list>

Robot::Robot(int x, int y, string n) : posX(x), posY(y), kills(0), lives(3), name(n) {}

int Robot::getX() const { return posX; }
int Robot::getY() const { return posY; }
int Robot::getKills() const { return kills; }
int Robot::getLives() const { return lives; }
string Robot::getName() const { return name; }

void Robot::addKill() { kills++; }
void Robot::loseLife() { lives--; }

void Robot::move(int x, int y) {
    posX = x;
    posY = y;
}

Robocop::Robocop(int x, int y, string n) : Robot(x, y, n) {
    std::cout << "RoboCop " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string Robocop::getType() const { return "RoboCop"; }

void Robocop::move() {
    posX = rand() % 8 + 1;
    posY = rand() % 8 + 1;
    std::cout << "RoboCop moved to (" << posX << ", " << posY << ")" << std::endl;
}

void Robocop::fire(list<Robot*>& robots) {
    std::cout << "RoboCop at (" << posX << ", " << posY << ") fires:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        int randX = rand() % 8 + 1;
        int randY = rand() % 8 + 1;
        if (randX == posX && randY == posY) {
            std::cout << " - fires at (" << randX << ", " << randY << ")";
            std::cout << " - RoboCop cannot commit suicide!" << std::endl;
        } else {
            std::cout << " - fires at (" << randX << ", " << randY << ")";
            auto it = std::find_if(robots.begin(), robots.end(), [&](Robot* robot) {
                return robot->getX() == randX && robot->getY() == randY;
            });
            if (it != robots.end()) {
                std::cout << " - Robot at (" << randX << ", " << randY << ") killed!" << std::endl;
                (*it)->loseLife();
                if ((*it)->getLives() == 0) {
                    delete *it;
                    robots.erase(it);
                }
                addKill();
                if (getKills() == 3) {
                    TerminatorRoboCop* newTRC = new TerminatorRoboCop(posX, posY, name);
                    robots.emplace_back(newTRC);  // Upgrade to TerminatorRoboCop
                    robots.erase(find(robots.begin(), robots.end(), this));
                }
            } else {
                std::cout << " - No robot at (" << randX << ", " << randY << ")." << std::endl;
            }
        }
    }
}

void Robocop::look(list<Robot*>& robots) {
    std::cout << "RoboCop at (" << posX << ", " << posY << ") is looking around." << std::endl;
    move();
    fire(robots);
}

BlueThunder::BlueThunder(int x, int y, string n) : Robot(x, y, n) {
    std::cout << "BlueThunder " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string BlueThunder::getType() const { return "BlueThunder"; }

void BlueThunder::fire(list<Robot*>& robots) {
    static int firingSequence[8][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    int step = rand() % 8;
    int targetX = posX + firingSequence[step][0];
    int targetY = posY + firingSequence[step][1];

    if (targetX == posX && targetY == posY) {
        std::cout << "BlueThunder at (" << posX << ", " << posY << ") cannot commit suicide!" << std::endl;
    } else {
        auto it = std::find_if(robots.begin(), robots.end(), [&](Robot* robot) {
            return robot->getX() == targetX && robot->getY() == targetY;
        });
        if (it != robots.end()) {
            std::cout << "BlueThunder at (" << posX << ", " << posY << ") killed robot at (" << targetX << ", " << targetY << ")" << std::endl;
            (*it)->loseLife();
            if ((*it)->getLives() == 0) {
                delete *it;
                robots.erase(it);
            }
            addKill();
        } else {
            std::cout << "BlueThunder fires at (" << targetX << ", " << targetY << ") - No robot at (" << targetX << ", " << targetY << ")." << std::endl;
        }
    }
}

void BlueThunder::move() {}

void BlueThunder::look(list<Robot*>& robots) {}

Terminator::Terminator(int x, int y, string n) : Robot(x, y, n) {
    std::cout << "Terminator " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string Terminator::getType() const { return "Terminator"; }

void Terminator::move() {
    int newX = posX + (rand() % 3 - 1);
    int newY = posY + (rand() % 3 - 1);
    newX = std::max(1, std::min(newX, 8));
    newY = std::max(1, std::min(newY, 8));
    posX = newX;
    posY = newY;
    std::cout << "Terminator moved to a new position." << std::endl;
}

void Terminator::fire(list<Robot*>& robots) {}

void Terminator::look(list<Robot*>& robots) {
    std::cout << "Terminator at (" << posX << ", " << posY << ") is looking around." << std::endl;
    move();
    std::cout << "Terminator at (" << posX << ", " << posY << ") terminates robots." << std::endl;
}

Madbot::Madbot(int x, int y, string n) : Robot(x, y, n) {
    std::cout << "Madbot " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string Madbot::getType() const { return "Madbot"; }

void Madbot::move() {
    posX = rand() % 8 + 1;
    posY = rand() % 8 + 1;
    std::cout << "Madbot moved to (" << posX << ", " << posY << ")" << std::endl;
}

void Madbot::fire(list<Robot*>& robots) {
    std::cout << "Madbot at (" << posX << ", " << posY << ") fires:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        int randX = rand() % 8 + 1;
        int randY = rand() % 8 + 1;
        if (randX == posX && randY == posY) {
            std::cout << " - fires at (" << randX << ", " << randY << ")";
            std::cout << " - Madbot cannot commit suicide!" << std::endl;
        } else {
            std::cout << " - fires at (" << randX << ", " << randY << ")";
            auto it = std::find_if(robots.begin(), robots.end(), [&](Robot* robot) {
                return robot->getX() == randX && robot->getY() == randY;
            });
            if (it != robots.end()) {
                std::cout << " - Robot at (" << randX << ", " << randY << ") killed!" << std::endl;
                (*it)->loseLife();
                if ((*it)->getLives() == 0) {
                    delete *it;
                    robots.erase(it);
                }
                addKill();
                if (getKills() == 3) {
                    RoboTank* newRoboTank = new RoboTank(posX, posY, name);
                    robots.push_back(newRoboTank);  // Upgrade to RoboTank
                    delete this;  // Remove the Madbot
                    robots.erase(find(robots.begin(), robots.end(), this));
                }
            } else {
                std::cout << " - No robot at (" << randX << ", " << randY << ")." << std::endl;
            }
        }
    }
}

void Madbot::look(list<Robot*>& robots) {
    std::cout << "Madbot at (" << posX << ", " << posY << ") is looking around." << std::endl;
    move();
    fire(robots);
}

RoboTank::RoboTank(int x, int y, string n) : Robot(x, y, n) {
    std::cout << "RoboTank " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string RoboTank::getType() const { return "RoboTank"; }

void RoboTank::move() {
    int newX = posX + (rand() % 3 - 1);
    int newY = posY + (rand() % 3 - 1);
    newX = std::max(1, std::min(newX, 8));
    newY = std::max(1, std::min(newY, 8));
    posX = newX;
    posY = newY;
    std::cout << "RoboTank moved to a new position." << std::endl;
}

void RoboTank::fire(list<Robot*>& robots) {}

void RoboTank::look(list<Robot*>& robots) {
    std::cout << "RoboTank at (" << posX << ", " << posY << ") is looking around." << std::endl;
    move();
    std::cout << "RoboTank at (" << posX << ", " << posY << ") fires at robots." << std::endl;
}

UltimateRobot::UltimateRobot(int x, int y, string n) : Robot(x, y, n) {
    std::cout << "UltimateRobot " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string UltimateRobot::getType() const { return "UltimateRobot"; }

void UltimateRobot::move() {
    posX = rand() % 8 + 1;
    posY = rand() % 8 + 1;
    std::cout << "UltimateRobot moved to (" << posX << ", " << posY << ")" << std::endl;
}

void UltimateRobot::fire(list<Robot*>& robots) {
    std::cout << "UltimateRobot at (" << posX << ", " << posY << ") fires:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        int randX = rand() % 8 + 1;
        int randY = rand() % 8 + 1;
        if (randX == posX && randY == posY) {
            std::cout << " - fires at (" << randX << ", " << randY << ")";
            std::cout << " - UltimateRobot cannot commit suicide!" << std::endl;
        } else {
            std::cout << " - fires at (" << randX << ", " << randY << ")";
            auto it = std::find_if(robots.begin(), robots.end(), [&](Robot* robot) {
                return robot->getX() == randX && robot->getY() == randY;
            });
            if (it != robots.end()) {
                std::cout << " - Robot at (" << randX << ", " << randY << ") killed!" << std::endl;
                (*it)->loseLife();
                if ((*it)->getLives() == 0) {
                    delete *it;
                    robots.erase(it);
                }
                addKill();
            } else {
                std::cout << " - No robot at (" << randX << ", " << randY << ")." << std::endl;
            }
        }
    }
}

void UltimateRobot::look(list<Robot*>& robots) {
    std::cout << "UltimateRobot at (" << posX << ", " << posY << ") is looking around." << std::endl;
    move();
    fire(robots);
}

TerminatorRoboCop::TerminatorRoboCop(int x, int y, string n) : Robot(x, y, n), Robocop(x, y, n), Terminator(x, y, n) {
    std::cout << "TerminatorRoboCop " << name << " is created at (" << x << ", " << y << ")." << std::endl;
}

string TerminatorRoboCop::getType() const { return "TerminatorRoboCop"; }

void TerminatorRoboCop::move() {
    Robocop::move();
}

void TerminatorRoboCop::fire(list<Robot*>& robots) {
    Robocop::fire(robots);
}

void TerminatorRoboCop::look(list<Robot*>& robots) {
    std::cout << "TerminatorRoboCop at (" << posX << ", " << posY << ") is looking around." << std::endl;
    move();
    fire(robots);
}

void readRobotDetails(const string& line, string& robotType, string& robotName) {
    istringstream iss(line);
    iss >> robotType >> robotName;
}

void printBattlefield(int M, int N, const list<Robot*>& robots) {
    cout << setw(3) << "";
    for (int i = 1; i <= N; ++i) {
        cout << setw(3) << i;
    }
    cout << endl;

    for (int i = 1; i <= M; ++i) {
        cout << setw(3) << i;
        for (int j = 1; j <= N; ++j) {
            bool robotFound = false;
            for (const auto& robot : robots) {
                if (robot->getX() == j && robot->getY() == i) {
                    if (dynamic_cast<Robocop*>(robot)) {
                        cout << setw(3) << 'R';
                    } else if (dynamic_cast<BlueThunder*>(robot)) {
                        cout << setw(3) << 'B';
                    } else if (dynamic_cast<Terminator*>(robot)) {
                        cout << setw(3) << 'T';
                    } else if (dynamic_cast<Madbot*>(robot)) {
                        cout << setw(3) << 'M';
                    } else if (dynamic_cast<RoboTank*>(robot)) {
                        cout << setw(3) << 'K';
                    } else if (dynamic_cast<UltimateRobot*>(robot)) {
                        cout << setw(3) << 'U';
                    } else if (dynamic_cast<TerminatorRoboCop*>(robot)) {
                        cout << setw(3) << 'C';
                    }
                    robotFound = true;
                    break;
                }
            }
            if (!robotFound) {
                cout << setw(3) << "*";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void simulateSteps(int steps, int M, int N, list<Robot*>& robots, queue<Robot*>& robotQueue) {
    for (int step = 0; step < steps; ++step) {
        cout << "Step " << step + 1 << ":" << endl;
        printBattlefield(M, N, robots);

        for (auto it = robots.begin(); it != robots.end(); ++it) {
            (*it)->look(robots);
        }

        if (!robotQueue.empty()) {
            Robot* reenteringRobot = robotQueue.front();
            robotQueue.pop();
            int newX = rand() % 8 + 1;
            int newY = rand() % 8 + 1;
            reenteringRobot->move(newX, newY);
            robots.push_back(reenteringRobot);
            cout << "Robot re-entered at (" << newX << ", " << newY << ")" << endl;
        }
    }

    Robot* winner = nullptr;
    for (auto& robot : robots) {
        if (!winner || robot->getKills() > winner->getKills()) {
            winner = robot;
        }
    }

    if (winner) {
        cout << "The winner is a " << winner->getType() << " named " << winner->getName() << " with " << winner->getKills() << " kills." << endl;
    }
}

void simulateBattlefield(const string& inputFilename) {
    ifstream inputFile(inputFilename);

    string line;
    int M = 0, N = 0, steps = 0, robotsCount = 0;
    list<Robot*> robots;
    queue<Robot*> robotQueue;

    try {
        if (!inputFile.is_open()) {
            throw runtime_error("Unable to open the input file.");
        }

        getline(inputFile, line);
        istringstream iss1(line);
        string battlefieldLabel, colon;
        iss1 >> battlefieldLabel >> colon >> M >> N;

        getline(inputFile, line);
        istringstream iss2(line);
        string stepLabel;
        iss2 >> stepLabel >> steps;

        getline(inputFile, line);
        istringstream iss3(line);
        string robotLabel;
        iss3 >> robotLabel >> robotsCount;

        set<pair<int, int>> positions; // To keep track of occupied positions

        for (int i = 0; i < robotsCount; ++i) {
            getline(inputFile, line);
            string type, name;
            readRobotDetails(line, type, name);

            // Randomize the initial position
            int x, y;
            do {
                x = rand() % 8 + 1;
                y = rand() % 8 + 1;
            } while (positions.count({x, y}) > 0); // Ensure unique positions

            positions.insert({x, y});

            if (type == "BlueThunder") {
                robots.emplace_back(new BlueThunder(x, y, name));
            } else if (type == "RoboCop") {
                robots.emplace_back(new Robocop(x, y, name));
            } else if (type == "Terminator") {
                robots.emplace_back(new Terminator(x, y, name));
            } else if (type == "Madbot") {
                robots.emplace_back(new Madbot(x, y, name));
            } else if (type == "RoboTank") {
                robots.emplace_back(new RoboTank(x, y, name));
            } else if (type == "UltimateRobot") {
                robots.emplace_back(new UltimateRobot(x, y, name));
            } else if (type == "TerminatorRoboCop") {
                robots.emplace_back(new TerminatorRoboCop(x, y, name));
            }
        }

        inputFile.close();

        simulateSteps(steps, M, N, robots, robotQueue);

        for (auto robot : robots) {
            delete robot;
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
