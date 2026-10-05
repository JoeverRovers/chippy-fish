#include "main.h"
#include "lemlib/api.hpp"
#include <cmath>

#pragma region setup

// Defining ports
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup right_mg({10, 7, 18}, pros::MotorGearset::blue); //ports of the right side, blue cartridges
pros::MotorGroup left_mg({-11,-4, -14}, pros::MotorGearset::blue); //negative means it spins the other way.

pros::ADIDigitalOut piston('A'); //piston port

pros::Motor motor(-20, pros::MotorGearset::blue); //blue cartrdge

// Configure drivetrain - we will need to calibrate this
lemlib::Drivetrain drivetrain(&left_mg,
                              &right_mg,
                              11.75, // track width(inches)
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omniwheels
                              450, // drivetrain rpm
                              2 // horizontal drift
);

pros::Imu imu(12); //IMU port (inertial sensor)

pros::Rotation vertical_encoder(5); //odom wheel port
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0.0, 1); //new_2 omniwheel used for odom I think
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
    motor.move_voltage(voltage);
    wait(time_in_milliseconds);
    motor.move_voltage(0); blockStopper.set_value(false); //hood UP
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
        int dir = master.get_analog(ANALOG_LEFT_Y);
        int turn = master.get_analog(ANALOG_LEFT_X);
        
        right_mg.move(dir - turn);
        right_mg.move(dir + turn);

        pros::delay(20);
    }
}

void autonomous() {
    autontemplate()
}

#pragma endregion real
