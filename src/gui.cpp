#include <cctype>

#include "gui.h"
#include "main.h"
#include "RobotAuto.h"

extern GameStatus_t GameStatus;

// the previous status handled
GameStatus_t PreviousStatus;

void GuiHandler()
{
    /** 
     * this is the starting of this function which will be called by initialize().
     * So PreviousStatus is not set, just randomly set one variable that is not equal to Initialize
     * will triger the action of drawing something on screen.
     * */
    PreviousStatus = DriverControl;

    while (true)
    {
        if (PreviousStatus != GameStatus)
        {
            // the status has changed, do something on the screen
            if (GameStatus == Initialize)
                InitAction();
            else if (GameStatus == Autonomous)
                AutonAction();
            else if (GameStatus == DriverControl)
                DriverConAction();
        }

        pros::delay(150);
    }
}

void InitAction()
{
    

    PreviousStatus = Initialize;
}

void AutonAction()
{
    PreviousStatus = Autonomous;
}

void DriverConAction()
{
    PreviousStatus = DriverControl;
}
