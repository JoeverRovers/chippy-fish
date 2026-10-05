#region VEXcode Generated Robot Configuration
from vex import *
#import urandom
import math

# Brain should be defined by default
brain=Brain()

# Robot configuration code
controller_1 = Controller(PRIMARY)
rightfront = Motor(Ports.PORT8, GearSetting.RATIO_6_1, False)
rightmiddle = Motor(Ports.PORT10, GearSetting.RATIO_6_1, False)
rightback = Motor(Ports.PORT18, GearSetting.RATIO_6_1, False)
leftfront = Motor(Ports.PORT11, GearSetting.RATIO_6_1, True)
leftmiddle = Motor(Ports.PORT9, GearSetting.RATIO_6_1, True)
leftback = Motor(Ports.PORT14, GearSetting.RATIO_6_1, True)
intake = Motor(Ports.PORT20, GearSetting.RATIO_6_1, False)
out = Motor(Ports.PORT15, GearSetting.RATIO_18_1, False)
matchload = DigitalOut(brain.three_wire_port.f)
descore = DigitalOut(brain.three_wire_port.h)
hood = DigitalOut(brain.three_wire_port.d)
imu = Inertial(Ports.PORT1)


# wait for rotation sensor to fully initialize
wait(30, MSEC)


# Make random actually random
'''
def initializeRandomSeed():
    wait(100, MSEC)
    random = brain.battery.voltage(MV) + brain.battery.current(CurrentUnits.AMP) * 100 + brain.timer.system_high_res()
    urandom.seed(int(random))
      
# Set random seed 
initializeRandomSeed()
'''


def play_vexcode_sound(sound_name):
    # Helper to make playing sounds from the V5 in VEXcode easier and
    # keeps the code cleaner by making it clear what is happening.
    print("VEXPlaySound:" + sound_name)
    wait(5, MSEC)

# add a small delay to make sure we don't print in the middle of the REPL header
wait(200, MSEC)
# clear the console to make sure we don't have the REPL in the console
print("\033[2J")

#endregion VEXcode Generated Robot Configuration

# ------------------------------------------
# 
# 	Project:      VEXcode Project
#	Author:       VEX
#	Created:
#	Description:  VEXcode V5 Python Project
# 
# ------------------------------------------

# Library imports
from vex import *

# Begin project code

# I got a tiny bit hem hem distracted hem hem

def print_a_pusheen():
    brain.screen.print('''
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⢿⣿⣿⣿⣿⣿⣿⣿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠿⢿⣿⣿⣿⡿⠁⣴⣶⡀⠹⣿⣿⣿⣿⡿⠁⣠⣦⡀⠻⣿⣿⣿⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⡀⠀⡄⢤⣤⡤⢠⣤⣤⣀⣀⣼⣿⣿⣿⣄⠀⡀⠀⡀⠀⣾⣿⣿⣿⡄⢹⣿⣿⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⢁⣴⣔⠿⢟⣼⣿⣮⣉⣥⠚⠿⠿⢿⣿⣿⣿⣿⣿⣿⣴⣿⣴⣷⣴⣿⣿⣿⣿⣷⠀⢿⠿⠿⠿⢿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢁⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⠶⠶⠤⣼⣿⣿⠋⠙⣿⣿⣿⠙⣿⣿⡟⠉⢻⣿⣿⡇⠠⣤⣶⣶⣾
    ⡏⠀⠀⠙⣿⣿⣿⣿⠏⢠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣤⣤⣤⣤⣼⣿⣿⣤⣤⣿⣧⣀⣄⣠⣿⣧⣤⣼⣿⣿⣷⠀⣤⣤⣤⣼
    ⡇⠐⣠⣤⠈⢿⣿⡟⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿
    ⣿⣆⠘⠋⠀⢀⡉⠁⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠸⣿⣿⣿
    ⣿⣿⣧⡀⠑⢿⢡⡆⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿
    ⣿⣿⣿⣿⣷⣤⡀⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⡆⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠀⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣷⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣆⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢀⣾⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠏⢠⣾⣿⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⢁⣴⣿⣿⣿⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠛⢀⣤⣤⣤⣤⡀⠛⠀⣤⣤⣤⣤⣤⣤⣤⡀⠛⠁⣤⣤⣤⣤⣄⠘⠃⢰⣿⣿⣿⣿⣿⣿⣿⣿
    ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣿⣿⣿⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣾⣿⣿⣿⣿⣿⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿
    ''')


# Functions

def intakeIn():
	intake.spin(FORWARD, 100, VOLT)

def intakeOut():
	intake.spin(REVERSE, 100, VOLT)

def intakeStop():
	intake.stop()


def scoreTop():
	out.spin(FORWARD, 200, VOLT)

def scoreBottom():
	out.spin(REVERSE, 100, VOLT)

def scoreStop():
	out.stop()


def dohood(hoodState):
	hood.set(hoodState)

def domatchload(matchLoaderState):
	matchload.set(matchLoaderState)

def dodescore(descoreState):
	descore.set(descoreState)


# Movement Functions
def turnleft(targetDegrees):
	
	# Read the initial orientation from the IMU
    initialOrientation = imu.rotation(DEGREES)
	
    # Calculate the target orientation
    targetOrientation = initialOrientation - targetDegrees
    motorSpeed = 20

    # Continue turning until the robot reaches the target orientation
    uhehlp = imu.rotation(DEGREES)
    while uhehlp >= targetOrientation:
        rightfront.set_velocity(-motorSpeed, RPM)
        rightmiddle.set_velocity(-motorSpeed, RPM)
        rightback.set_velocity(-motorSpeed, RPM)

        leftfront.set_velocity(motorSpeed, RPM)
        leftmiddle.set_velocity(motorSpeed, RPM)
        leftback.set_velocity(motorSpeed, RPM)

        uhehlp = imu.rotation(DEGREES)
        wait(0.1, SECONDS)
    

    # Stop the motors
    rightfront.stop()
    rightmiddle.stop()
    rightback.stop()

    leftfront.stop()
    leftmiddle.stop()
    leftback.stop()
    return


def turnright(targetDegrees):
	
	# Read the initial orientation from the IMU
    initialOrientation = imu.rotation(DEGREES)
	
    # Calculate the target orientation
    targetOrientation = initialOrientation - targetDegrees
    motorSpeed = 20

    # Continue turning until the robot reaches the target orientation
    uhehlp = imu.rotation(DEGREES)
    while uhehlp <= targetOrientation:
        rightfront.set_velocity(motorSpeed, RPM)
        rightmiddle.set_velocity(motorSpeed, RPM)
        rightback.set_velocity(motorSpeed, RPM)

        leftfront.set_velocity(-motorSpeed, RPM)
        leftmiddle.set_velocity(-motorSpeed, RPM)
        leftback.set_velocity(-motorSpeed, RPM)

        uhehlp = imu.rotation(DEGREES)
        wait(0.1, SECONDS)
    

    # Stop the motors
    rightfront.stop()
    rightmiddle.stop()
    rightback.stop()

    leftfront.stop()
    leftmiddle.stop()
    leftback.stop()
    return
	

def forward(cm, moveSpeed) :
    centimeterstodegree = 0.0720384648761 * cm
    
    leftfront.set_velocity(moveSpeed, RPM)
    leftfront.spin_to_position(centimeterstodegree, DEGREES)
    leftmiddle.set_velocity(moveSpeed, RPM)
    leftmiddle.spin_to_position(centimeterstodegree, DEGREES)
    leftback.set_velocity(moveSpeed, RPM)
    leftback.spin_to_position(centimeterstodegree, DEGREES)

    rightfront.set_velocity(moveSpeed, RPM)
    rightfront.spin_to_position(centimeterstodegree, DEGREES)
    rightmiddle.set_velocity(moveSpeed, RPM)
    rightmiddle.spin_to_position(centimeterstodegree, DEGREES)
    rightback.set_velocity(moveSpeed, RPM)
    rightback.spin_to_position(centimeterstodegree, DEGREES)



def backward(cm, moveSpeed) :
    centimeterstodegree = -0.0720384648761 * cm
    
    leftfront.set_velocity(moveSpeed, RPM)
    leftfront.spin_to_position(centimeterstodegree, DEGREES)
    leftmiddle.set_velocity(moveSpeed, RPM)
    leftmiddle.spin_to_position(centimeterstodegree, DEGREES)
    leftback.set_velocity(moveSpeed, RPM)
    leftback.spin_to_position(centimeterstodegree, DEGREES)

    rightfront.set_velocity(moveSpeed, RPM)
    rightfront.spin_to_position(centimeterstodegree, DEGREES)
    rightmiddle.set_velocity(moveSpeed, RPM)
    rightmiddle.spin_to_position(centimeterstodegree, DEGREES)
    rightback.set_velocity(moveSpeed, RPM)
    rightback.spin_to_position(centimeterstodegree, DEGREES)



def pre_autonomous():
    # actions to do when the program starts
    brain.screen.clear_screen()
    brain.screen.print("pre auton code")
    wait(5, SECONDS)

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    print_a_pusheen()

    domatchload(False)
    domatchload(True)
    domatchload(False)
    forward(10, 20)
    turnleft(180)
    dodescore(False)
    dodescore(True)
    dodescore(False)
    turnright(90)
    dohood(False)
    dohood(True)
    dohood(False)

    # place automonous code here

def user_control():
    brain.screen.clear_screen()
    # place driver control in this while loop
    while True:

        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)
pre_autonomous()
autonomous()
