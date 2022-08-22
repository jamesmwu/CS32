//James Wu
//CS32 Project 1

#include <iostream>
//#include <string>
//#include <ctime>

//New headers
//#include "Player.h"
//#include "Arena.h"
//#include "Robot.h"
#include "Game.h"
//#include "globals.h"

using namespace std;


int main()
{
      // Initialize the random number generator.  (You don't need to
      // understand how this works.)
    srand(static_cast<unsigned int>(time(0)));

      // Create a game
      // Use this instead to create a mini-game:
//    Game g(15, 18, 80);

    Game g(3, 3, 2);
//    Game g(10, 10, 5);

      // Play the game
    g.play();
}
