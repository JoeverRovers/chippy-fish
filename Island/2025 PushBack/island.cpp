#include "main.h"
#include "lemlib/api.hpp"
#include <cmath>

// Defining ports
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::MotorGroup right_mg({10, 7, 18}, pros::MotorGearset::blue);
pros::MotorGroup left_mg({-11,-4, -14}, pros::MotorGearset::blue);  

pros::ADIDigitalOut blockStopper('B');
pros::ADIDigitalOut matchLoader('C');
pros::ADIDigitalOut descore('A');

pros::Motor intake(-20, pros::MotorGearset::blue);
pros::Motor score(15,pros::MotorGearset::blue);

// configure drivetrain
lemlib::Drivetrain drivetrain(&left_mg, // left motor group
                              &right_mg, // right motor group
                              11.75, // 11.725 nch track width?? or 11.75
                              lemlib::Omniwheel::NEW_325, // using new 3.25" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

pros::Imu imu(12);

pros::Rotation vertical_encoder(5);

lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, 0.0, 1);

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel 1
                            nullptr, // vertical tracking wheel 2, set to nullptr as it doesn't exist lol
                            nullptr ,// horizontal tracking wheel 1, which doesn't exist
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// 5/10
lemlib::ControllerSettings lateral_controller(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// 3 kP, 10 kD
lemlib::ControllerSettings angular_controller(3, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);



// Functions
void intakeIn(){
    intake.move_voltage(12000);
}

void intakeOut(){
    intake.move_voltage(-12000);
}

void intakeStop(){
    intake.move(0);
}

void scoreTop(){
    score.move_voltage(12000);
}

void scoreBottom(){
    score.move_voltage(-12000);
}

void scoreStop(){
    score.move(0);
}

void block(bool blockStopperState){
    blockStopper.set_value(blockStopperState);
}

void matchLoad(bool matchLoaderState){
    matchLoader.set_value(matchLoaderState);
}

void hook(bool descoreState){
    descore.set_value(descoreState);
}

int side = -1; //left side/right side auto, 1 = left

void auton2() {
	/*
	auton skills based off of skills coordinates
	like last function I did a picture again and, the numbers before the park should be fine because I copied them off of skills :sweatsmile: but the park might be extremely off :333
	I also extended everything by one second
	starting at not (0, 0) is a bit cursed so I guess start at (0, 0) :thubup:
	I'm going to assume park is (-15, -15)
	apparently #region does not work because that is for C#!!! apparently it is #pragma region and endregion for c++, my'bad
	note that like last time, this is for the left side
	and note to self that we are an s bot and do not need to turn to get from matchload to goal
	
	0. starting position (0, 0)
	1. move to matchload part 1 (0, 33)
	2. move to matchload part 2 and intake (-16, 33)
	3. score (22, 33)
	4. now for this I don't want to deal with non multiple of 90 angles or some nice ish angles with trig for that matter so uh let's do some weird zigzag thing :???<:DDDDD:
	    1. park part 1 (10, 33)
	    2. park part 2 (10, 15)
	    3. park part 3 (-15, 15)
	    4. park part 4 (-15, -15)
	
	YIPPEE
	*/
	
	#pragma region 0. starting position!!!
	
    blockStopper.set_value(true); //hood DOWN
	matchLoader.set_value(true); //matchload DOWN
	chassis.setPose(0 * side, 0, 0); //start at (0, 0)
	
	#pragma endregion 0. starting position!!!
	
	
	
	#pragma region 1. move to matchload PART 1!!! - (0, 0, 0) - 0 seconds elapsed - hood DOWN matchload DOWN
	
	chassis.moveToPoint(0 * side, 33, 3000); pros::delay(3000); //moving to (0, 33) in 3 seconds
	
	#pragma endregion 1. move to matchload PART 1!!! - (0, 0, 0) - 0 seconds elapsed - hood DOWN matchload DOWN
	
	
	
	#pragma region 2. intake!!! - (0, 33, 0) - 3 seconds elapsed - hood DOWN matchload DOWN
	
	//1. move to matchload
	chassis.turnToHeading(-90 * side, 1500); pros::delay(1500); //turn left in 1.5 seconds
	chassis.moveToPoint(-20 * side, 33, 3000); pros::delay(3000); //moving to matchload (-20, 33) in 3 seconds, ramming into the matchload more
	
	//2. intake
	//note, our matchloader should be down here
    intake.move(100); pros::delay(4000); intake.move(0); //intake for 4 seconds
	
	#pragma endregion 2. intake!!! - (0, 33, 0) - 3 seconds elapsed - hood DOWN matchload DOWN
	
	
	
	#pragma region 3. score!!! - (-16, 33, -90) - 11.5 seconds elapsed - hood DOWN matchload DOWN
	
	//1. move to goal
	chassis.moveToPoint(22 * side, 33, 3000, {.forwards=false}); pros::delay(3000); //moving to goal (22, 33) in 3 seconds, make sure to go backwards!
	
	//2. manage pistons and stuff - wee can move hood function before the step 1 if it bumps into the goal
    blockStopper.set_value(false); //hood UP
	matchLoader.set_value(false); //matchload UP
	pros::delay(1000); //wait is it supposed to like wait one second for this or something
	
	//3. score!
	//scoreing for 4 seconds
	intake.move(100); score.move(100); 
	pros::delay(4000); 
	intake.move(0); score.move(0);
	
	#pragma endregion 3. score!!! - (-16, 33, -90) - 11.5 seconds elapsed - hood DOWN matchload DOWN
	
	
	
	#pragma region 4. park!!! - (22, 33, -90) - 19.5 seconds elapsed - hood UP matchload UP
	
	//1. park part 1 (10, 33)
	chassis.moveToPoint(10 * side, 33, 2000); pros::delay(2000); //moving to (10, 33) in 2 seconds

	chassis.turnToHeading(-180 * side, 1500); pros::delay(1500);
	chassis.moveToPoint(10 * side, 20, 2000); pros::delay(2000);
	chassis.turnToHeading(-90 * side, 1500); pros::delay(1500);
	chassis.moveToPoint(-13 * side, 15, 2000); pros::delay(3000);

	chassis.moveToPoint(-14.674 * side, 12.371, 1500); pros::delay(1500);
	chassis.moveToPoint(-15.53 * side, 4.429, 1500); pros::delay(1500);
	chassis.moveToPoint(-16.141 * side, -5.59, 1500); pros::delay(1500);
	chassis.moveToPoint(-16.517 * side, -18.696, 1500); pros::delay(1500);

	/*
	//2. park part 2 (10, 15)
	chassis.turnToHeading(-180 * side, 1500); pros::delay(1500); //turn left in 1.5 seconds
	chassis.moveToPoint(10 * side, 15, 2000); pros::delay(3000); //moving to (10, 15) in 3 seconds
	
	//3. park part 3 (-15, 15)
	chassis.turnToHeading(-90 * side, 1500); pros::delay(1500); //turn right in 1.5 seconds
	chassis.moveToPoint(-15 * side, 15, 2000); pros::delay(3000); //moving to (-15, 15) in 3 seconds
	
	//4. park part 4 (-15, -15)
	//first we turn just a bit to an angle such that both sleds go into the park
	chassis.turnToHeading(-175 * side, 1500); pros::delay(1500); //turn left in 1.5 seconds
	chassis.moveToPoint(-19 * side, -19, 3000); pros::delay(3000); //park!!!
	*/
	
	#pragma endregion 4. park!!! - (22, 33, -90) - 19.5 seconds elapsed - hood UP matchload UP
	
	
	
	#pragma region final
	/*
	final:
	position: (-15, -15, -180)
	time: 35 seconds elapsed
	hood UP matchload UP
	*/
	
	
	/* title template:
	#pragma region #. title - (x, y, thet) - # seconds elapsed - hood d matchload d
	#pragma endregion  
	*/
	#pragma endregion final
	
}

void auton() {
    /*
    I just uh copy and pasted all the settings above erm yeah
    there should be a reference picture in the island with the steps numbered also
    [how big is our bot again???] the numbers might be extremely off so please pardon that :3
    did not think to plot intermediate steps on the jerryio so uhh stuff like go back a bit part I eyeballed that heheheh :333 and are not included with pictur
    I think #region collapses the code underneath it in vs code which helps to organize wall of text but I am not sure, each region has the step, where the bot should be, how much time has passed and state of pistons if you reach here
    all measures here in inches
    
    0. starting position (-48, 12)
    1. move so that the bot is directly right/forward to the matchload(-48, 46.5)
    2. turn and face the matchloader and then go there and intake (-60, 46.5)
    3. go towards longgoal and score (-27, 46.5)
    4. turn and go to park (-61, 31)
    5. park (-61, -3)
    
    yayay :doublethumbthumbup:
    */
    
    // #region 0. starting position!!!
    blockStopper.set_value(false); //hood DOWN
	matchLoader.set_value(false); //matchload DOWN
	chassis.setPose(-48, 12, 0); //is this okay or a bit goofber
	
	// #region 1. moving to matchload part 1!!! - (-48, 12, 0) - 0 seconds elapsed - hood DOWN matchload DOWN
	chassis.moveToPoint(-48, 46.5, 2000); //moving to (-48, 46.5) in 2 seconds
	
	// #region 2. intake!!! - (-48, 46.5, -90) - 2 seconds elapsed - hood DOWN matchload DOWN
	
	//1. move there
	chassis.turnToPoint(-60, 46.5, 500); //turn to matchload in 0.5 seconds
	chassis.moveToPoint(-60, 46.5, 2000); //moving to matchload(-60, 46.5) in 2 seconds
	
	//2. intake
	//note, our matchloader should be down here
    intake.move(100); pros::delay(4000); intake.move(0); //start intaking for 4 seconds
    
    // #region 3. score!!! - (-60, 46.5, 90) - 8.5 seconds elapsed - hood DOWN matchload DOWN
    
    //1) go to goal
    
	matchLoader.set_value(true); //matchload UP
    chassis.moveToPoint(-27, 46.5, 2000); //moving to goal(-27, 46.5) in 2 seconds 
    
	//2) score!!! - (-27, 46.5, 90) - 10.5 seconds elapsed
    blockStopper.set_value(true); //hood UP
	//scoreing for 4 seconds
	intake.move(100); score.move(100); 
	pros::delay(4000); 
	intake.move(0); score.move(0);
	//ehh should I put the hood down nah I am a bit lazy
	
	// #region 4. go park!!! - (-27, 46.5, 90) - 14.5 seconds elapsed - hood UP matchload UP
	
    //I think we can either just movetopose it, turn then move, or go back and then turn then move, I guess I will write all 3 and comment out the other two
	
	//a. movetoposing
	chassis.moveToPose(-61, 31, 180, 4000); //moving to preparetopark position(-61, 31) and we should end up facing the park in 4 seconds
	
	/*
    //b. turn then move
    chassis.turnToPoint(-61, 31, 500); //turn to park in 0.5 seconds
	chassis.moveToPoint(-61, 31, 3000); //moving to park(-61, 31) in 3 seconds
	
	//c. go back, turn then move
	chassis.moveToPose(-30, 46.5, 90, 1000); //moving back a bit(3in) while still facing the goal hopefully in 1 second
    chassis.turnToPoint(-61, 31, 500); //turn to park in 0.5 seconds
	chassis.moveToPoint(-61, 31, 2000); //moving to park(-27, 46.5) in 2 seconds
	
	//note, this is not needed if we are using movetopose
    chassis.turnToPoint(-27, 46.5, 500); //turn to goal in 0.5 seconds
    */
    
    // #region 5. park!!! - (-61, 31, 180) - 18.5 seconds elapsed - hood UP matchload UP
    chassis.turnToPoint(-61, 31, 4); //go park - I set this a few inches beyond the center of the park to push blocks out and because, what if it doesn't go through, taking 4 seconds
	
	// #region 6. final thoughta!!! probably!!!
	/*
	final:
	position: (-61, 31, 4)
	time: 22.5 seconds elapsed
	hood UP matchload UP
	*/
	
	//WAT DER PHYSICSSSSSSSSSS
    
}
