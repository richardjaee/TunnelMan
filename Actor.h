#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <algorithm>
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
private:
    StudentWorld * m_StudentWorld;
    bool isAlive;
    
public:
    // NAME: Actor Constructor
    // INPUT: imageID integer, integer x, integer y, pointer to StudentWord, direction, a double size, unsigned integer depth
    // OUTPUT: None
    // DESCRIPTION: Constructor for Actor Class
    Actor(int imageID, int x, int y,  StudentWorld * m_world, Direction dir = right, double size = 1.0, unsigned int depth = 0); //constructor
    
    // NAME: getWorld
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: pointer to StudentWorld
    StudentWorld * getWorld();
    
    // NAME: Actor Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION:
    virtual ~Actor();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: pure virtual function
    void virtual doSomething() = 0; //pure virtual
    
    // NAME: alive
    // INPUT: None
    // OUTPUT: A boolean
    // DESCRIPTION: true if isAlive is true, false otherwise
    bool alive();
    
    // NAME: dead
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: sets isAlive to false
    void dead();

};

class TunnelMan : public Actor
{
private:
    int m_hp;
    int m_waterAmmo;
    int m_goldNugget;
    int m_Sonar;
public:
    
    // NAME: getHP
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: Returns the current HP of the TunnelMan
    int getHP() const;
    
    // NAME: getGold
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: returns the current gold count of the TunnelMan
    int getGold() const;
    
    // NAME: Constructor
    // INPUT: pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for TunnelMan
    TunnelMan(StudentWorld * m_world);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for TunnelMan
    virtual ~TunnelMan();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT:  None, void
    // DESCRIPTION: TunnelMan's doSomething
    void virtual doSomething();
    
    // NAME: foundGold
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Increments goldNugget
    void foundGold();
    
    // NAME: Ammo
    // INPUT: an integer x
    // OUTPUT: None, void
    // DESCRIPTION: decrements or increments ammo count depending on the input
    void Ammo(int x);
    
    // NAME: SonarAdd
    // INPUT: an integer x
    // OUTPUT: None, void
    // DESCRIPTION: increments sonar
    void SonarAdd(int x);
    
    // NAME: remaining ammo
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: returns the current amount of water ammo
    int remainingAmmo();
    
    // NAME: remainingSonar
    // INPUT: None
    // OUTPUT: an integer
    // DESCRIPTION: returns the current amount of sonar ammo
    int remainingSonar();
    
    // NAME: annoyed
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: when called, will decrement health of the tunnelman by 2
    void annoyed();
};

class WaterSquirt : public Actor
{
private:
    int ticksLeft;
    
public:
    // NAME: Constructor
    // INPUT: an integer x, integer y, pointer to StudentWorld, direction dir
    // OUTPUT: None
    // DESCRIPTION: Constructor for WaterSquirt class
    WaterSquirt(int x, int y, StudentWorld * world, Direction dir);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for WaterSquirt class
    virtual ~WaterSquirt();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: WaterSquirt's doSomething
    void virtual doSomething();
};

class Boulder : public Actor
{
public:
    // NAME: Constructor
    // INPUT: integer x, integer y, pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for Boulder class
     Boulder(int x, int y, StudentWorld* world);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for Boulder class
    virtual ~Boulder();
    
    // NAME: doSoemthing
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Boulder's doSomething
    void virtual doSomething();
};

class Earth : public Actor
{
public:
    // NAME: Constructor
    // INPUT: integer x, integer y, pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for Earth Class
    Earth(int x, int y, StudentWorld * m_world);
    
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for Earth class
    virtual ~Earth();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Earth's doSomething function
    void virtual doSomething();

};


class Goodie : public Actor
{
public:
    // NAME: Constructor
    // INPUT: imageID, integer x, integer y, pointer to StudentWorld, direction right, double size, unsigned integer depth
    // OUTPUT: None
    // DESCRIPTION: Constructor for Goodie class
    Goodie(int imageID, int x, int y, StudentWorld* world, Direction dir = right, double size = 1.0, unsigned int depth = 0);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for Goodie class
    virtual ~Goodie();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Goodie's doSomething method
    void virtual doSomething();
};

class SonarKit : public Goodie {
private:
    int m_ticksLeft;
public:
    
    // NAME: Constructor
    // INPUT: integer x, integer y, pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for SonarKit class
    SonarKit(int x, int y, StudentWorld * world);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: SonarKit's destructor
    virtual ~SonarKit();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: SonarKit's doSomething method
    void virtual doSomething();
};

class WaterPool : public Goodie {
private:
    int ticksLeft;
public:
    
    // NAME: Constructor
    // INPUT: integer x, integer y, pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for WaterPool class
    WaterPool(int x, int y, StudentWorld * world);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for WaterPool class
    virtual ~WaterPool();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: WaterPool's doSomething Method
    void virtual doSomething();
    
};
class Barrel : public Goodie
{
public:
    
    // NAME: Constructor
    // INPUT: integer x, integer y, pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for Barrel class
    Barrel(int x, int y, StudentWorld * world);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for Barrel class
    virtual ~Barrel();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Barrel's doSomething method
    void virtual doSomething();
private:
    int ticksLeft;
};

class GoldNugget : public Goodie
{
private:
    int ticksLeft;
public:
    
    // NAME: Constructor
    // INPUT: integer x, integer y, pointer to StudentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for GoldNugget class
    GoldNugget(int x, int y, StudentWorld * world);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for GoldNugget
    virtual ~GoldNugget();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: GoldNugget's doSomething method
    void virtual doSomething();
};


class Protester : public Actor {
private:
    int m_yellTicks;
    int m_restTicks;
public:
    
    // NAME: Constructor
    // INPUT: imageID, integer x, integer y, pointer to studentWorld, integer HP
    // OUTPUT: None
    // DESCRIPTION: Constructor for Protestor Class
    Protester(int imageID, int x, int y, StudentWorld* world, int HP);
    
    // NAME: Destructor
    // INPUT: None
    // OUTPUT: None
    // DESCRIPTION: Destructor for Protestor class
    virtual ~Protester();
    
    // NAME: doSomething
    // INPUT: None
    // OUTPUT: None, void
    // DESCRIPTION: Protester's doSomething Method
    virtual void doSomething();
   
    // NAME: move
    // INPUT: Direction direction
    // OUTPUT: None, void
    // DESCRIPTION: will move the Protester in a given direction
    void move(Direction direction);
    
    // NAME: isFacingPlayer
    // INPUT: None
    // OUTPUT: a boolean
    // DESCRIPTION: true if the protestor is facing the tunnelMan, false otherwise
    bool facingPlayer();

};

class RegularProtester : public Protester
{
public:
    // NAME: Constructor
    // INPUT: pointer to studentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for Regular Protestor class
    RegularProtester(StudentWorld* world);
};

class HardcoreProtester : public Protester
{
public:
    // NAME: Constructor
    // INPUT: pointer to studentWorld
    // OUTPUT: None
    // DESCRIPTION: Constructor for HardCoreProtestor class
    HardcoreProtester(StudentWorld* world);
};
#endif // ACTOR_H_
