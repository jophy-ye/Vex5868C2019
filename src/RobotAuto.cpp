#include "api.h"

#include "RobotAuto.h"
#include "Config.h"
using namespace CONSTANTS;

#include <cmath>


/**
 * param is the parameter passed when the task is created.
 * In this case, param store a pointer to the instance of RobotAuto (robot)
 *  */
void LiftersTaskControllerFunc(void* param)
{
    while (true)
    {
        if (param != NULL)
        {
            ((RobotAuto*)param)->UpdateIntakeLifterPos();
            ((RobotAuto*)param)->UpdateLifterPos();
        }
        else
        {
            // param is not pointing to anything, raise an error
            Debug::WarnLog("In \"LiftersTask\", (RobotAuto*) is not pointing to anything.");
        }
        
        pros::delay(100);
    }
}


void RobotAuto::Stop()
{
    LeftFrontMotor = 0;
    RightFrontMotor = 0;
    LeftBackMotor = 0;
    RightBackMotor = 0;

    MotorReset();
}

void RobotAuto::MotorReset()
{
    LeftFrontMotor.tare_position();
    LeftBackMotor.tare_position();
    RightFrontMotor.tare_position();
    RightBackMotor.tare_position();

    LeftMotorMovedCM = RightMotorMovedCM = 0;
}

void RobotAuto::Move(double power)
{
    double LeftPower, RightPower;

    // calculate the power for both sides with PID's P controlAUTO_MOVEMENT
    LeftPower = power - (LeftMotorMovedCM - RightMotorMovedCM) * AUTO_MOVEMENT::KP;
    RightPower = power + (LeftMotorMovedCM - RightMotorMovedCM) * AUTO_MOVEMENT::KP;

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
    LeftMotorMovedCM = (LeftFrontMotor.get_position() + LeftBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
    RightMotorMovedCM = (RightFrontMotor.get_position() + RightBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
}

void RobotAuto::MoveDistance(double dist, double power, bool OptimizedStop)
{
    using std::abs;

    Stop();
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
        LeftMotorMovedCM = (LeftFrontMotor.get_position() + LeftBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
        RightMotorMovedCM = (RightFrontMotor.get_position() + RightBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
    }

    // let the whole robot stop after finishing the move
    Stop();
}

void RobotAuto::Slide(double power)
{
    // Each power variable is the robot's front motors power.
    double LeftPower, RightPower;

    // calculate the power for both sides with PID's P controlAUTO_MOVEMENT
    LeftPower = power;
    RightPower = - power;

    // modify the power if it exceeded
    if (LeftPower > 127)    LeftPower = 127;
    if (LeftPower < -127)   LeftPower = -127;
    if (RightPower > 127)   RightPower = 127;
    if (RightPower < -127)  RightPower = -127;

    // apply the power to the motors
    LeftFrontMotor = (int) LeftPower;
    LeftBackMotor = - ((int) LeftPower);
    RightFrontMotor = (int) RightPower;
    RightBackMotor = - ((int) RightPower);

    // change the value of LeftMotorMovedCM and RightMotorMovedCM
    // Note: the encoder_unit has been set to "degree"
    LeftMotorMovedCM = (LeftBackMotor.get_position() - LeftFrontMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
    RightMotorMovedCM = (RightFrontMotor.get_position() - RightBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
}

void RobotAuto::SlideDistance(double dist, double power, bool OptimizedStop)
{
    using std::abs;

    Stop();
    double LeftPower, RightPower;
    using AUTO_MOVEMENT::OPTIMIZEDSTOP_PRESERVE_DIST;

    LeftFrontMotor.tare_position();
    LeftBackMotor.tare_position();
    RightFrontMotor.tare_position();
    RightBackMotor.tare_position();

    while (abs(LeftMotorMovedCM) < abs(dist) || abs(RightMotorMovedCM) < abs(dist))
    {
        // calculate the power for both sides with PID's P control
        LeftPower = power;
        RightPower = - power;

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
        LeftBackMotor = - ((int) LeftPower);
        RightFrontMotor = (int) RightPower;
        RightBackMotor = - ((int) RightPower);
        
        // change the value of LeftMotorMovedCM and RightMotorMovedCM
        // Note: the encoder_unit has been set to "degree"
        LeftMotorMovedCM = (LeftFrontMotor.get_position() - LeftBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
        RightMotorMovedCM = (RightBackMotor.get_position() - RightFrontMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
    }

    // let the whole robot stop after finishing the move
    Stop();
}

void RobotAuto::Turn(double power)
{
    double LeftPower, RightPower;

    // calculate the power for both sides with PID's P controlAUTO_MOVEMENT
    LeftPower = power - (LeftMotorMovedCM + RightMotorMovedCM) * AUTO_MOVEMENT::KP;
    RightPower = - power - (LeftMotorMovedCM + RightMotorMovedCM) * AUTO_MOVEMENT::KP;

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
    LeftMotorMovedCM = (LeftFrontMotor.get_position() + LeftBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
    RightMotorMovedCM = (RightFrontMotor.get_position() + RightBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
}

void RobotAuto::TurnDegree(double degree, double power, bool OptimizedStop)
{
    using std::abs;

    Stop();
    double LeftPower, RightPower;
    using AUTO_MOVEMENT::OPTIMIZEDSTOP_PRESERVE_DIST;

    double turn_dist = ROBOT::TURN_RADIUS * PI * degree / 180;  // the distance each wheel is supposed to move

    LeftFrontMotor.tare_position();
    LeftBackMotor.tare_position();
    RightFrontMotor.tare_position();
    RightBackMotor.tare_position();

    while (abs(LeftMotorMovedCM) < abs(turn_dist) || abs(RightMotorMovedCM) < abs(turn_dist))
    {
        // calculate the power for both sides with PID's P control
        LeftPower = power - (LeftMotorMovedCM + RightMotorMovedCM) * AUTO_MOVEMENT::KP;
        RightPower = - power - (LeftMotorMovedCM + RightMotorMovedCM) * AUTO_MOVEMENT::KP;

        // configure the output power if OptimizedStop is enabled
        if (OptimizedStop)
        {
            if ((abs(turn_dist) - abs(LeftMotorMovedCM)) <= OPTIMIZEDSTOP_PRESERVE_DIST
                || (abs(turn_dist) - abs(RightMotorMovedCM)) <= OPTIMIZEDSTOP_PRESERVE_DIST)
            {
                // configure the power because the robot is near the end and OptimizedStop is enabled
                double ConfigureRate = (abs(turn_dist - abs(LeftMotorMovedCM))) / OPTIMIZEDSTOP_PRESERVE_DIST;

                LeftPower *= ConfigureRate;
                RightPower *= ConfigureRate;
            }
        }

        // modify the power if it exceeded
        if (LeftPower > 127)    LeftPower = 127;
        if (LeftPower < -127)   LeftPower = -127;
        if (RightPower > 127)   RightPower = 127;
        if (RightPower < -127)  RightPower = -127;

        // apply the power to therobot motors
        LeftFrontMotor = (int) LeftPower;
        LeftBackMotor = (int) LeftPower;
        RightFrontMotor = (int) RightPower;
        RightBackMotor = (int) RightPower;

        // change the value of LeftMotorMovedCM and RightMotorMovedCM
        // Note: the encoder_unit has been set to "degree"
        LeftMotorMovedCM = (LeftFrontMotor.get_position() + LeftBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
        RightMotorMovedCM = (RightFrontMotor.get_position() + RightBackMotor.get_position()) / 720 * (ROBOT::WHEEL_DIAMETER * PI);
    }

    // let the whole robot stop after finishing the move
    Stop();
}

bool RobotAuto::SetIntakeMode(short mode_input)
{
    switch(mode_input)
    {
        case 0: Intake1Motor = 0; Intake2Motor = 0; return true;
        case 1: Intake1Motor = -127; Intake2Motor = -127; return true;
        case 2: Intake1Motor = 127; Intake2Motor = 127; return true;
        default: Debug::WarnLog("Did not specify a correct mode for SetIntakeMode"); return false;
    }
}

void RobotAuto::UpdateIntakeLifterPos()
{
    if (IntakeLifterTargetPos < INTAKE::INTAKE_LIFTER_LOW_DEGREE)
        IntakeLifterTargetPos = INTAKE::INTAKE_LIFTER_LOW_DEGREE;
    if (IntakeLifterTargetPos > INTAKE::INTAKE_LIFTER_HIGH_DEGREE)
        IntakeLifterTargetPos = INTAKE::INTAKE_LIFTER_HIGH_DEGREE;

    double power = (IntakeLifterTargetPos - IntakeLifterMotor.get_position()) * INTAKE::INTAKE_LIFTER_KP;
    IntakeLifterMotor = (int)power;
}

void RobotAuto::UpdateLifterPos()
{
    if (LifterMotor.get_position() < LIFTER::AVOID_INTAKELIFTER_MIN_DEGREE && 
        IntakeLifterTargetPos > 20)
    {
        LifterTargetPos = LIFTER::AVOID_INTAKELIFTER_MIN_DEGREE;
        LifterMotor.move_absolute(LIFTER::AVOID_INTAKELIFTER_MIN_DEGREE, 70);
    }
    else
    {
        double power;
        power = (LifterTargetPos - LifterMotor.get_position()) * LIFTER::LIFTER_KP;

        // modify the velocity if it is too big
        if (power > LIFTER::LIFTER_POWER_MAX)
            power = LIFTER::LIFTER_POWER_MAX;
        else if (power < - LIFTER::LIFTER_POWER_MAX)
            power = - LIFTER::LIFTER_POWER_MAX;
        
        if (std::abs(power) < 10)
            power = 0;

        LifterMotor = (int)power;   
    }
}

RobotAuto::~RobotAuto()
{};
