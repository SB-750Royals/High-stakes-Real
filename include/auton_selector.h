#ifndef SELECTION_H
#define SELECTION_H

#include "lvgl/lvgl.h"
#include "pros/apix.h"
#include <cstring>  

namespace selector {

    extern int auton;
    extern int autonCount;

    extern const char *btnmMap[];

    extern lv_obj_t *tabview;
    extern lv_obj_t *redBtnm;
    extern lv_obj_t *blueBtnm;

    lv_res_t redBtnmAction(lv_obj_t *btnm, const char *txt);
    lv_res_t blueBtnmAction(lv_obj_t *btnm, const char *txt);
    lv_res_t skillsBtnAction(lv_obj_t *btn);

    int tabWatcher();

    void init(int hue, int default_auton, const char **autons);

} // namespace selector

#endif // SELECTION_H
