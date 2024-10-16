#include "main.h"
#include "auton_selector.h"

namespace selector {

// Autonomous selector variables
int auton;
int autonCount;
const char *btnmMap[] = {"Auto1", "Auto2", "Auto3", "", "", "", "", "", "", "", ""};  // Up to 10 autonomous routines

// LVGL objects
lv_obj_t *tabview;
lv_obj_t *redBtnm;
lv_obj_t *blueBtnm;

// Red Button Matrix Action
void redBtnmAction(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_obj_t *btnm = lv_event_get_target(e);
        const char *txt = lv_btnmatrix_get_btn_text(btnm, lv_btnmatrix_get_selected_btn(btnm)); // Get selected button's text
        for (int i = 0; i < autonCount; i++) {
            if (strcmp(txt, btnmMap[i]) == 0) {
                auton = i + 1;  // Set auton for red side
            }
        }
    }
}

// Blue Button Matrix Action
void blueBtnmAction(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_obj_t *btnm = lv_event_get_target(e);
        const char *txt = lv_btnmatrix_get_btn_text(btnm, lv_btnmatrix_get_selected_btn(btnm)); // Get selected button's text
        for (int i = 0; i < autonCount; i++) {
            if (strcmp(txt, btnmMap[i]) == 0) {
                auton = -(i + 1);  // Set auton for blue side
            }
        }
    }
}

// Skills Button Action
void skillsBtnAction(lv_event_t *e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        auton = 0;  // Set auton for skills
    }
}

// Watcher for tab changes
int tabWatcher() {
    int activeTab = lv_tabview_get_tab_act(tabview);
    while (true) {
        int currentTab = lv_tabview_get_tab_act(tabview);
        if (currentTab != activeTab) {
            activeTab = currentTab;
            if (activeTab == 0) {
                if (auton == 0) auton = 1;  // Default to first red auton
                auton = abs(auton);
                lv_btnmatrix_set_btn_ctrl(redBtnm, abs(auton) - 1, LV_BTNMATRIX_CTRL_CHECKED); // Set button as selected
            } else if (activeTab == 1) {
                if (auton == 0) auton = -1;  // Default to first blue auton
                auton = -abs(auton);
                lv_btnmatrix_set_btn_ctrl(blueBtnm, abs(auton) - 1, LV_BTNMATRIX_CTRL_CHECKED); // Set button as selected
            } else {
                auton = 0;  // Skills tab
            }
        }
        pros::delay(20);
    }
}

// Initialization function
void init(int hue, int default_auton, const char **autons) {
    int i = 0;
    while (strcmp(autons[i], "") != 0) {
        btnmMap[i] = autons[i];  // Copy autons to button map
        i++;
    }
    autonCount = i;
    auton = default_auton;

    // Set LVGL theme
    lv_theme_t *th = lv_theme_default_init(NULL, hue, LV_THEME_DEFAULT_DARK, LV_FONT_DEFAULT);  // Use the default theme
    lv_disp_set_theme(NULL, th);

    // Create tab view (Red, Blue, Skills tabs)
    tabview = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 40);
    lv_obj_t *redTab = lv_tabview_add_tab(tabview, "Red");
    lv_obj_t *blueTab = lv_tabview_add_tab(tabview, "Blue");
    lv_obj_t *skillsTab = lv_tabview_add_tab(tabview, "Skills");

    // Set default tab based on auton value
    if (auton < 0) {
        lv_tabview_set_act(tabview, 1, LV_ANIM_NONE);  // Blue
    } else if (auton == 0) {
        lv_tabview_set_act(tabview, 2, LV_ANIM_NONE);  // Skills
    }

    // Create button matrix for Red tab
    redBtnm = lv_btnmatrix_create(redTab);
    lv_btnmatrix_set_map(redBtnm, btnmMap);
    lv_obj_add_event_cb(redBtnm, redBtnmAction, LV_EVENT_CLICKED, NULL); // Register event callback for Red button matrix
    lv_btnmatrix_set_btn_ctrl(redBtnm, abs(auton) - 1, LV_BTNMATRIX_CTRL_CHECKED);  // Set default selected button
    lv_obj_set_size(redBtnm, 450, 50);
    lv_obj_align(redBtnm, LV_ALIGN_CENTER, 0, 0);

    // Create button matrix for Blue tab
    blueBtnm = lv_btnmatrix_create(blueTab);
    lv_btnmatrix_set_map(blueBtnm, btnmMap);
    lv_obj_add_event_cb(blueBtnm, blueBtnmAction, LV_EVENT_CLICKED, NULL); // Register event callback for Blue button matrix
    lv_btnmatrix_set_btn_ctrl(blueBtnm, abs(auton) - 1, LV_BTNMATRIX_CTRL_CHECKED);  // Set default selected button
    lv_obj_set_size(blueBtnm, 450, 50);
    lv_obj_align(blueBtnm, LV_ALIGN_CENTER, 0, 0);

    // Create Skills button
    lv_obj_t *skillsBtn = lv_btn_create(skillsTab);
    lv_obj_t *label = lv_label_create(skillsBtn);
    lv_label_set_text(label, "Skills");
    lv_obj_set_size(skillsBtn, 450, 50);
    lv_obj_align(skillsBtn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(skillsBtn, skillsBtnAction, LV_EVENT_CLICKED, NULL); // Register event callback for Skills button

    // Start tab watcher task
    pros::Task tabWatcher_task(tabWatcher);
}

} // namespace selector
