#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "api.h"

namespace CONSTANTS
{
    namespace PORT
    {
        // all not set +++++++++++++++++++++++
        // all port numbers
        const unsigned int LEFT_FRONT       = 0;
        const unsigned int RIGHT_FRONT      = 0;
        const unsigned int LEFT_BACK        = 0;
        const unsigned int RIGHT_BACK       = 0;
    }

    namespace ROBOT
    {
        // all not set +++++++++++++++++++++++
        // all dimensions for robot
        const double WHEEL_DIAMETER         = 0;
    }

    namespace PID
    {
        // all values for PID control
    }

    namespace BASIS_MOTORS
    {
        // all not set +++++++++++++++++++++++
        // all info about basis motors (except ports)
        const pros::motor_gearset_e_t GEARSET = pros::E_MOTOR_GEARSET_18;

        const bool LEFT_FRONT_REVERSED      = false;
        const bool RIGHT_FRONT_REVERSED     = false;
        const bool LEFT_BACK_REVERSED       = false;
        const bool RIGHT_BACK_REVERSED      = false;
    }
}

#endif
