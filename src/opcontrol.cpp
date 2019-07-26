#include <cstdlib>
#include "main.h"

#include "RobotAuto.h"
#include "vector2d.h"
#include "Config.h"
#include "typedefs.h"
#include "Debug.h"
using namespace CONSTANTS;

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


void opcontrol()
{
	pros::Controller joystick(pros::E_CONTROLLER_MASTER);
	//pros::Controller joystick(pros::E_CONTROLLER_MASTER);
	extern RobotAuto robot;
	extern GameStatus_t GameStatus;
	GameStatus = DriverControl;
	vector2d LeftJoyVec, RightJoyVec;	// Vector to store left and right joystick number
	Debug::StatLog("$ OpControl Starting");

	joystick.rumble("-"); // warn the user, game is starting
	
	// start the loop
	while (true)
	{
		LeftJoyVec.set_x(joystick.get_analog(ANALOG_LEFT_X));
		LeftJoyVec.set_y(joystick.get_analog(ANALOG_LEFT_Y));
		RightJoyVec.set_x(joystick.get_analog(ANALOG_RIGHT_X));
		RightJoyVec.set_y(joystick.get_analog(ANALOG_RIGHT_Y));


		// robot movement
		if (std::abs(LeftJoyVec.gradient()) < JOYSTICK_VAL::HORIZONTAL_SLIDE_THRESOLD && 
				RightJoyVec.magnitude() < 10)
		{
			// horizontal sliding movement ( abs(left_joystick_gradient)) < thresold )
			robot.Slide(LeftJoyVec.get_x() * JOYSTICK_VAL::CONTROL_P_VAL);
		}
		else
		{
			// basis basic movement (forward/backward)
			if (LeftJoyVec.magnitude() < 15 && RightJoyVec.magnitude() < 15)
			{
				robot.LeftFrontMotor = 0;
				robot.LeftBackMotor = 0;
				robot.RightFrontMotor = 0;
				robot.RightBackMotor = 0;	
			}
			else
			{
				robot.LeftFrontMotor = LeftJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;
				robot.LeftBackMotor = LeftJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;
				robot.RightFrontMotor = RightJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;
				robot.RightBackMotor = RightJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;	
			}
		}

		
		// intake motors
		if (joystick.get_digital(DIGITAL_L1))
			robot.SetIntakeMode(1);
		else if (joystick.get_digital(DIGITAL_L2))
			robot.SetIntakeMode(2);
		else
			robot.SetIntakeMode(0);
		
		// intake-lifter controls
		if (joystick.get_digital(DIGITAL_R1))
			robot.IntakeLifterTargetPos += 20;
		else if (joystick.get_digital(DIGITAL_R2))
			robot.IntakeLifterTargetPos -= 20;
		

		// lifter motors
		if (joystick.get_digital(DIGITAL_X))
			robot.LifterTargetPos += 15;
		else if (joystick.get_digital(DIGITAL_B))
			robot.LifterTargetPos -= 15;
		else if (joystick.get_digital(DIGITAL_A))
			robot.LifterTargetPos += 8;

		pros::delay(20);
	}
}
