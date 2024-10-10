#include "main.h"
#include "lemlib/api.hpp"
#include "globals.h"
#include "driver.h"
#include "auton.h"

void drivhari() {
    // loop forever
    while (true) {
        // get left y and right y positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
        int checkcommit = 7;

        // move the robot
        
        chassis.curvature(-rightY,  -leftY);

        // delay to save resources
        pros::delay(25);
    }
}


bool rollerOnL = false;  
bool buttonPressedL = false;

bool rollerOnR = false;  
bool buttonPressedR = false;
void roller(){

    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && !buttonPressedL) {
            buttonPressedL = true; 

            rollerOnL = !rollerOnL; 

            if (rollerOnL) {
                top_down_roller.move(-127); // Start roller at 100 RPM
                
            } else {
                top_down_roller.move(0); // Stop the roller
            } 
    }

    if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            buttonPressedL = false; 
    }



    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && !buttonPressedR) {
            buttonPressedR = true; 

            rollerOnR = !rollerOnR; 

            if (rollerOnR) {
                top_down_roller.move(127); // Start roller at 100 RPM
                
            } else {
                top_down_roller.move(0); // Stop the roller
            } 
    }

        // Reset the buttonPressed flag when L1 is released
    if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            buttonPressedR = false; // Ready to detect next press
    }
    
    

}
