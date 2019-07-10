/*
* Some function to deal with gui on the vex v5 brain
*/


#ifndef _GUI_H_
#define _GUI_H_


/**
 * Used to generate a task to run code dealing with GUI
 */
void GuiHandler();

/**
 * Action to be done when game mode has changed to Initialize
 */
void InitAction();

/**
 * Action to be done when game mode has changed to Autonomous Period
 */
void AutonAction();

/**
 * Action to be done when game mode has changed to Driver Control Period
 */
void DriverConAction();

#endif