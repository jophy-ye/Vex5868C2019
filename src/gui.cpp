#include <cstdint>

#include "gui.h"
#include "main.h"
#include "RobotAuto.h"
#include "typedefs.h"

extern AutonPos_t AutonPos;
extern GameStatus_t GameStatus;

// the previous status handled
GameStatus_t PreviousStatus;


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
lv_obj_t* Init_Robot_Stat_Battery_Volt_Label;   // the battery voltage (vex brain) label
lv_obj_t* Init_Robot_Stat_Comp_Connected_Label;  // the competition status label
lv_obj_t* Init_Robot_Stat_Cont_Battery_Volt_Label;   // the battery capacity (controller) label
lv_obj_t* Init_Robot_Stat_Ref_Btn;  // the button for user to reload the data

lv_obj_t* Init_Action_Selector;     // the tab (belongs to Init_Page) to show the action selector, like autonomous.
lv_obj_t* GuideText_Label;  // the label to guide the user for selecting the button (can be reused)
lv_obj_t* BlueFront_btn;    // the button for starting position: Blue_Front, free_num = 0
lv_obj_t* RedFront_btn; // the button for starting position: Red_Front, free_num = 1
lv_obj_t* BlueBack_btn; // the button for starting position: Blue_Back, free_num = 2
lv_obj_t* RedBack_btn;  // the button for starting position: Red_Back, free_num = 3
lv_obj_t* Skills_btn;   // the button for starting position: Skills, free_num = 4
lv_obj_t* Init_Action_Main_Label;


// lv_obj_t* Auton_Page;       //* the page used to store all autonomous objects
// lv_obj_t* DCon_Page;        //* the page used to store all DriverControl objects


void GuiHandler(void* param)
{
    /** 
     * this is the starting of this function which will be called by initialize().
     * So PreviousStatus is not set, just randomly set one variable that is not equal to Initialize
     * will triger the action of drawing something on screen.
     * */
    PreviousStatus = DriverControl;
    Brain_Scr = lv_scr_act();
    Scr_Height = lv_obj_get_height(Brain_Scr);
    Scr_Width = lv_obj_get_width(Brain_Scr);
    InitSetup();
    AutonSetup();
    DConSetup();

    while (true)
    {
        if (PreviousStatus != GameStatus)
        {
            // the status has changed, show the specific container
            lv_obj_set_hidden(Init_Page, true);
            // lv_obj_set_hidden(Auton_Page, true);
            // lv_obj_set_hidden(DCon_Page, true);
            if (GameStatus == Initialize)
            {
                lv_obj_set_hidden(Init_Page, false);
                PreviousStatus = Initialize;
            }
            else if (GameStatus == Autonomous)
            {
                // lv_obj_set_hidden(Auton_Page, false);
                PreviousStatus = Autonomous;
            }
            else if (GameStatus == DriverControl)
            {
                // lv_obj_set_hidden(DCon_Page, false);
                PreviousStatus = DriverControl;
            }
        }

        pros::delay(200);
    }
}

void InitSetup()
{
    // set up the init_tabview and all the tabs
    Init_Page = lv_tabview_create(Brain_Scr, NULL);
    lv_obj_align(Init_Page, Brain_Scr, LV_ALIGN_CENTER, 0, 0);
    Init_Robot_Stat_Tab = lv_tabview_add_tab(Init_Page, "Status");
    Init_Action_Selector = lv_tabview_add_tab(Init_Page, "Select Action");

    // set up some robot status data on screen
    Init_Robot_Stat_Battery_Volt_Label = lv_label_create(Init_Robot_Stat_Tab, NULL);
    Init_Robot_Stat_Comp_Connected_Label = lv_label_create(Init_Robot_Stat_Tab, NULL);
    Init_Robot_Stat_Cont_Battery_Volt_Label = lv_label_create(Init_Robot_Stat_Tab, NULL);
    lv_obj_align(Init_Robot_Stat_Battery_Volt_Label, Init_Robot_Stat_Tab, 
                LV_ALIGN_IN_RIGHT_MID, -290, 130);
    lv_obj_align(Init_Robot_Stat_Comp_Connected_Label, Init_Robot_Stat_Battery_Volt_Label,
                LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 0);
    lv_obj_align(Init_Robot_Stat_Cont_Battery_Volt_Label, Init_Robot_Stat_Comp_Connected_Label,
                LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 0);
    Init_Robot_Stat_Ref_Btn = lv_btn_create(Init_Robot_Stat_Tab, NULL);
    lv_obj_align(Init_Robot_Stat_Ref_Btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 70);
    lv_btn_set_action(Init_Robot_Stat_Ref_Btn, LV_BTN_ACTION_CLICK, LoadStatus_Action);
    LoadStatus_Action(Init_Robot_Stat_Ref_Btn); // call function to load data manually
    GuideText_Label = lv_label_create(Init_Robot_Stat_Ref_Btn, NULL);
    lv_obj_align(GuideText_Label, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(GuideText_Label, "Refresh");
    lv_obj_set_height(Init_Robot_Stat_Ref_Btn, 60);

    // set the Action selector
    Init_Action_Main_Label = lv_label_create(Init_Action_Selector, NULL);
    lv_label_set_text(Init_Action_Main_Label, "Select Autonomous Position: ");
    lv_obj_align(Init_Action_Main_Label, Init_Action_Selector, LV_ALIGN_IN_TOP_MID, 0, -230);
    BlueFront_btn = lv_btn_create(Init_Action_Selector, NULL);
    RedFront_btn = lv_btn_create(Init_Action_Selector, NULL);
    BlueBack_btn = lv_btn_create(Init_Action_Selector, NULL);
    RedBack_btn = lv_btn_create(Init_Action_Selector, NULL);
    Skills_btn = lv_btn_create(Init_Action_Selector, NULL);
    lv_obj_set_size(BlueFront_btn, lv_obj_get_width(Init_Action_Selector) / 2 - 10, 45);
    lv_obj_set_size(RedFront_btn, lv_obj_get_width(Init_Action_Selector) / 2 - 10, 45);
    lv_obj_set_size(BlueBack_btn, lv_obj_get_width(Init_Action_Selector) / 2 - 10, 45);
    lv_obj_set_size(RedBack_btn, lv_obj_get_width(Init_Action_Selector) / 2 - 10, 45);
    lv_obj_set_size(Skills_btn, lv_obj_get_width(Init_Action_Selector) / 2 - 10, 45);
    //**** the twenty below is kind of random, not set!
    lv_obj_align(BlueFront_btn, Init_Action_Selector, LV_ALIGN_IN_TOP_LEFT, 10, 100);
    lv_obj_align(RedFront_btn, BlueFront_btn, LV_ALIGN_OUT_RIGHT_MID, 0, 0);
    lv_obj_align(BlueBack_btn, BlueFront_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_align(RedBack_btn, RedFront_btn, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_align(Skills_btn, BlueBack_btn, LV_ALIGN_OUT_BOTTOM_RIGHT, 130, 0);
    lv_obj_set_free_num(BlueFront_btn, 0);
    lv_obj_set_free_num(RedFront_btn, 1);
    lv_obj_set_free_num(BlueBack_btn, 2);
    lv_obj_set_free_num(RedBack_btn, 3);
    lv_obj_set_free_num(Skills_btn, 4);
    lv_btn_set_action(BlueFront_btn, LV_BTN_ACTION_PR, ChangePosBtnPressed_Action);
    lv_btn_set_action(RedFront_btn, LV_BTN_ACTION_PR, ChangePosBtnPressed_Action);
    lv_btn_set_action(BlueBack_btn, LV_BTN_ACTION_PR, ChangePosBtnPressed_Action);
    lv_btn_set_action(RedBack_btn, LV_BTN_ACTION_PR, ChangePosBtnPressed_Action);
    lv_btn_set_action(Skills_btn, LV_BTN_ACTION_PR, ChangePosBtnPressed_Action);
    GuideText_Label = lv_label_create(BlueFront_btn, NULL);
    lv_label_set_text(GuideText_Label, "Blue Front");
    lv_obj_align(GuideText_Label, NULL, LV_ALIGN_CENTER, 0, 0);
    GuideText_Label = lv_label_create(RedFront_btn, NULL);
    lv_label_set_text(GuideText_Label, "Red Front");
    lv_obj_align(GuideText_Label, NULL, LV_ALIGN_CENTER, 0, 0);
    GuideText_Label = lv_label_create(BlueBack_btn, NULL);
    lv_label_set_text(GuideText_Label, "Blue Back");
    lv_obj_align(GuideText_Label, NULL, LV_ALIGN_CENTER, 0, 0);
    GuideText_Label = lv_label_create(RedBack_btn, NULL);
    lv_label_set_text(GuideText_Label, "Red Back");
    lv_obj_align(GuideText_Label, NULL, LV_ALIGN_CENTER, 0, 0);
    GuideText_Label = lv_label_create(Skills_btn, NULL);
    lv_label_set_text(GuideText_Label, "Skills");
    lv_obj_align(GuideText_Label, NULL, LV_ALIGN_CENTER, 0, 0);
}

static lv_res_t ChangePosBtnPressed_Action(lv_obj_t* PressedButton)
{/* 
    lv_obj_set_text(BlueFront_btn, LV_BTN_STATE_TGL_REL);
    lv_obj_set_text(RedFront_btn, LV_BTN_STATE_TGL_REL);
    lv_obj_set_text(BlueBack_btn, LV_BTN_STATE_TGL_REL);
    lv_obj_set_text(RedBack_btn, LV_BTN_STATE_TGL_REL);*/

    std::uint32_t BtnFreeNum = lv_obj_get_free_num(PressedButton);
    switch(BtnFreeNum)
    {
        /**
         * The BlueFront button is 0, RedFront button is 1,
         * BlueBack button is 2, RedBack is 3
         */
        case 0: lv_label_set_text(Init_Action_Main_Label, "Blue Front"); break;
        case 1: lv_label_set_text(Init_Action_Main_Label, "Red Front"); break;
        case 2: lv_label_set_text(Init_Action_Main_Label, "Blue Back"); break;
        case 3: lv_label_set_text(Init_Action_Main_Label, "Red Back"); break;
        case 4: lv_label_set_text(Init_Action_Main_Label, "Skills"); break;
    }

    return LV_RES_OK;
}

static lv_res_t LoadStatus_Action(lv_obj_t* RefreshButton)
{
    // retrieve all data as reported by the vexos
    double BatteryVoltage = (double)pros::battery::get_voltage() / 1000;
    std::uint8_t CompStatus = pros::competition::get_status();
    std::int32_t ContBatteryLevel = pros::c::controller_get_battery_level(pros::E_CONTROLLER_MASTER);

    // print the data on the screen
    char buffer[32];
    buffer[0] = '\0';
    snprintf(buffer, 32, "Robot Battery Voltage: %f", BatteryVoltage);
    lv_label_set_text(Init_Robot_Stat_Battery_Volt_Label, buffer);
    buffer[0] = '\0';
    if (!((CompStatus & COMPETITION_CONNECTED) >> 1))
        strcpy(buffer, "Competition: Connected");
    else
        strcpy(buffer, "Competition: Not Connected");
    

    lv_label_set_text(Init_Robot_Stat_Comp_Connected_Label, buffer);
    buffer[0] = '\0';
    snprintf(buffer, 32, "Controller Battery Level: %d", ContBatteryLevel);
    lv_label_set_text(Init_Robot_Stat_Cont_Battery_Volt_Label, buffer);
    

    return LV_RES_OK;
}

void AutonSetup()
{
    /*
    Auton_Page = lv_page_create(Brain_Scr, NULL);
    lv_obj_align(Auton_Page, Brain_Scr, LV_ALIGN_CENTER, 0, 0);
    */
}

void DConSetup()
{
    /*
    DCon_Page = lv_page_create(Brain_Scr, NULL);
    lv_obj_align(DCon_Page, Brain_Scr, LV_ALIGN_CENTER, 0, 0);
    */
}
