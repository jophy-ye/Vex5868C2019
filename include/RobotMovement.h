#ifndef _ROBOT_MOVEMENT_H_
#define _ROBOT_MOVEMENT_H_

#include "Constants.h"
using namespace CONSTANTS;
#include "api.h"

class RobotMovement
{
private:
    pros::Motor LeftFrontMotor;
    pros::Motor LeftBackMotor;
    pros::Motor RightFrontMotor;
    pros::Motor RightBackMotor;
public:
    RobotMovement():
       LeftFrontMotor(PORT::LEFT_FRONT, BASIS_MOTORS::GEARSET, BASIS_MOTORS::LEFT_FRONT_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       LeftBackMotor(PORT::LEFT_BACK, BASIS_MOTORS::GEARSET, BASIS_MOTORS::LEFT_BACK_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       RightFrontMotor(PORT::RIGHT_FRONT, BASIS_MOTORS::GEARSET, BASIS_MOTORS::RIGHT_FRONT_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       RightBackMotor(PORT::RIGHT_BACK, BASIS_MOTORS::GEARSET, BASIS_MOTORS::RIGHT_BACK_REVERSED, pros::E_MOTOR_ENCODER_DEGREES) {};
    /*
    The constructor function of the class "RobotMovement"

    Input: (none)
    Output: (none)
    */

    void Stop();
    /*
    Function for the whole robot to stop

    Input: (none)
    Output: (none)
    */

    void Move(double power = 127);
    /*
    Function for the whole robot to start moving

    Input:
        power (double)      :  The power for the motor (-127 ~ 127)
    Output: (none)
    */

    void MoveDistance(double dist, double power = 127, bool OptimizedStop = false);
    /*
    Function for the whole robot to move a certain distance

    Input:
        dist (double)       :  The desire distance in centimeters(cm)
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)
    */

    void SlideDistance(double dist, double power = 127, bool OptimizedStop = false);
    /*
    Function for the whole robot to slide left and right

    Input:
        dist (double)       :  The desire distance in centimeters(cm)
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)
    */

    void Turn(double degree, double power = 127, bool OptimizedStop = false);
    /*
    Function for the whole robot to turn

    Input:
        degree (double)     :  The desire degree
        power (double)      :  The power for the motor (-127 ~ 127)
        OptimizedStop (bool):  The stop of the movement will be more accurate if true
    Output: (none)
    */
};

#endif
