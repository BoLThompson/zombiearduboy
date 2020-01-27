#include "player.h"

extern Player player;

//player initialization
void Player::init() {
  x = (FIELD_WIDTH/8)<<8;
  y = TEMP_GROUND<<8;
  stepRoutine = &Player::idleStep;
  fireRoutine = &Player::fireNormal;
  faceRight = true;
}

void Player::step() {
  (this->*stepRoutine)();

  //update player bullets
  bullets.step();
}

void Player::idleStep() {

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
  shootAction();

  //possibly jump
  jumpAction();
}

void Player::jumpStep() {
  y+= vSpeed;
  vSpeed = min(vSpeed+64,5<<8);

  x+= hSpeed;

  if (ab.pressed(RIGHT_BUTTON)) faceRight = true;
  else if (ab.pressed(LEFT_BUTTON)) faceRight = false;

  if (y >= TEMP_GROUND<<8) {
    y = TEMP_GROUND<<8;
    stepRoutine = &Player::idleStep;
  }

  shootAction();
}

void Player::shootAction() {
  if (ab.justPressed(FIRE_BUTTON)) {
    (this->*fireRoutine)();
  }
}

void Player::jumpAction() {
  if (ab.justPressed(JUMP_BUTTON)) {
    stepRoutine = &Player::jumpStep;
    vSpeed = -3*(_BV(8));
    if (ab.pressed(RIGHT_BUTTON)) {
      hSpeed = _BV(8);
    }
    else if (ab.pressed(LEFT_BUTTON)) {
      hSpeed = _BV(8)*-1;
    }
    else hSpeed=0;
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
  uint16_t dispX = x>>8;
  uint16_t dispY = y>>8;
  ab.fillRect(dispX-PLAYER_WIDTH/2+1,dispY-PLAYER_HEIGHT+1, PLAYER_WIDTH-2, PLAYER_HEIGHT-2, BLACK);
  ab.drawRect(dispX-PLAYER_WIDTH/2, dispY-PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
  ab.drawRect(dispX-(faceRight==true ? 0 : GUN_WIDTH), dispY-(PLAYER_HEIGHT/3)*2, GUN_WIDTH, GUN_HEIGHT, WHITE);

  bullets.draw();
}

struct BulletList * Player::getBulletList() {
  struct BulletList *value = &bullets;
  return value;
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
    struct Bullet *nextNode = curNode->next;
    curNode->step();
    curNode = nextNode;
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
    x+=_BV(10);
  }
  else x-=_BV(10);
  timer++;
  if (timer == 0) {
    destroy();
  }
}

void Bullet::destroy() {
  struct Bullet *curNode = (player.getBulletList())->head;
  
  //if we're the head,
  if (curNode == this) {
    (player.getBulletList())->head = next;
  }

  //otherwise
  else {

    //we need to look for the first node before us
    while (curNode->next != this) {
      curNode = curNode->next;
    }

    //now curNode is our parent
    curNode->next = next;

    //we've cut ourselves out of the chain, tadah
  }

  delete this;
}

void Bullet::draw() {
  uint16_t dispX = x>>8;
  uint16_t dispY = y>>8;

  ab.fillRect(dispX-1, dispY-1, 3, 3, WHITE);
}