#pragma once
#include "main.h"
#include "pros/motors.hpp"

/*
    DEFINES CATAPULT FUNCTIONS
*/

extern pros::MotorGroup Catapult;

extern pros::ADIDigitalIn CataLimit;

extern pros::Distance CataDistance;

extern int cata_distance_away_to_shoot;

void spin_cata_driver(int shootButtonValue, int velocity);
void spin_cata_auto(int velocity);

void stop_cata_auto();

void cata_task_function();