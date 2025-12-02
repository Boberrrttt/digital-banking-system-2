#ifndef EEZ_LVGL_UI_GUI_H
#define EEZ_LVGL_UI_GUI_H

#include <lvgl/lvgl.h>

#if defined(EEZ_FOR_LVGL)
#include <eez/flow/lvgl_api.h>
#endif

#if !defined(EEZ_FOR_LVGL)
#include "screens.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

void ui_init();
void ui_tick();

#if !defined(EEZ_FOR_LVGL)
void loadScreen(enum ScreensEnum screenId);
#endif

// ➜ ADD THIS LINE (GLOBAL LIST DECLARATION)
extern lv_obj_t *transaction_list;

#ifdef __cplusplus
}
#endif
#endif

