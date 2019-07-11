/*
* Some function to deal with gui on the vex v5 brain
*/
#include "main.h"
#include <cstdint>

#ifndef _GUI_H_
#define _GUI_H_


/**
 * all components used for lvgl interface
 * 
 * Note1: all marked as static which means it can only
 * be accessed in this file
 * 
 * TODO: styling (unurgent)
 */
lv_obj_t* Brain_Scr;        // the vex brain screen
std::int16_t Scr_Width;     // the vex brain screen width
std::int16_t Scr_Height;    // the vex brain screen height


// Note: This page is seprated as different tabs
lv_obj_t* Init_Page;        // the tabview widget used to store all initialize objects
lv_obj_t* Init_Robot_Stat_Tab;    // the tab (belongs to Init_Page) to show the robot status
lv_obj_t* Init_Robot_Stat_Battery_Cap_Label;  //* the battery capacity (vex brain) label
lv_obj_t* Init_Robot_Stat_Comp_Status_Label;  //* the competition status label
lv_obj_t* Init_Robot_Stat_Cont_Battery_Cap_Label;   //* the battery capacity (controller) label
lv_obj_t* Init_Robot_Stat_Ref_Btn;  // the button for user to reload the data

lv_obj_t* Init_Action_Selector;     // the tab (belongs to Init_Page) to show the action selector, like autonomous.


lv_obj_t* Auton_Page;       //* the page used to store all autonomous objects
lv_obj_t* DCon_Page;        //* the page used to store all DriverControl objects




/**
 * Used to generate a task to run code dealing with GUI
 */
void GuiHandler();

/**
 * Initialize all components for Initialize stage
 */
void InitSetup();

/**
 * Load the robot status on the initalize screen
 * Although it is normally called by the robot, 
 * this action can be called manually when necessary
 */
lv_res_t LoadStatus_Action(lv_obj_t* RefreshButton);

/**
 * Initialize all components for Autonomous Period
 */
void AutonSetup();

/**
 * Initialize all components for DriverControl Period
 */
void DConSetup();

#endif