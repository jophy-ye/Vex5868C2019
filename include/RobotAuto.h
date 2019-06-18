/*
The class for autonomous movements of the robot
*/

#ifndef _ROBOT_AUTO_MOVEMENT_H_
#define _ROBOT_AUTO_MOVEMENT_H_

#include "api.h"

#include "Constants.h"
using namespace CONSTANTS;
#include "Robot.h"

class RobotAuto : public Robot
{
private:
    // how many CM each motor has moved
    double LeftMotorMovedCM, RightMotorMovedCM;

public:
    /*
    The constructor function of the class "RobotMovement"

    Input: (none)
    Output: (none)
    */
    RobotAuto(): Robot() {};

    /*
    Function for the whole robot to stop

    Input: (none)
    Output: (none)
    */
    void Stop();

    /*
    Function to reset the motor's absolute position

    Input: (none)
    Output: (none)
    */
    void MotorReset();

    /*
    Function for the whole robot to start moving

    Input:
        power (double)      :  The power for the motor (-127 ~ 127)
    Output: (none)

    #Note: if you want to the robot to move with other condition other than distance,
            apply this function regularly with that condition.
        Ex:     RobotAuto::Stop();
                while ([CONDITION])
                {RobotAuto::Move(127);}
                RobotAuto::Stop();
    */
    void Move(double power = 127);

    /*
    Function for the whole robot to move a certain distance

    Input:
        dist (double)       :  The desire distance in centimeters(cm)
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)

    #Note1: dist is supposed to be positive, please set the rotate direction through power
        (negative dist will not affect the direction)
    */
    void MoveDistance(double dist, double power = 127, bool OptimizedStop = false);

    /*
    Function for the whole robot to slide left and right

    Input:
        dist (double)       :  The desire distance in centimeters(cm)
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)

    #Note1: a minus degree will result in left slide, and vise versa.
    #Note2: dist is supposed to be positive, please set the rotate direction through power
        (negative dist will not affect the direction)
    */
    void SlideDistance(double dist, double power = 127, bool OptimizedStop = false);

    /*
    Function for the whole robot to swing turn

    Input:
        power (double)      :  The power for the motor (-127 ~ 127)
    Output: (none)

    #Note: if you want to the robot to turn with other condition other than distance,
            apply this function regularly with that condition.
        Ex:     RobotAuto::Stop();
                while ([CONDITION])
                {RobotAuto::Turn(127);}
                RobotAuto::Stop();
    */
    void Turn(double power = 127);

    /*
    Function for the whole robot to swing turn

    Input:
        degree (double)     :  The desire degree
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)

    #Note1: a minus degree will result in left swing turn, and vise versa.
    #Note2: degree is supposed to be positive, please set the rotate direction through power
        (negative dist will not affect the direction)
    */
    void TurnDegree(double degree, double power = 127, bool OptimizedStop = false);

    /*
    The default destructor of the class "RobotMovement"

    Input: (none)
    Output: (none)
    */
    ~RobotAuto();
};

#endif
