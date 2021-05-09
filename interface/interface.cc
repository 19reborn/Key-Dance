#include "interface.h"
#include <cstdio>

extern InterfaceState state;

InterfaceTest::InterfaceTest() {
    this->pos = {screenWidth/2.0, 0.0};
}

void InterfaceTest::init() {

}

void InterfaceTest::update() {
    this->pos.y += 2;
}

void InterfaceTest::draw() {
    DrawCircleV(this->pos, 50, MAROON);
}