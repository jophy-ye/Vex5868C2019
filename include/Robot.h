/*
The class of the basis move
    containing the motor declaration
*/

#ifndef _BASIS_H_
#define _BASIS_H_

#include "api.h"

#include "Config.h"
using namespace CONSTANTS;

class Robot
{
public:
    pros::Motor LeftFrontMotor;      // Basis LeftFrontMotor
    pros::Motor LeftBackMotor;      // Basis LeftBackMotor
    pros::Motor RightFrontMotor;    // Basis RightFrontMotor
    pros::Motor RightBackMotor;     // Basis RightBackMotor

    pros::Motor Intake1Motor;       // the first intake motor
    pros::Motor Intake2Motor;       // the second intake motor

    pros::Motor LifterMotor;        // the lifter motor
    pros::ADIDigitalIn LifterSwitch;// the limit switch used by the lifter

    /*
    The default constructor
    */
    Robot():
       LeftFrontMotor(PORT::LEFT_FRONT, BASIS_MOTORS::GEARSET, BASIS_MOTORS::LEFT_FRONT_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       LeftBackMotor(PORT::LEFT_BACK, BASIS_MOTORS::GEARSET, BASIS_MOTORS::LEFT_BACK_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       RightFrontMotor(PORT::RIGHT_FRONT, BASIS_MOTORS::GEARSET, BASIS_MOTORS::RIGHT_FRONT_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       RightBackMotor(PORT::RIGHT_BACK, BASIS_MOTORS::GEARSET, BASIS_MOTORS::RIGHT_BACK_REVERSED, pros::E_MOTOR_ENCODER_DEGREES),
       Intake1Motor(PORT::INTAKE_1, INTAKE::INTAKE_1_REVERSED),
       Intake2Motor(PORT::INTAKE_2, INTAKE::INTAKE_2_REVERSED),
       LifterMotor(PORT::LIFTER, LIFTER::LIFTER_REVERSED),
       LifterSwitch(PORT::LIFTER_SWITCH) {};

    /*
    The default destructor
    */
    ~Robot() {};
};

#endif
