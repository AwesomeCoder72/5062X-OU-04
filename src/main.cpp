/*
	API INCLUDES
*/

#include "main.h"
#include "lemlib/api.hpp"

/*
	USER-MADE INCLUDES
*/

#include "catapult.hpp"
#include "autons.hpp"
#include "intake.hpp"
#include "pistons.hpp"


/*
	MOTOR PORT DEFINITIONS
*/

#define CATA_5_5W_MOTOR_PORT 1
#define CATA_11W_MOTOR_PORT 3

#define INTAKE_MOTOR_PORT 12

#define DRIVE_LB_PORT 6
#define DRIVE_LM_PORT 7
#define DRIVE_LF_PORT 8

#define DRIVE_RB_PORT 3
#define DRIVE_RM_PORT 4
#define DRIVE_RF_PORT 5

/*
	IMU PORT DEFINITIONS
*/

#define IMU_PORT 18

/*
	SMART SENSOR PORT DEFINTIONS
*/

#define CATA_DISTANCE_SENSOR_PORT 20

/*
	DIGITAL PORT DEFINITIONS
*/

#define CATA_LIMIT_SWITCH_PORT 'H'
#define AUTON_POT_PORT 'E'
#define INTAKE_ACTUATOR_PORT 'G'
#define WINGS_ACTUATOR_PORT 'F'

/*
	CONTROLLER BUTTON DEFINITIONS
*/

#define AUTON_SELECT_BUTTON pros::E_CONTROLLER_DIGITAL_UP

#define CATA_LAUNCH_ONCE_BUTTON pros::E_CONTROLLER_DIGITAL_R1
#define INTAKE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L2

#define ACTUATE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_X
#define ACTUATE_WINGS_BUTTON pros::E_CONTROLLER_DIGITAL_A

#define UP_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_LEFT
#define DOWN_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

/*
	CONTROLLER DEFINITION
*/

pros::Controller controller (pros::E_CONTROLLER_MASTER);

/*
	MOTOR INITIALIZATIONS
*/

pros::Motor Catapult_5_5W(CATA_5_5W_MOTOR_PORT, MOTOR_GEARSET_18, false);
pros::Motor Catapult_11W(CATA_11W_MOTOR_PORT, MOTOR_GEARSET_18, true);

pros::MotorGroup Catapult({Catapult_5_5W, Catapult_11W});

pros::Motor Intake(INTAKE_MOTOR_PORT, MOTOR_GEARSET_6, true);

/*
	SENSOR INITIALIZATIONS
*/

pros::ADIDigitalIn CataLimit(CATA_LIMIT_SWITCH_PORT);
pros::ADIAnalogIn AutonPot(AUTON_POT_PORT);
pros::Distance CataDistance(CATA_DISTANCE_SENSOR_PORT);

/*
	PISTON INITIALIZATIONS
*/

pros::ADIDigitalOut IntakeActuator(INTAKE_ACTUATOR_PORT);
pros::ADIDigitalOut WingsActuator(WINGS_ACTUATOR_PORT);

/*
	LEMLIB DRIVE MOTOR INITIALIZATIONS
*/

pros::Motor drive_lb(DRIVE_LB_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor drive_lm(DRIVE_LM_PORT, pros::E_MOTOR_GEARSET_06, true);
pros::Motor drive_lf(DRIVE_LF_PORT, pros::E_MOTOR_GEARSET_06, true);

pros::Motor drive_rb(DRIVE_RB_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor drive_rm(DRIVE_RM_PORT, pros::E_MOTOR_GEARSET_06, false);
pros::Motor drive_rf(DRIVE_RF_PORT, pros::E_MOTOR_GEARSET_06, false);

/*
	LEMLIB DRIVE MOTOR GROUP INITIALIZATIONS
*/

pros::MotorGroup drive_left({drive_lb, drive_lm, drive_lf});
pros::MotorGroup drive_right({drive_rb, drive_rm, drive_rf});

/*
	LEMLIB DRIVE IMU INITIALIZATION
*/

pros::Imu inertial_sensor(IMU_PORT);

/*
	LEMLIB DRIVE Drivetrain INITIALIZATION
*/

lemlib::Drivetrain drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    11, // track width
    3.25, // wheel diameter // 3.175
    360, // wheel rpm
	10 // chase power
};

/*
	LEMLIB DRIVE OdomSensors INITIALIZATION
*/

lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

/*
	LEMLIB DRIVE LATERAL_PID (forward/backward) INITIALIZATION
*/

lemlib::ControllerSettings lateralPIDController {
    8, // kP
    0, // kI
	30, // kD
	0, // antiWindUp ???
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};

/*
	LEMLIB DRIVE ANGULAR_PID (left/right) INITIALIZATION
*/
 
lemlib::ControllerSettings angularPIDController {
    4.2, // kP
	0, // kI
    40, // kD
	0, // antiWindUp ???
    3, // smallErrorRange
    100, // smallErrorTimeout
    10, // largeErrorRange
    500, // largeErrorTimeout
    40 // slew rate
};

/*
	LEMLIB DRIVE CHASSIS CONSTRUCTOR INITIALIZATION
*/

lemlib::Chassis chassis(drivetrain, lateralPIDController, angularPIDController, sensors);

/*
	CATAPULT CONFIG
*/

int cata_distance_away_to_shoot = 30;


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	chassis.calibrate();


	// pros::Task CataTask(cata_task_function);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

ASSET(test1_txt);

void autonomous() {
    chassis.setPose(-50, -56, 240);
	skills();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

int match_load_speed = 200;


void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(1);
	pros::Motor right_mtr(2);

	while (true) {

		chassis.arcade(127, 127, 0.0);

		spin_cata_driver(controller.get_digital(DIGITAL_R1), match_load_speed);


		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int left = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_Y);

		left_mtr = left;
		right_mtr = right;

		pros::delay(20);
	}
}
