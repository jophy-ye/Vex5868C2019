/*
* Some function to deal with gui on the vex v5 brain
*/
#include "main.h"
#include <cstdint>

#ifndef _GUI_H_
#define _GUI_H_


/**
 * Used to generate a task to run code dealing with GUI
 */
void GuiHandler();

/**
 * Initialize all components for Initialize stage
 */
void InitSetup();

/**
 * When one of four buttons (for autonomous position)
 * is pressed, this function will be activated
 */
static lv_res_t ChangePosBtnPressed_Action(lv_obj_t* PressedButton);

/**
 * Load the robot status on the initalize screen
 * Although it is normally called by the robot, 
 * this action can be called manually when necessary
 */
static lv_res_t LoadStatus_Action(lv_obj_t* RefreshButton);

/**
 * Initialize all components for Autonomous Period
 */
void AutonSetup();

/**
 * Initialize all components for DriverControl Period
 */
void DConSetup();

#endif