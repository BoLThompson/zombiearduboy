#ifndef PLAYER_H
#define PLAYER_H
#include "global.h"

namespace Player {

    //32 bit coordinates, low byte is subpixels
    extern Pos pos;

    //used for air movement, low byte is subpixels per frame
    extern Speed speed;

    //facing direction
    extern bool faceRight;

    //pointer to the code which is executed on fire
    extern void (*fireRoutine)();

    //pointer to the code which is executed next frame
    extern void (*stepRoutine)();

    //pointer to the code for drawing on the screen
    extern void (*drawRoutine)();

    extern uint8_t fireTimer;

    //idle step
    void idleStep();
    //in air
    void jumpStep();

    //normal firing action
    void fireNormal();

    void jumpAction();
    void shootAction();

    void init();
    void draw();
};

#endif