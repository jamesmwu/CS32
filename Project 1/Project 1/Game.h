//
//  Game.h
//  Project 1
//
//  Created by James Wu on 6/22/22.
//

#ifndef Game_h
#define Game_h
class Arena;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

        // Mutators
    void play();

  private:
    Arena* m_arena;
};

#endif /* Game_h */
