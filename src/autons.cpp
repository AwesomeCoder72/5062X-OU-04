#include "catapult.hpp"
#include "main.h"
#include "lemlib/api.hpp"

#include "intake.hpp"
#include "pistons.hpp"

#include "autons.hpp"

void skills() {

    actuate_intake(true);

    spin_cata_auto(100);
    pros::delay(36500); // 39500
    stop_cata_auto();

    chassis.turnTo(0, -59, 1500, true); // turn to move to center

    // chassis.moveToPose(40, -61, 90, 1500, {false, 0, 0.6, 127, 50, 0}); // move into offensive zone

    chassis.turnTo(52.5, -44, 600, true); // turn to diagonal

    chassis.moveToPoint(52.5, -44, 1500, 180);

    actuate_wings(true);

    chassis.turnTo(58, 0, 600, true);

    chassis.moveToPoint(58, -24, 1500, 200); // side push??

    actuate_wings(false);

    chassis.moveToPoint(58,-36, 1500, 160);

    chassis.turnTo(22, -24, 600, true);

    chassis.moveToPoint(22, -24, 1500, 150); //go to line

    chassis.turnTo(22, 0, 600, true);

    chassis.moveToPoint(22,0,700,160);

    actuate_wings(true);

    chassis.turnTo(48, 0, 600, true);

    chassis.moveToPoint(43, -8, 1500, 300); // first push

    actuate_wings(false);

    chassis.moveToPoint(10, 15, 1500, 160);

    actuate_wings(true);


    chassis.moveToPoint(43, 15, 1500, 300); // second push

    chassis.moveToPoint(10, 15, 1500, 160);

    actuate_wings(false);

    chassis.turnTo(44, 50, 600, true);

    chassis.moveToPoint(44, 50, 700);

    chassis.turnTo(60, 24, 600, true);

    actuate_wings(true);

    chassis.moveToPoint(60, 18, 700, 200);

    chassis.moveToPoint(51, 42, 700, 200);

    actuate_wings(false);


    chassis.moveToPoint(60, 18, 700, 200);

    chassis.moveToPoint(51, 42, 700, 200);


}