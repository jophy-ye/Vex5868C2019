#include "main.h"

#include "Config.h"
#include "RobotAuto.h"
#include "typedefs.h"
#include "Debug.h"

extern RobotAuto robot;
extern GameStatus_t GameStatus;
extern AutonPos_t AutonPos;

void TestFunction()
{
    robot.SlideDistance(10, 127, true);
}

// Autonomous Action for starting position: Blue_Front
void AutonBlueFront()
{

}

// Autonomous Action for starting position: Red_Front
void AutonRedFront()
{
    /**
     * Go forward and suck all cubes (there are four)
     */
    robot.SetIntakeMode(1);
    robot.MoveDistance(70, 100, true);
    pros::delay(200);
}

// Autonomous Action for starting position: Blue_Back
void AutonBlueBack()
{

}

// Autonomous Action for starting position: Red_Back
void AutonRedBack()
{

}

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
void autonomous()
{
    GameStatus = Autonomous;
    Debug::StatLog("$ Autonomous Starting");

    TestFunction();

    switch(AutonPos)
    {
        case BlueFront: AutonBlueFront(); break;
        case RedFront: AutonRedFront(); break;
        case BlueBack: AutonBlueBack(); break;
        case RedBack: AutonRedBack(); break;
    }
}
