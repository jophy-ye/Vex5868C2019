#include "RobotAutoMovement.h"
#include "Constants.h"
using namespace CONSTANTS;

void RobotAutoMovement::Stop()
{
    LeftFrontMotor = 0;
    RightFrontMotor = 0;
    LeftBackMotor = 0;
    RightFrontMotor = 0;
}
