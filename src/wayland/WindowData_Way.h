#pragma once

#include <MiniFB_types.h>
#include <stdint.h>
#include <wayland-client.h>
#include "xdg-shell-protocol.h"

typedef struct
{
    struct wl_display       *display;
    struct wl_registry      *registry;
    struct wl_compositor    *compositor;
    struct xdg_wm_base      *xdg_wm_base;
    struct wl_seat          *seat;
    struct wl_keyboard      *keyboard;
    
    struct wl_pointer       *pointer;
    struct wl_cursor_theme  *cursor_theme;
    struct wl_cursor        *default_cursor;
    struct wl_surface       *cursor_surface;
    
    struct wl_shm           *shm;
    struct wl_shm_pool      *shm_pool;
    struct wl_surface       *surface;
    struct xdg_surface      *xdg_surface;
    struct xdg_toplevel     *xdg_toplevel;

    uint32_t                seat_version;
    uint32_t                shm_format;
    uint32_t                *shm_ptr;

    int                     fd;
    
    struct mfb_timer        *timer;
} SWindowData_Way;
