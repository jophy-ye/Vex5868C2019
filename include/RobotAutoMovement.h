/*
The class for autonomous movements of the robot
*/

#ifndef _ROBOT_AUTO_MOVEMENT_H_
#define _ROBOT_AUTO_MOVEMENT_H_

#include "api.h"

#include "Constants.h"
using namespace CONSTANTS;
#include "Equipment.h"

class RobotAutoMovement : public Equipment
{
public:
    /*
    The constructor function of the class "RobotMovement"

    Input: (none)
    Output: (none)
    */
    RobotAutoMovement(): Equipment() {};

    /*
    Function for the whole robot to stop

    Input: (none)
    Output: (none)
    */
    void Stop();

    /*
    Function for the whole robot to start moving

    Input:
        power (double)      :  The power for the motor (-127 ~ 127)
    Output: (none)
    */
    void Move(double power = 127);

    /*
    Function for the whole robot to move a certain distance

    Input:
        dist (double)       :  The desire distance in centimeters(cm)
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)
    */
    void MoveDistance(double dist, double power = 127, bool OptimizedStop = false);

    /*
    Function for the whole robot to slide left and right

    Input:
        dist (double)       :  The desire distance in centimeters(cm)
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)
    */
    void SlideDistance(double dist, double power = 127, bool OptimizedStop = false);

    /*
    Function for the whole robot to turn

    Input:
        degree (double)     :  The desire degree
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)
    */
    void Turn(double degree, double power = 127, bool OptimizedStop = false);

    /*
    The default destructor of the class "RobotMovement"

    Input: (none)
    Output: (none)
    */
    ~RobotAutoMovement();
};

#endif
