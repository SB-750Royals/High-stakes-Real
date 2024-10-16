#include "main.h"
#include "lemlib/api.hpp"
#include "driver.hpp"
#include "globals.hpp"

void drivehari() {
    // get left y and right x joysticks
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    // move the robot
    chassis.curvature(-rightY,  -leftY);

    // delay to save resources
    pros::delay(25);
    
}

bool extended = false;
void pistons() {

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        extended = !extended;
        if(extended){
            piston1.extend();
            piston2.extend();
        }
        if(!extended==false){
            piston1.retract();
            piston2.retract();
        }
    }
   


}

bool rollerOnF = false;
bool rollerOnR = false;
void roller(){

    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
        rollerOnF=!rollerOnF;
        if(rollerOnF){
            top_down_roller.move(127);
        }
        if(!rollerOnF){
            top_down_roller.move(0);
        }
    }   


    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
        rollerOnR=!rollerOnR;
        if(rollerOnR){
            top_down_roller.move(-127);
        }
        if(!rollerOnR){
            top_down_roller.move(0);
        }
    }    
}