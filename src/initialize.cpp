#include "main.h"
#include "RobotAuto.h"
#include "gui.h"
#include "typedefs.h"


RobotAuto robot;
GameStatus_t GameStatus = Initialize;
AutonPos_t AutonPos = BlueFront;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    Debug::print("Program starting...");
    GameStatus = Initialize;

    pros::Task LiftersTask = pros::Task(LiftersTaskControllerFunc, (void*)(&robot), 10, TASK_STACK_DEPTH_DEFAULT, "IntakeLifter Task");
    pros::Task MotorLockingTask = pros::Task(MotorLockingTaskControllerFunc, (void*)(&robot), 13, TASK_STACK_DEPTH_DEFAULT, "MotorLocking Task");
    pros::Task ScreenHandlerTask = pros::Task(GuiHandler, NULL, TASK_PRIORITY_MIN + 1, TASK_STACK_DEPTH_DEFAULT, "GUI Task");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{}
