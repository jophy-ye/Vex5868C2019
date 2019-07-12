#include <cstdint>

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
            lv_obj_set_hidden(Auton_Page, true);
            lv_obj_set_hidden(DCon_Page, true);
            if (GameStatus == Initialize)
            {
                lv_obj_set_hidden(Init_Page, false);
                PreviousStatus = Initialize;
            }
            else if (GameStatus == Autonomous)
            {
                lv_obj_set_hidden(Auton_Page, false);
                PreviousStatus = Autonomous;
            }
            else if (GameStatus == DriverControl)
            {
                lv_obj_set_hidden(DCon_Page, false);
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
    Init_Robot_Stat_Comp_Status_Label = lv_label_create(Init_Robot_Stat_Tab, NULL);
    Init_Robot_Stat_Cont_Battery_Cap_Label = lv_label_create(Init_Robot_Stat_Tab, NULL);
    lv_obj_align(Init_Robot_Stat_Battery_Volt_Label, Init_Robot_Stat_Tab, 
                LV_ALIGN_CENTER, 0, 68);
    lv_obj_align(Init_Robot_Stat_Comp_Status_Label, Init_Robot_Stat_Battery_Volt_Label,
                LV_ALIGN_CENTER, 0, 68);
    lv_obj_align(Init_Robot_Stat_Cont_Battery_Cap_Label, Init_Robot_Stat_Comp_Status_Label,
                LV_ALIGN_CENTER, 0, 68);
    Init_Robot_Stat_Ref_Btn = lv_btn_create(Init_Robot_Stat_Tab, NULL);
    lv_obj_align(Init_Robot_Stat_Ref_Btn, NULL, LV_ALIGN_IN_BOTTOM_RIGHT, 0, 0);
    lv_btn_set_action(Init_Robot_Stat_Ref_Btn, LV_BTN_ACTION_CLICK, LoadStatus_Action);

    LoadStatus_Action(Init_Robot_Stat_Ref_Btn); // call function to load data manually
}

static lv_res_t LoadStatus_Action(lv_obj_t* RefreshButton)
{
    // retrieve all data as reported by the vexos
    double BatteryVoltage = pros::battery::get_voltage();
    std::uint8_t CompStatus = pros::competition::get_status();
    std::int32_t ContBatteryLevel = pros::c::controller_get_battery_level(pros::E_CONTROLLER_MASTER);

    // print the data on the screen
    char buffer[32];
    buffer[0] = '\0';
    snprintf(buffer, 32, "Robot Battery Voltage: %f", BatteryVoltage);
    lv_label_set_text(Init_Robot_Stat_Battery_Volt_Label, buffer);
    buffer[0] = '\0';
    switch(CompStatus)
    {
        case COMPETITION_DISABLED: snprintf(buffer, 30, "Competition Status: Enabled"); break;
        case COMPETITION_CONNECTED: snprintf(buffer, 30, "Competition Status: Connected"); break;
        case COMPETITION_AUTONOMOUS: snprintf(buffer, 30, "Competition Status: Autonomous"); break;
    }
    lv_label_set_text(Init_Robot_Stat_Comp_Status_Label, buffer);
    buffer[0] = '\0';
    snprintf(buffer, 32, "Controller Battery Level: %d", ContBatteryLevel);
    lv_label_set_text(Init_Robot_Stat_Cont_Battery_Cap_Label, buffer);
    

    return LV_RES_OK;
}

void AutonSetup()
{
    
}

void DConSetup()
{
    
}