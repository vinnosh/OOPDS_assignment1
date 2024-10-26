
#include "robot.h"
#include <ctime>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    simulateBattlefield("simulation.txt");
    return 0;
}
