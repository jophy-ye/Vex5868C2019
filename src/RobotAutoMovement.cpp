#include "api.h"

#include "RobotAutoMovement.h"
#include "Constants.h"
using namespace CONSTANTS;

#include <cmath>


void RobotAutoMovement::Stop()
{
    LeftFrontMotor = 0;
    RightFrontMotor = 0;
    LeftBackMotor = 0;
    RightFrontMotor = 0;
}

void RobotAutoMovement::Move(double power)
{
    LeftFrontMotor = power;
    RightFrontMotor = power;
    LeftBackMotor = power;
    RightFrontMotor = power;
}

void RobotAutoMovement::MoveDistance(double dist, double power, bool OptimizedStop)
{
    using std::abs;
    double LeftMotorMovedCM, RightMotorMovedCM;
    LeftMotorMovedCM = RightMotorMovedCM = 0;
    double LeftPower, RightPower;
    using AUTO_MOVEMENT::OPTIMIZEDSTOP_PRESERVE_DIST;

    LeftFrontMotor.tare_position();
    LeftBackMotor.tare_position();
    RightFrontMotor.tare_position();
    RightBackMotor.tare_position();


    while (abs(LeftMotorMovedCM) < abs(dist) || abs(RightMotorMovedCM) < abs(dist))
    {
        // calculate the power for both sides with PID's P controlAUTO_MOVEMENT
        LeftPower = power - (LeftMotorMovedCM - RightMotorMovedCM) * AUTO_MOVEMENT::KP;
        RightPower = power + (LeftMotorMovedCM - RightMotorMovedCM) * AUTO_MOVEMENT::KP;

        // configure the output power if OptimizedStop is enabled
        if (OptimizedStop)
        {
            if ((abs(dist) - abs(LeftMotorMovedCM)) <= OPTIMIZEDSTOP_PRESERVE_DIST
                || (abs(dist) - abs(RightMotorMovedCM)) <= OPTIMIZEDSTOP_PRESERVE_DIST)
            {
                // configure the power because the robot is near the end and OptimizedStop is enabled
                double ConfigureRate = (abs(dist - abs(LeftMotorMovedCM))) / OPTIMIZEDSTOP_PRESERVE_DIST;

                LeftPower *= ConfigureRate;
                RightPower *= ConfigureRate;
            }
        }

        // modify the power if it exceeded
        if (LeftPower > 127)    LeftPower = 127;
        if (LeftPower < -127)   LeftPower = -127;
        if (RightPower > 127)   RightPower = 127;
        if (RightPower < -127)  RightPower = -127;

        // apply the power to the motors
        LeftFrontMotor = (int) LeftPower;
        LeftBackMotor = (int) LeftPower;
        RightFrontMotor = (int) RightPower;
        RightBackMotor = (int) RightPower;

        // change the value of LeftMotorMovedCM and RightMotorMovedCM
        // Note: the encoder_unit has been set to "degree"
        LeftMotorMovedCM = LeftFrontMotor.get_position() / 360 * (ROBOT::WHEEL_DIAMETER * PI);
        RightMotorMovedCM = RightFrontMotor.get_position() / 360 * (ROBOT::WHEEL_DIAMETER * PI);
    }

    // let the whole robot stop after finishing the move
    Stop();
}
