#ifndef _MINIFB_H_
#define _MINIFB_H_

#include "MiniFB_export.h"
#include "MiniFB_version.h"
#include "MiniFB_enums.h"

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef __ANDROID__
#define MFB_RGB(r, g, b)        (((uint32_t) r) << 16) | (((uint32_t) g) << 8) | ((uint32_t) b)
#define MFB_ARGB(a, r, g, b)    (((uint32_t) a) << 24) | (((uint32_t) r) << 16) | (((uint32_t) g) << 8) | ((uint32_t) b)
#else
    #ifdef HOST_WORDS_BIGENDIAN
    #define MFB_RGB(r, g, b)     (((uint32_t) r) << 16) | (((uint32_t) g) << 8) | ((uint32_t) b)
    #define MFB_ARGB(a, r, g, b) (((uint32_t) a) << 24) | (((uint32_t) r) << 16) | (((uint32_t) g) << 8) | ((uint32_t) b)
    #else
    #define MFB_ARGB(r, g, b)    (((uint32_t) a) << 24) | (((uint32_t) b) << 16) | (((uint32_t) g) << 8) | ((uint32_t) r)
    #define MFB_RGB(r, g, b)     (((uint32_t) b) << 16) | (((uint32_t) g) << 8) | ((uint32_t) r)
    #endif
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Create a window that is used to display the buffer sent into the mfb_update function, returns 0 if fails
MFB_EXPORT struct mfb_window * mfb_open(const char *title, unsigned width, unsigned height);
MFB_EXPORT struct mfb_window * mfb_open_ex(const char *title, unsigned width, unsigned height, unsigned flags);

// Update the display
// Input buffer is assumed to be a 32-bit buffer of the size given in the open call
// Will return a negative status if something went wrong or the user want to exit
// Also updates the window events
MFB_EXPORT mfb_update_state    mfb_update(struct mfb_window *window, void *buffer);

MFB_EXPORT mfb_update_state    mfb_update_ex(struct mfb_window *window, void *buffer, unsigned width, unsigned height);

// Only updates the window events
MFB_EXPORT mfb_update_state    mfb_update_events(struct mfb_window *window);

// Close the window
MFB_EXPORT void                mfb_close(struct mfb_window *window);

// Set user data
MFB_EXPORT void                mfb_set_user_data(struct mfb_window *window, void *user_data);
MFB_EXPORT void *              mfb_get_user_data(struct mfb_window *window);

// Set viewport (useful when resize)
MFB_EXPORT bool                mfb_set_viewport(struct mfb_window *window, unsigned offset_x, unsigned offset_y, unsigned width, unsigned height);
// Let mfb to calculate the best fit from your framebuffer original size
MFB_EXPORT bool                mfb_set_viewport_best_fit(struct mfb_window *window, unsigned old_width, unsigned old_height);

// DPI
// [Deprecated]: Probably a better name will be mfb_get_monitor_scale
MFB_EXPORT void                mfb_get_monitor_dpi(struct mfb_window *window, float *dpi_x, float *dpi_y);
// Use this instead
MFB_EXPORT void                mfb_get_monitor_scale(struct mfb_window *window, float *scale_x, float *scale_y);

// Callbacks
MFB_EXPORT void                mfb_set_active_callback(struct mfb_window *window, mfb_active_func callback);
MFB_EXPORT void                mfb_set_resize_callback(struct mfb_window *window, mfb_resize_func callback);
MFB_EXPORT void                mfb_set_close_callback(struct mfb_window* window, mfb_close_func callback);
MFB_EXPORT void                mfb_set_keyboard_callback(struct mfb_window *window, mfb_keyboard_func callback);
MFB_EXPORT void                mfb_set_char_input_callback(struct mfb_window *window, mfb_char_input_func callback);
MFB_EXPORT void                mfb_set_mouse_button_callback(struct mfb_window *window, mfb_mouse_button_func callback);
MFB_EXPORT void                mfb_set_mouse_move_callback(struct mfb_window *window, mfb_mouse_move_func callback);
MFB_EXPORT void                mfb_set_mouse_scroll_callback(struct mfb_window *window, mfb_mouse_scroll_func callback);

// Getters
MFB_EXPORT const char *        mfb_get_key_name(mfb_key key);

MFB_EXPORT bool                mfb_is_window_active(struct mfb_window *window);
MFB_EXPORT unsigned            mfb_get_window_width(struct mfb_window *window);
MFB_EXPORT unsigned            mfb_get_window_height(struct mfb_window *window);
MFB_EXPORT int                 mfb_get_mouse_x(struct mfb_window *window);             // Last mouse pos X
MFB_EXPORT int                 mfb_get_mouse_y(struct mfb_window *window);             // Last mouse pos Y
MFB_EXPORT float               mfb_get_mouse_scroll_x(struct mfb_window *window);      // Mouse wheel X as a sum. When you call this function it resets.
MFB_EXPORT float               mfb_get_mouse_scroll_y(struct mfb_window *window);      // Mouse wheel Y as a sum. When you call this function it resets.
MFB_EXPORT const uint8_t *     mfb_get_mouse_button_buffer(struct mfb_window *window); // One byte for every button. Press (1), Release 0. (up to 8 buttons)
MFB_EXPORT const uint8_t *     mfb_get_key_buffer(struct mfb_window *window);          // One byte for every key. Press (1), Release 0.

// FPS
MFB_EXPORT void                mfb_set_target_fps(uint32_t fps);
MFB_EXPORT unsigned            mfb_get_target_fps(void);
MFB_EXPORT bool                mfb_wait_sync(struct mfb_window *window);

// Timer
MFB_EXPORT struct mfb_timer *  mfb_timer_create(void);
MFB_EXPORT void                mfb_timer_destroy(struct mfb_timer *tmr);
MFB_EXPORT void                mfb_timer_reset(struct mfb_timer *tmr);
MFB_EXPORT double              mfb_timer_now(struct mfb_timer *tmr);
MFB_EXPORT double              mfb_timer_delta(struct mfb_timer *tmr);
MFB_EXPORT double              mfb_timer_get_frequency(void);
MFB_EXPORT double              mfb_timer_get_resolution(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}

#endif

#endif
