#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "api.h"

namespace CONSTANTS
{
    const double PI = 3.141592653589;

    namespace PORT
    {
        // all not set +++++++++++++++++++++++
        // all port numbers
        const unsigned int LEFT_FRONT       = 5;    // motor
        const unsigned int RIGHT_FRONT      = 10;   // motor
        const unsigned int LEFT_BACK        = 4;    // motor
        const unsigned int RIGHT_BACK       = 9;    // motor

        const unsigned int INTAKE_1         = 18;    // motor
        const unsigned int INTAKE_2         = 11;    // motor
        const unsigned int INTAKE_LIFTER    = 20;   // motor

        const unsigned int LIFTER           = 16;    // motor
    }

    namespace ROBOT
    {
        // all not set +++++++++++++++++++++++
        // all dimensions for robot
        const double WHEEL_DIAMETER         = 10.16;

        /*
        The turning radius of the robot.
        TURN_RADIUS = sqrt(robot_width^2 + distance_between_wheel^2) / 2
        */
        const double TURN_RADIUS            = 33.4;

        const double MOTOR_LOCK_CONTROL_KP  = 2;
    }

    namespace AUTO_MOVEMENT
    {
        // all not set +++++++++++++++++++++++
        // all values for PID control
        const float KP = 4;

        /*
        if OptimizedStop is enabled,
        the robot will start to slow down 'OPTIMIZEDSTOP_PRESERVE_DIST' cm before the goal
        */
        const float OPTIMIZEDSTOP_PRESERVE_DIST = 15;
    }

    namespace BASIS_MOTORS
    {
        // all not set +++++++++++++++++++++++
        // all info about basis motors (except ports)
        const pros::motor_gearset_e_t GEARSET = pros::E_MOTOR_GEARSET_18;

        const bool LEFT_FRONT_REVERSED              = true;
        const bool RIGHT_FRONT_REVERSED             = false;
        const bool LEFT_BACK_REVERSED               = false;
        const bool RIGHT_BACK_REVERSED              = true;
    }

    namespace JOYSTICK_VAL
    {
        // all not set +++++++++++++++++++++
        // all info of joystick mapping

        // an absolute value for horizontal sliding joystick thresold
        const double HORIZONTAL_SLIDE_THRESOLD      = 0.4;
        // the motor value would be joystick_input * CONTROL_P_VAL
        const double CONTROL_P_VAL                  = 0.95;
    }

    namespace LIFTER
    {
        // all not set +++++++++++++++++++++
        // all info of lifter (except port)
        const bool LIFTER_REVERSED                  = true;

        const int LIFTER_POWER_MAX                  = 54;
        const float LIFTER_KP                       = 0.7;

        // Thresold value of LifterMotor's encoder (high position)
        const float LIFTER_HIGH_DEGREE              = 3200;
        // Thresold value of LifterMotor's encoder (low position)
        const float LIFTER_LOW_DEGREE               = 0;

        const float LIFTER_SLOWDOWN_RESERVE_DEGREE  = 700;


        // the minimum degree required to avoid colliding with intake-lifter when intake-lifter is moving
        const float AVOID_INTAKELIFTER_MIN_DEGREE   = 800;
    }

    namespace INTAKE
    {
        // all not set +++++++++++++++++++++
        // all info of the two intakes (except port)
        const bool INTAKE_1_REVERSED                = true;
        const bool INTAKE_2_REVERSED                = false;
        const bool INTAKE_LIFTER_REVERSED           = true;

        const float INTAKE_LIFTER_KP                = 0.7;
        // Thresold value of IntakeLifterMotor's encoder (high position)
        const float INTAKE_LIFTER_HIGH_DEGREE       = 2400;
        // Thresold value of IntakeLifterMotor's encoder (low position)
        const float INTAKE_LIFTER_LOW_DEGREE        = 0;
    }
}

#endif
