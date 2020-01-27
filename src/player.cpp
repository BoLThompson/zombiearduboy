#include "player.h"

//player initialization
void Player::init() {
  x = (FIELD_WIDTH/8)<<8;
  y = ((FIELD_HEIGHT/4)*3)<<8;
  stepRoutine = &Player::idle;
  fireRoutine = &Player::fireNormal;
  faceRight = true;
}

void Player::step() {
  (this->*stepRoutine)();

  //update player bullets
  bullets.step();
}

void Player::idle() {

  //walking and moonwalking
  
  //if holding Left
  if (ab.pressed(LEFT_BUTTON)) {

    //at least move half a pixel
    x-=_BV(7);

    //if we're not shooting,
    if (!ab.pressed(FIRE_BUTTON)) {

      //turn to the left
      faceRight = false;

      //move an additional half pixel
      x-=_BV(7);
    }
    //if we are shooting, only move the extra half pixel if we're facing the right way
    else if (!faceRight) x-=_BV(7);

  }

  //and all that again for the right
  if (ab.pressed(RIGHT_BUTTON)) {
    x+=_BV(7);
    if (!ab.pressed(FIRE_BUTTON)) {
      faceRight = true;
      x+=_BV(7);
    }
    else if (faceRight) x+=_BV(7);
  }

  //shoot maybe?
  if (ab.justPressed(FIRE_BUTTON)) {
    (this->*fireRoutine)();
  }
}

void Player::fireNormal() {
  struct Bullet *newBullet = bullets.append();

  newBullet->x = x;
  newBullet->y = y - (5<<8);
  newBullet->dir = (faceRight ? RIGHT : LEFT);
  newBullet->faction = GOOD;
  newBullet->stepRoutine = &Bullet::normalStep;
}

void Player::draw() {
  uint8_t dispX = x>>8;
  uint8_t dispY = y>>8;
  ab.fillRect(dispX-PLAYER_WIDTH/2+1,dispY-PLAYER_HEIGHT+1, PLAYER_WIDTH-2, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(dispX-PLAYER_WIDTH/2, dispY-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
  ab.drawRect(dispX-(faceRight==true ? 0 : GUN_WIDTH), dispY-(PLAYER_HEIGHT/3)*2, GUN_WIDTH, GUN_HEIGHT, WHITE);

  bullets.draw();
}

// //heheheh
// struct Bullet * BulletList::getHead() {
//   return head;
// }

// //pfahaha
// struct Bullet * BulletList::getTail() {
//   return tail;
// }

//put a new node at the end
struct Bullet * BulletList::append() {

  //new bullet to add
  struct Bullet *temp = new Bullet;
  
  //set that shit's next pointer to NULL, it's going to be the tail
  temp->next = NULL;

  temp->timer = 0;

  if (head == NULL) {
    head = temp;
    tail = temp;
  }
  else {
    tail->next=temp;
    tail = temp;
  }

  return temp;
}

void BulletList::step() {
  struct Bullet *curNode = head;

  while (curNode != NULL) {
    curNode->step();
    curNode = curNode->next;
  }
}

void BulletList::draw() {

  //get the first bullet
  struct Bullet *curNode = head;

  while( curNode != NULL) {
    curNode->draw();
    curNode = curNode->next;
  }
}

void Bullet::step() {
  (this->*stepRoutine)();
}

void Bullet::normalStep() {
  if (dir == RIGHT) {
    x+=_BV(8);
  }
  else x-=_BV(8);
  timer++;
  if (timer == 0) {
    //destroy self
  }
}

void Bullet::draw() {
  uint8_t dispX = x>>8;
  uint8_t dispY = y>>8;

  ab.fillRect(dispX-1, dispY-1, 3, 3, WHITE);
}