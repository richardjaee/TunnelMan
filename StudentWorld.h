#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "GraphObject.h"
#include <vector>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld : public GameWorld
{
public:
    
    // NAME: Constructor
    // INPUT: assetDir string
    // OUTPUT: Nobe
    // DESCRIPTION: Constructor for StudentWorld
    StudentWorld(std::string assetDir);
    
    // NAME: init
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: initializes the game and its objects
    virtual int init();
    
    // NAME: move
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: Calls the TunnelMan's doSomething method, creates Protesters, deletes Objects
    virtual int move();
    
    // NAME: EarthDelete
    // INPUT: an integer x, an integer y
    // OUTPUT: None, void
    // DESCRIPTION: Will set earth's setvisible to false
    void EarthDelete(int x, int y); 
    
    // NAME: removeEarth
    // INPUT: integer x, integer y
    // OUTPUT: None, void
    // DESCRIPTION: creates the tunnel
    void removeEarth(int x, int y);
    
    // NAME: grid
    // INPUT: an integer x, an integer y
    // OUTPUT: an integer
    // DESCRIPTION: will return the current value at the current coordinate on the grid
    int grid(int x, int y);
    
    // NAME: getTunnelMan
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: pointer to TunnelMan
    TunnelMan * getTunnelMan() const;
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for StudentWorld
    ~StudentWorld();
    
    // NAME: cleanUp
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Removes objects at the end of a level
    virtual void cleanUp();

    // NAME: BoulderInWay
    // INPUT: an integer x, an integer y
    // OUTPUT: a boolean
    // DESCRIPTION: true if there is a boulder <= 4 from the TunnelMan, false otherwise
    bool BoulderInWay(int x, int y) const;
    
    // NAME: randomCoord
    // INPUT: a reference to an integer x and y
    // OUTPUT: None, void
    // DESCRIPTION: will randomly set x and y
    void randomCoord(int &x, int &y);
    
    // NAME: foundBarrel
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: decrements the needed oil count
    void foundBarrel();
    
    // NAME: shootWater
    // INPUT: an integer x, an integer y
    // OUTPUT: None, void
    // DESCRIPTION: will shoot water and decrement the ammo count
    void shootWater(int x, int y);
   
    // NAME: restTicks
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: retuns the current level's rest ticks for the protester
    int restTicks();
    
    // NAME: minusProtester
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: decrements Protester count
    void minusProtester();
    
    // NAME: spawnProtester
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: will spawn a protester at 60,60
    void spawnProtester();
    
    // NAME: setDisplayText
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: displays the current state of the game
    void setDisplayText();
    
    // NAME: displayFormat
    // INPUT: int level, int lives, int health, int squirts,int gold,int barrelsLeft, int  sonar,int score
    // OUTPUT: a string
    // DESCRIPTION: will return a properly formatted display
    std::string displayFormat(int level, int lives, int health, int squirts,int gold,int barrelsLeft, int  sonar,int score);
    
    // NAME: sonarUse
    // INPUT: an integer x, an integer y
    // OUTPUT: None, void
    // DESCRIPTION: will decrement sonar ammo
    void sonarUse(int x, int y);
    
    // NAME: barrelsRemaining
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: returns the current needed barrel count
    int barrelsRemaining();
    
private:
    //The game window is exactly 64 squares wide by 64 squares high.
    TunnelMan * m_tunnelMan; //tunnelman pointer
    Earth * m_board[64][64]; //earth pointer to 2d array
    std::vector<Actor*> m_actor;
    int mapGrid[64][64];
    int m_ticks;
    int m_ticksPassed;
    int m_barrels;
    int m_gold;
    int m_protesters;
};


#endif // STUDENTWORLD_H_
