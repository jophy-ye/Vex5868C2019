#include <cstdlib>
#include "main.h"

#include "RobotAuto.h"
#include "vector2d.h"
#include "Config.h"
#include "typedefs.h"
#include "Debug.h"
using namespace CONSTANTS;

pros::Controller joystick(pros::E_CONTROLLER_MASTER);


/**
 * Check the robot battery, if the voltage is lower than 11V, it will report on the joystick.
*/
bool CheckBattery()
{
    if (((double)pros::battery::get_voltage() / 1000) < 12.7)
    {
        // battery is too low, report on the controller
        joystick.set_text(0, 0, "Battery Too Low!");
		return true;
    }
	else
	{
		return false;
	}
}

/**2
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
	//pros::Controller joystick(pros::E_CONTROLLER_MASTER);
	extern RobotAuto robot;
	extern GameStatus_t GameStatus;
	GameStatus = DriverControl;
	vector2d LeftJoyVec, RightJoyVec;	// Vector to store left and right joystick number
	bool CURRENT_SLIDE	= false;	// asign to true if current mode is "slide movement", asign to false if it is "normal movement"

	// these variables are used for time-warn (last 15 seconds)
	uint32_t OpStartMillis = pros::millis();	// the starting time of opcontrol in millis
	bool TimeWarnActivated = false;				// when time warn has been done, this will be set to true

	Debug::StatLog("$ OpControl Starting");

	if (CheckBattery())
	{
		joystick.rumble(".-");
	}
	else
	{
		joystick.rumble("-"); // warn the user, game is starting
	}
	
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
			robot.MotorReleaseLock();
			// horizontal sliding movement ( abs(left_joystick_gradient)) < thresold )
			if (CURRENT_SLIDE == false)
				robot.MotorReset();

			robot.Slide(LeftJoyVec.get_x() * JOYSTICK_VAL::CONTROL_P_VAL);

			CURRENT_SLIDE = true;
		}
		else
		{
			// normal basic movement (forward/backward)
			if (LeftJoyVec.magnitude() < 15 && RightJoyVec.magnitude() < 15)
			{
				robot.MotorStartLock();
			}
			else
			{
				robot.MotorReleaseLock();
				robot.LeftFrontMotor = LeftJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;
				robot.LeftBackMotor = LeftJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;
				robot.RightFrontMotor = RightJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;
				robot.RightBackMotor = RightJoyVec.get_y() * JOYSTICK_VAL::CONTROL_P_VAL;	
			}

			CURRENT_SLIDE = false;
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

		
		// time-check (last 15 seconds)
		if ((pros::millis() - OpStartMillis > 90000) && (!TimeWarnActivated))
		{
			joystick.rumble("-");
			joystick.set_text(0, 0, "Time Warning");
			TimeWarnActivated = true;
		}

		pros::delay(20);
	}
}
