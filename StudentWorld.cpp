#include "MainWorld.h"
#include <string>


using namespace std;

MainWorld::MainWorld(std::string assetDir)
: GameWorld(assetDir){}

GameWorld* createMainWorld(string assetDir)
{
	return new MainWorld(assetDir);
}

// Students:  Add code to this file (if you wish), MainWorld.h, Actor.h and Actor.cpp



void MainWorld::setDisplayText(){
    int level = getLevel();
    int lives = getLives();
    int health = m_tunnelMan->getHP()* 10;
    int squirts = m_tunnelMan->remainingAmmo();
    int gold = m_tunnelMan->getGold();
    int barrelsLeft = barrelsRemaining();
    int sonar = m_tunnelMan->remainingSonar();
    int score = getScore();
    
    
    // Lvl: 52 Lives: 3 Hlth: 80% Wtr: 20 Gld: 3 Oil Left: 2 Sonar: 1 Scr: 321000

 
    string s = displayFormat(level, lives, health, squirts, gold, barrelsLeft, sonar, score);
    GameWorld::setGameStatText(s); // calls our provided GameWorld::setGameStatText
    
}
string MainWorld::displayFormat(int level, int lives, int health, int squirts,int gold,int barrelsLeft, int  sonar,int score){
    
    stringstream s;
    
    s.fill(' '); s << "Lvl: " << setw(2) << level; //fills unuse space with a blank space
    s << " Lives: " << setw(1) << lives;
    s <<  " Hlth: " << setw(3) << health;
    s << "% Wtr: ";
    s << setw(2) << squirts;
    s << " Gld: " << setw(2) << gold;
    s << " Oil Left: " << setw(2) << barrelsLeft;
    s << " Sonar: " << setw(2) << sonar;
    s.fill('0'); //fills the unused with 0's
    s << " Scr: " << setw(6) << score; //will make sure the score has 6 places
     
    
    return s.str();
}

void MainWorld::foundBarrel(){
    m_barrels--; //decrements barrels needed
}

int MainWorld::barrelsRemaining(){
    return m_barrels; //returns the amount of barrels needed
}

void MainWorld::sonarUse(int x, int y){
    if (m_tunnelMan->remainingSonar() == 0){ //if there are no more sonar ammo, then return
        return;
    }
    SonarKit * sk = new SonarKit(x,y,this); //create a new SonarKit object
    m_actor.push_back(sk); //push the object into a vector
    
    this->playSound(SOUND_SONAR);
   // m_tunnelMan->SonarAdd(-1);
}

void MainWorld::shootWater(int x, int y){
    if (m_tunnelMan->remainingAmmo() == 0){ //if there is not more water ammo, then return
        return;
    }
    
    
    WaterSquirt *ws = new WaterSquirt(x, y, this, m_tunnelMan->getDirection()); //create a new WaterSquirt object
    m_actor.push_back(ws); //push teh water squirt object into a vector
    
    this->playSound(SOUND_PLAYER_SQUIRT);
    m_tunnelMan->Ammo(-1); //decrement ammo by 1
     
}

bool MainWorld::BoulderInWay(int x, int y) const{
  
    for (size_t i = 0; i < m_actor.size(); i++){ //checks every object in our vector
        
        if (m_actor[i]->getID() == TID_BOULDER){ //if the object is a boulder
            
            double rad = sqrt(pow(x - m_actor[i]->getX(), 2.0) + pow(y - m_actor[i]->getY(), 2.0)); //calculate radius
            if (rad <= 3){ //if radius is less then or equal to 3, return true, (its in our way)
                return true;
            }
        }
    }
    return false; //it is not in the way of the tunnelman, return false
     
}


void MainWorld::minusProtester(){
    m_protesters--; //decrement protester count
}

int MainWorld::restTicks(){
    int currlevel = getLevel();
    return max(0, 3 - currlevel/4); //return the restticks of the protesters based on the level we are on
}

int MainWorld::init(){
    m_tunnelMan = new TunnelMan(this); //creates a new tunnelman
    m_ticks = 0; //initializes ticks to 0
    
    //creating Earth
    for (int i = 0; i < 64; i++){
        
        for (int k = 0; k < 60; k++){
            
            m_board[i][k] = new Earth(i, k, this);
            mapGrid[i][k] = TID_EARTH;
            
        }
    }
    
    //creating tunnel
    for (int i = 30; i < 34; i++){
        for (int k = 4; k < 60; k++){
            EarthDelete(i, k);
        }
    }
    
    
    //boulders
    int B = min(int(getLevel() / 2 + 2), 9);
    for (int i = 0; i < B; i++)
       {
           int x = -1;
           int y = -1;
           while ((x < 0 || x > 60) || (y < 20  || y >56)){ //keeps calling randomCoord until we have correct x and y coords
               randomCoord(x, y);
           }
           for (int j = x; j < x + 4; j++)
           {
               for (int k = y; k < y + 4; k++)
               {
                   if (m_board[j][k] != nullptr)
                   {
                       delete m_board[j][k];
                       m_board[j][k] = nullptr;
                   }
               }
           }
           Boulder* boulder = new Boulder(x, y, this); //create a new boulder objecy
           m_actor.push_back(boulder); //push the boulder into the vector
       }
     
    
    //gold nuggets
    int G = max(int(5 - getLevel() / 2), 2); //calculate the maximum amount of gold objects we can have
    m_gold = G;
    for (int i = 0; i < G; i++)
          {
              int x;
              int y;
              randomCoord(x, y);
              GoldNugget * gold = new GoldNugget(x, y, this); //create a new goldNugget object
              m_actor.push_back(gold); //push the gold into the vector
          }
        
    
    //creating barrels
    int L = min(int(2 + getLevel()), 21);//calculate the max number of barrels we need to find
   
    m_barrels = L;
    for (int i = 0; i < L; i++)
      {
          int x;
          int y;
          randomCoord(x, y);
          Barrel * barrel = new Barrel(x, y, this); //create a new barrel object
          m_actor.push_back(barrel); //push the barrel into the vector
      }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

void MainWorld::spawnProtester(){
    
    int T = max(25, 200 - (int)getLevel()); //calculate ticks needed before we spawn another protester
    int P = fmin(15, 2 + getLevel() * 1.5); //calculate the max amount of protesters we can have
    int hardcore = min(90, (int)getLevel() * 10 + 30); //calculate the prbability of getting a harcore protester
    if (m_ticks == 1 || (m_ticksPassed > T && m_protesters < P)){
        if (rand() % 100 + 1 < hardcore){
            HardcoreProtester*HP = new HardcoreProtester(this); //create a new hardcore protester
            m_actor.push_back(HP); //push the protester into a vector
        }
        else{
        RegularProtester*RP = new RegularProtester(this);//create a new regular protester
        m_actor.push_back(RP); //push the protester into a vector
        }
        m_ticksPassed=0; //reset ticks passed
        m_protesters++; //increment protester count
    }
    m_ticksPassed++; //increment the amount of ticks passed
}
//done
void MainWorld::randomCoord(int &x, int&y){
   
    if (m_actor.size() == 0){ //there are no other actors on the board
        x = (rand() % 59) + 1; //randomize x and y
        y = (rand() % 59) + 1;
        return;
    }
    bool flag = false; //set a flag equal to false
    while (!flag){ //while the flag is false
        
        for (size_t i = 0; i < m_actor.size(); i++){ //need to check to make sure that inputted object is not too close to another object
            x = (rand() % 59) + 1; //rerolls x and y
            y = (rand() % 59) + 1;
            double rad = sqrt(pow(m_actor[i]->getX() - x, 2.0) + pow(m_actor[i]->getY() - y, 2.0));
            if (rad <= 4.0){ //if its too close to another object
                break; //rerolls
        }
            else {
                flag = true; //we found a working coord, set flag to true and stop the loop
            }
        }
    }
}

int MainWorld::move(){
    
    m_ticks++; //increments ticks
    spawnProtester(); //calls the spawnprotester method
    MainWorld::setDisplayText(); //calls the setDisplay method
   // void waterPool(); //calls the waterpool method
    if (m_barrels == 0){ //we have found all of the barrels needed
        advanceToNextLevel();
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    }
    m_tunnelMan->doSomething(); //calls tunnelman's dosomething
    
    if (m_actor.size()> 0) { //if our vector is empty
         vector<Actor*>::iterator it; //create an iterator
         
         //actors doSomething
         for (it = m_actor.begin(); it != m_actor.end(); it++) //call every actor in our vector's doSomething method
         {
             if ((*it)->alive())
             {
                 (*it)->doSomething();
                 
             }
         }
        //removing actors if they're dead
             for (it = m_actor.begin(); it != m_actor.end();){
                 if (!(*it)->alive()){
                     delete *it;
                     it = m_actor.erase(it);
                 }
                 else{
                     it++;
                     
                 }
             }
         }
     
    if (m_tunnelMan->alive() == false){ //if the tunnelman is dead
        playSound( SOUND_PLAYER_GIVE_UP);
        decLives(); //decrease the lives
        return GWSTATUS_PLAYER_DIED; //end the round
    }
    
    return GWSTATUS_CONTINUE_GAME;
}


TunnelMan* MainWorld::getTunnelMan() const {
    return m_tunnelMan;
}


int MainWorld::grid(int x, int y){
    return mapGrid[x][y]; //return the value of the grid at this coord
}

void MainWorld::cleanUp(){
    vector<Actor*>::iterator it; //create an iterator
    it = m_actor.begin(); //initialize the iterator
    while (it != m_actor.end()){ //delete all of the actors
        delete *it;
        it = m_actor.erase(it);
    }
    

    delete m_tunnelMan; //clears the tunnelman
    
    for (int i = 0; i < 64; i++){ //clears the board
        for (int k = 0; k < 60; k++){
            delete m_board[i][k];
        }
    }
}


MainWorld::~MainWorld(){
    delete m_tunnelMan; //clears the tunnelman
    
    vector<Actor*>::iterator it;
    
    it = m_actor.begin(); //initialize the iterator
    while (it != m_actor.end()){
        delete *it;
        it = m_actor.erase(it);
    }
    for (int i = 0; i < 64; i++){ //clears the board
        for (int k = 0; k < 60; k++){
            delete m_board[i][k];
        }
    }
}


void MainWorld::EarthDelete(int x, int y){
    m_board[x][y]->setVisible(false); //calls the setVisible function and sets it to false
    m_board[x][y] = 0; //sets the location to 0
}

void MainWorld::removeEarth(int x, int y){
    for (int i = x; i <= x + 3; i++){
        
           for (int k = y; k <= y + 3; k++){
               
               if (m_board[i][k] != 0){ //if the value at the current coord is not 0 (we havent already removed the earth)
                   EarthDelete(i, k); //call the earthDelete method
                 playSound(SOUND_DIG);
                  
        
               }
           }
       }
}

