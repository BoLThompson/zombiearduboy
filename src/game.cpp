#include "game.h"
#include "player.h"

Player player; //haha lol

//title screen
  //maybe a difficulty toggle
  //sound toggle?
  //button layout

//game initialization
void Game::init() {

  //instantiate the player
  player.init();
}

//game loop
void Game::loop() {
  ab.drawRect(0,0,128,64,WHITE);

  //do player shit
  player.step();

  //do enemy shit

  
  player.draw();
}

//director
  //difficulty +
    //wave
      //certain amount of difficulty points are allotted for enemies to be spawned
      //enemy groups are selected
      //enemy group spawns are consumed as possible
      //enemy group spawns are fully consumed and all enemies are defeated

//death
  //show score
  //try again?

//contact details