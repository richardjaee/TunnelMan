#include "Actor.h"
#include "StudentWorld.h"
#include "GraphObject.h"
#include <algorithm>
// CONSTRUCTORS

Actor::Actor(int imageID, int x, int y, StudentWorld* world, Direction dir, double size, unsigned int depth) : GraphObject(imageID, x, y, dir, size, depth), isAlive(true), m_StudentWorld(world)
{
    setVisible(true);
}
Goodie::Goodie(int imageID, int x, int y, StudentWorld * world, Direction dir, double size, unsigned int depth) : Actor(imageID, x, y, world, dir, size, depth) {}

Earth::Earth(int x, int y, StudentWorld * m_world) : Actor(TID_EARTH, x, y, m_world, right, 0.25 , 3){}

TunnelMan::TunnelMan(StudentWorld * m_world): Actor(TID_PLAYER, 30, 60, m_world), m_hp(10), m_waterAmmo(5), m_Sonar(1), m_goldNugget(0) {}

WaterSquirt::WaterSquirt(int x, int y, StudentWorld * world, Direction dir) :
Actor(TID_WATER_SPURT, x, y, world, dir, 1.0, 1), ticksLeft(0) {}

RegularProtester::RegularProtester(StudentWorld* world)
: Protester(TID_PROTESTER, 60, 60, world, 5) {}

HardcoreProtester::HardcoreProtester(StudentWorld* world)
: Protester(TID_HARD_CORE_PROTESTER, 60, 60, world, 20 ) {}
Protester::Protester(int imageID, int x, int y, StudentWorld* world, int HP)
: Actor(imageID, x, y, world, left, 1.0, 0),  m_yellTicks(15)
{
    m_restTicks = getWorld()->restTicks();
}

Barrel::Barrel(int x, int y, StudentWorld * world): Goodie(TID_BARREL, x, y, world, right, 1.0, 2)
{
    setVisible(false);
}

GoldNugget::GoldNugget(int x, int y, StudentWorld *world) : Goodie(TID_GOLD, x, y, world, right, 1.0, 2)
{
    setVisible(false);
}

Boulder::Boulder(int x, int y, StudentWorld* world) :
Actor(TID_BOULDER, x, y, world, down, 1.0, 1){}

WaterPool::WaterPool(int x, int y, StudentWorld * world): Goodie(TID_WATER_POOL, x, y, world, right, 1.0, 2), ticksLeft(std::max(100, int(300 - 10 * world->getLevel()))){}

SonarKit::SonarKit(int x, int y, StudentWorld * world) :Goodie(TID_SONAR,x,y,world,right,1.0,2),m_ticksLeft(std::max(100, int(300 - 10 * world->getLevel()))) {}

//destructors
Actor::~Actor(){}

SonarKit::~SonarKit(){}

Earth::~Earth(){}

TunnelMan::~TunnelMan(){}

WaterSquirt::~WaterSquirt(){}

Goodie::~Goodie(){}

Barrel::~Barrel(){}

Boulder::~Boulder(){}

GoldNugget::~GoldNugget(){}

WaterPool::~WaterPool() {}
Protester::~Protester() {}


//studentWorld pointer
StudentWorld * Actor::getWorld() {
    return m_StudentWorld;
    
}

//protester methods
bool Protester::facingPlayer(){
    switch (getDirection()) { //switch statement
        case left:
            return getWorld()->getTunnelMan()->getX() <= getX(); //return true if protester is facing the tunnelman to the left
        case right:
            return getWorld()->getTunnelMan()->getX() >= getX(); //return true if protester is facing the tunnelman to the right
        case up: //did not finish
            return false;
        case down:
            return false;
        case none:
            return false;
    }
    return false;
}

void Protester::move(Direction direction){
    switch (direction) { //switch statement
    case left:
        if (getDirection() == left) {
            if (getX() == 0){ //if we've reached the end of the board
                setDirection(right); //turn around
                
            }
            moveTo(getX() - 1, getY()); //decrement x
        }
        else{
            setDirection(left); //otherwise look to the left
        }
        break;
    case right:
        if (getDirection() == right) {
            if (getX() == 60) { //if we've reached the end of the board
                setDirection(left); //turn around
                
            }
            moveTo(getX() + 1, getY()); //increment x
        }
        else {
            setDirection(right); //otherwise, look to the right
        }
        break;
    case up: //did not finish
        break;
    case down:
        break;
    case none:
        return;
    }
}

//actor methods
bool Actor::alive(){
    return (isAlive); //if the actor is stil alive, return true
}

void Actor::dead(){
    isAlive = false; //set the private member function, isAlive to false
}

//TunnelMan methods
void TunnelMan::Ammo(int x){
    m_waterAmmo += x; //increment waterAmmo by the given x
}

void TunnelMan::annoyed(){
    m_hp-=2; //decrement hp by 2
    if (m_hp <= 0){ //if the player's health has dropped to 0 or below
        dead(); //call the dead functio, which will end the game
    }
}

int TunnelMan::getGold() const{
    return m_goldNugget; //return the current count of goldNuggets
}

void TunnelMan::SonarAdd(int x){
    m_Sonar+=x; //increment the current count of Sonar by the given x
}

int TunnelMan::remainingSonar(){
    return m_Sonar; //returns the current count of Sonar
}

void TunnelMan::foundGold(){
    m_goldNugget++; //increments the current count of goldNugget
}

int TunnelMan::getHP() const{
    return m_hp; //returns the current amount of HP
}

int TunnelMan::remainingAmmo(){
    return m_waterAmmo; //returns the current amount of waterAmmo
}

//class doSomething functions
void WaterPool::doSomething(){
    if (!alive()){ //if the waterPool is not alive
        return;
    }
    
    ticksLeft--; //decrement ticksLeft
    
    if (ticksLeft <= 0){ //the lifetime is over
        dead(); //set the waterPool actor to dead
    }
    
    double rad = sqrt(pow(getX()-getWorld()->getTunnelMan()->getX(), 2.0) + pow(getY()-getWorld()->getTunnelMan()->getY(), 2.0)); //calculate radius
    if (rad <= 3){ //picked up
        dead(); //call the dead function
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getTunnelMan()->Ammo(5); //increase ammo count by 5
        getWorld()->increaseScore(500); //increase the score by 500
    }
}

void SonarKit::doSomething(){
    if (!alive()){
        return;
    }
    m_ticksLeft--;
    
    if (m_ticksLeft <= 0){ //end of life
        dead();
    }
    
    double radius = sqrt(pow(getX() - getWorld()->getTunnelMan()->getX(), 2.0) + pow(getY() - getWorld()->getTunnelMan()->getY(), 2.0)); //calculate radius
    
    if (radius <= 3){ //goodie picked up
        dead(); //call the dead function
        getWorld()->playSound(SOUND_GOT_GOODIE); //play the corresponding sound
        getWorld()->increaseScore(75); //increase score by 75
    }
}

void Boulder::doSomething(){
    if (!alive()){
        return;
    }
}

void Protester::doSomething(){
    
    if (!alive()){
       return;
    }
    
    if (m_restTicks > 0) { //if the protester is in a rest state
        m_restTicks--; //derement restTicks
        return;
    }
    else {
        m_restTicks = getWorld()->restTicks(); //reset restTicks
        m_yellTicks++; //increment yellticks
    }
    
    move(getDirection()); //move the protester
   
    double rad = sqrt(pow(getX() - getWorld()->getTunnelMan()->getX(), 2.0) + pow(getY() - getWorld()->getTunnelMan()->getY(), 2.0)); //calculates radius
    
    if (rad <= 4 && facingPlayer()) { //if radius is less than or equal to 4 and is facing the player
        if (m_yellTicks > 15) {
            getWorld()->getTunnelMan()->annoyed(); //calls the tunnelman annoyed method
            getWorld()->playSound(SOUND_PROTESTER_YELL);
            m_yellTicks = 0; //resets yellticks
            return;
        }
        return;
    }
    
}

void GoldNugget::doSomething(){
     if (!alive()){ //The object must check to see if it is currently alive. If not, then its doSomething() method must return immediately – none of the following steps should be performed.
            return;
        }
        
        //Otherwise, if the Gold Nugget is not currently visible AND the TunnelMan is within a radius of 4.0 of it (<= 4.00 units away), then:
        double rad = sqrt(pow(getX() - getWorld()->getTunnelMan()->getX(), 2.0) + pow(getY() - getWorld()->getTunnelMan()->getY(), 2.0));
        
        if (!isVisible() && rad <= 4){ //if the player is in proximity
            setVisible(true); //The Gold Nugget must make itself visible with the setVisible() method.
            return; //The Gold Nugget doSomething() method must immediately return.
        }
        
        if (rad <= 3) //Otherwise, if the Gold Nugget is pickup-able by the TunnelMan and it is within a radius of 3.0 (<= 3.00 units away) from the TunnelMan, then the Gold Nugget will activate, and:
        {
            dead(); //The Gold Nugget must set its state to dead (so that it will be removed by your StudentWorld class from the game at the end of the current tick)
            getWorld()->playSound(SOUND_GOT_GOODIE);// The Gold Nugget must play a sound effect to indicate that the TunnelMan picked up the Goodie: SOUND_GOT_GOODIE..
            getWorld()->increaseScore(10); //The Gold Nugget increases the player’s score by 10 points (This increase can be performed by the TunnelMan class or the Gold Nugget class).
            getWorld()->getTunnelMan()->foundGold(); //The Gold Nugget must tell the TunnelMan object that it just received a new Nugget so it can update its inventory.
        }
    
}


void Barrel::doSomething(){
    
    if (!alive()){ //The object must check to see if it is currently alive. If not, then its doSomething() method must return immediately – none of the following steps should be performed.
        return;
    }
    
    //Otherwise, if the Barrel is not currently visible AND the TunnelMan is within a radius of 4.0 of it (<= 4.00 units away), then:
    double rad = sqrt(pow(getX() - getWorld()->getTunnelMan()->getX(), 2.0) + pow(getY() - getWorld()->getTunnelMan()->getY(), 2.0)); //calculates radius
    
    if (!isVisible() && rad <= 4){ //if the player is in proximity
        setVisible(true); //The Barrel must make it self visible with the setVisible() method.
        return; //The Barrel’s doSomething() method must immediately return.
    }
    
    if (rad <= 3) //Otherwise, if the Barrel is within a radius of 3.0 (<= 3.00 units away) from the TunnelMan, then the Barrel will activate, and:
    {
        dead(); //The Barrel must set its state to dead
        getWorld()->playSound(SOUND_FOUND_OIL); //The Barrel must play a sound effect to indicate that the player picked up the Goodie: SOUND_FOUND_OIL.
        getWorld()->increaseScore(1000); //The Barrel must increase the player’s score by 1000 points.
        getWorld()->foundBarrel(); //decrement barrels needed
    }
}


void WaterSquirt::doSomething(){
    ticksLeft++; //increment ticks left
    int x = getX();
    int y = getY();
    if (ticksLeft == 8){ //if it has reached its max life cycle, 8 ticks
        dead(); // call the dead funcion
        return;
    }
    if (getDirection() == right){ //if the direction is to the right
        if (x + 1 <= 60){ //if we are not at the edge of the map
            moveTo(x + 1, y);
        }
        else{
            dead(); //call the dead function
        }
        return;
    }
    
    if (getDirection() == left){ //if the direction is to the left
        if (x - 1 >= 0){ //if we are not at the edge of the map
            moveTo(x - 1, y);
        }
        else{
            dead(); //call the dead function
        }
        return;
    }
    if (getDirection() == down){ //if the direction is downwards
        if (y - 1 >= 0){ //if we are not at the edge of the map
            moveTo(x, y-1);
        }
        else{
            dead();
        }
        return;
    }
    
    if (getDirection() == up){ //if the direction is upwards
        if (y + 1 <= 60){ //if we are not at the edge of the map
            moveTo(x, y+1);
        }
        else{
            dead();
        }
        return;
    }
    
    
}


void Earth::doSomething(){}

void TunnelMan::doSomething(){
    
    if (alive() == false){
        return;
    }
    int ch = 0; //initialize ch to 0
       if (getWorld()->getKey(ch)){
           
           switch (ch){
               case KEY_PRESS_SPACE: //if the user has hit space
               {
                   getWorld()->shootWater(getX(), getY()); //call the shootwater method
                   break;
               }
               case KEY_PRESS_ESCAPE: //if the user has hit escape
               {
                   dead(); //kill the player
                   break;
               }
               case 'z': //if the user has hit z or z
               case 'Z':
               {
                   if (m_Sonar <= 0){ //if we dont have ammo
                       break;
                   }
                   getWorld()->sonarUse(getX(), getY()); //otherwise, use the Sonar
                   m_Sonar--; //decrement sonar count
               }
               case KEY_PRESS_LEFT:
                   if (getX() > 0 && getDirection() == left && !getWorld()->BoulderInWay(getX()-1, getY())){ //if we are facing left and do not have a boulder in our way
                       
                       moveTo(getX() - 1, getY()); //move one space left
                       getWorld()->removeEarth(getX(), getY()); //dig the earth
                   }
                   else{
                       
                       setDirection(left); //otherwise, turn the tunnelman left
                   }
                   break;
                   
               case KEY_PRESS_RIGHT:
                   if (getX() < 60 && getDirection() == right && !getWorld()->BoulderInWay(getX()+1, getY())){ //if we are facing right and do not have a boulder in our way
                       
                       moveTo(getX() + 1, getY()); //move one space right
                       
                       getWorld()->removeEarth(getX(), getY()); //dig the earth
                   }
                   else{
                       
                       setDirection(right); //otherwise, turn the tunnelman right
                   }
                   break;
                   
               
                   
               case  KEY_PRESS_UP:
                   
                   if (getY() < 60 && getDirection()== up && !getWorld()->BoulderInWay(getX(), getY() + 1)){ //if we are facing up and do not have a boulder in our way
                       moveTo(getX(), getY() + 1); //move one space up
                       
                      getWorld()->removeEarth(getX(), getY()); //dig the earth
                   }
                   else{
                       
                       setDirection(up); //otherwise, turn the tunnelman upwards
                   }
                   break;
                   
               case KEY_PRESS_DOWN:
                   if (getY() > 0 && getDirection() == down && !getWorld()->BoulderInWay(getX(), getY()- 1)){ //if we are facing down and do not have a boulder in our way
                       
                       moveTo(getX(), getY() - 1); //move one space down
                       getWorld()->removeEarth(getX(), getY()); //dig the earth
                   }
                   else{
                       
                       setDirection(down); //otherwise, turn the tunnelman downwards
                   }
                   break;
                   
            }
           
       }
    
}

void Goodie::doSomething(){}


