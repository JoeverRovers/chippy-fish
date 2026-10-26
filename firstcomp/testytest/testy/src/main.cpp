#include "main.h"
#include "lemlib/api.hpp"
#include <cmath>

#pragma region setup

// Defining ports
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup right_mg({10, 2, 8}, pros::MotorGearset::blue); //ports of the right side, blue cartridges
pros::MotorGroup left_mg({-20, -14, -17}, pros::MotorGearset::blue); //negative means it spins the other way.
// port 15, 16 = bad
// port 5 and 6 are bad?!
// port 9 bad??
// need to update the colours

pros::ADIDigitalOut piston('A'); //piston port

pros::Motor rightliftmotor(-1, pros::MotorGearset::red); // red
pros::Motor lefttliftmotor(11, pros::MotorGearset::red); //red

// Configure drivetrain - we will need to calibrate this
lemlib::Drivetrain drivetrain(&left_mg,
                              &right_mg,
                              11.75, // track width(inches)
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omniwheels
                              360, // drivetrain rpm
                              2 // horizontal drift
);

pros::Imu imu(4); //IMU port (inertial sensor)

pros::Rotation odom(12); //odom wheel port
// pros::Rotation liftrotationsensor(4); //rotation sensor
lemlib::TrackingWheel vertical_tracking_wheel(&odom, lemlib::Omniwheel::NEW_2, 0.0, 1); //new_2 omniwheel used for odom I think
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2 (we don't have one)
                            nullptr ,// horizontal tracking wheel 1 (we don't have one)
                            nullptr, // horizontal tracking wheel 2 (we don't have one)
                            &imu // inertial sensor
);

//calibrate this
lemlib::ControllerSettings lateral_controller(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range (inches)
                                              100, // small error range timeout (milliseconds)
                                              3, // large error range (inches)
                                              500, // large error range timeout (milliseconds)
                                              20 // maximum acceleration (slew)
);

// :(
lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range (inches)
                                              100, // small error range timeout (milliseconds)
                                              3, // large error range (inches)
                                              500, // large error range timeout (milliseconds)
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);

#pragma endregion setup


void initialize() {
    pros::lcd::initialize();
    pros::lcd::print(0, "19109G");
    right_mg.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    left_mg.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    rightliftmotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    lefttliftmotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);

    imu.reset();

    while(imu.is_calibrating()){
        pros::delay(10);
    }
    chassis.calibrate(); 
    chassis.setPose(0, 0, 0);
    // while (true) {
    //     lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
    //     pros::lcd::print(0, "x: %f", pose.x); // print the x position
    //     pros::lcd::print(1, "y: %f", pose.y); // print the y position
    //     pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
    //     pros::delay(10);

    // }
    pros::delay(10);

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


//setup functions
void turntoheading(int direction_in_degrees, int time_in_milliseconds) {
    chassis.turnToHeading(direction_in_degrees, time_in_milliseconds); pros::delay(time_in_milliseconds);
}
void movetopoint(int x_in_inches, int y_in_inches, int time_in_milliseconds) {
    chassis.moveToPoint(x_in_inches, y_in_inches, time_in_milliseconds); pros::delay(time_in_milliseconds);
}
void wait(int time_in_milliseconds) {
    pros::delay(time_in_milliseconds);
}
void movemotor(int voltage, int time_in_milliseconds) {
    wait(time_in_milliseconds);
}
void retractpiston(pros::ADIDigitalOut piston) {
    piston.set_value(false);
}
void extendpiston(pros::ADIDigitalOut piston) {
    piston.set_value(true);
}


void autontemplate() {
    /*
    any comments you have. you can have more than 2 steps

    0. starting position (x, y)
    1. step 1 (x, y)
    2. step 2 (x, y)
    */

    #pragma region 0. starting position
    //setup
    #pragma endregion 0. starting position
    
	#pragma region 1. description - (x, y, direction) - 0 seconds elapsed - state of pistons
	//whatever you need here
    #pragma endregion 1. description - (x, y, direction) - 0 seconds elapsed - state of pistons
    
	/*
	final:
	position: (x, y, direction)
	time: 35 seconds elapsed
	hood UP matchload UP
	*/

}

#pragma region real

void opcontrol() { 
    while (true) {
        //arcade drive from coding workshop I don't know which one youall like
        // printf("right\n", rightliftmotor.get_position());
        // printf("leftt\n", lefttliftmotor.get_position());
        pros::lcd::initialize();
        pros::lcd::print(1, "hi");
        // pros::lcd::print(2, std::to_string(rightliftmotor.get_position()));

        int dir = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_RIGHT_X);
        
        right_mg.move(dir - turn);
        left_mg.move(dir + turn);
        
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
            rightliftmotor.move(127);
            lefttliftmotor.move(127);
        }
        else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
            rightliftmotor.move(-127);
            lefttliftmotor.move(-127);
        }
        else{
            rightliftmotor.move(0);
            lefttliftmotor.move(0);
        }

        pros::delay(20);
    }
}

void autonomous() {
    autontemplate();
}

#pragma endregion real
