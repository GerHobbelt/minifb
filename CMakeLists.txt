cmake_minimum_required(VERSION 3.7)

set(PROJECT_NAME MiniFB-native)
set(PROJECT_VERSION 0.7.0)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

message(STATUS "Processing " ${PROJECT_NAME})

include(GNUInstallDirs)

# Detect iOS
#--------------------------------------
if(NOT DEFINED IOS)
    if(DEFINED CMAKE_SYSTEM_NAME)
        string(TOLOWER CMAKE_SYSTEM_NAME CMAKE_SYSTEM_NAME_LOWER)
        if(CMAKE_SYSTEM_NAME_LOWER STREQUAL "ios")
            set(IOS true)
        endif()
    endif()
endif()

# Sources
#--------------------------------------
set(SrcLib
    include/MiniFB.h
    include/MiniFB_export.h
    include/MiniFB_version.h
    include/MiniFB_enums.h

    src/MiniFB_version.c
    src/MiniFB_common.c
    src/MiniFB_internal.c
    src/MiniFB_internal.h
    src/MiniFB_timer.c
    src/WindowData.h
)

#--
set(SrcWindows
    src/windows/WinMiniFB.c
    src/windows/WindowData_Win.h
)

#--
set(SrcMacOSX
    src/macosx/MacMiniFB.m
    src/macosx/OSXWindow.h
    src/macosx/OSXWindow.m
    src/macosx/OSXView.h
    src/macosx/OSXView.m
    src/macosx/OSXViewDelegate.h
    src/macosx/OSXViewDelegate.m
    src/macosx/WindowData_OSX.h
)

#--
set(SrcIOS
    src/ios/WindowData_IOS.h
    src/ios/iOSMiniFB.m
    src/ios/iOSView.h
    src/ios/iOSView.m
    src/ios/iOSViewController.h
    src/ios/iOSViewController.m
    src/ios/iOSViewDelegate.h
    src/ios/iOSViewDelegate.m
    include/MiniFB_ios.h
)

#--
set(SrcWayland
    src/wayland/xdg-shell-protocol.h
    src/wayland/xdg-shell-protocol.c
    src/wayland/WaylandMiniFB.c
    src/wayland/WindowData_Way.h
    src/MiniFB_linux.c
)

#--
set(SrcX11
    src/x11/X11MiniFB.c
    src/x11/WindowData_X11.h
    src/MiniFB_linux.c
)

set(SrcGL
    src/gl/MiniFB_GL.h
    src/gl/MiniFB_GL.c
)

#--
set(SrcWeb
    src/web/WebMiniFB.c
)

# Set features
#--------------------------------------
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Code generation options
#--------------------------------------

if(APPLE AND NOT IOS)
    option(USE_METAL_API "Build the project using metal API code" ON)
    option(USE_INVERTED_Y_ON_MACOS "Use default mouse position: (0, 0) at (left, down)" OFF)
elseif(UNIX)
    if (NOT EMSCRIPTEN)
        option(USE_WAYLAND_API "Build the project using wayland API code" OFF)
        if(NOT USE_WAYLAND_API)
            option(USE_OPENGL_API "Build the project using OpenGL API code" ON)
        endif()
    endif()
elseif(WIN32)
    option(USE_OPENGL_API "Build the project using OpenGL API code" ON)
endif()

# Set GCC/Clang flags
#--------------------------------------

# Of course we have to enforce this also on Windows when using MSVC,
# since our managed library and our native library would be both named "minifb.dll" instead
set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
set(CMAKE_STATIC_LIBRARY_PREFIX "lib")

if(NOT MSVC)
    # Avoid default flag values
    #--------------------------------------
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "" )
    set(CMAKE_C_FLAGS_RELEASE "")

    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")

    set(CMAKE_OBJC_FLAGS "")
    set(CMAKE_OBJC_FLAGS_DEBUG "")
    set(CMAKE_OBJC_FLAGS_RELEASE "")

    set(CMAKE_OBJCXX_FLAGS "")
    set(CMAKE_OBJCXX_FLAGS_DEBUG "")
    set(CMAKE_OBJCXX_FLAGS_RELEASE "")

    # Set our flags
    #--------------------------------------
    add_compile_options("$<$<CONFIG:Debug>:-g>")
    add_compile_options("$<IF:$<CONFIG:Debug>,-O0,-O2>")
    add_compile_options(-Wall -Wextra)
    add_compile_options(-Wno-switch -Wno-unused-function -Wno-unused-parameter -Wno-implicit-fallthrough)

    if(NOT APPLE)
        add_compile_options(-Wno-cast-function-type)
    endif()
else()
    # Security check
    add_compile_options(/GS)
    # Function level linking
    add_compile_options(/Gy)
    # Exceptions
    add_compile_options(/EHsc)
    if(MSVC_VERSION GREATER_EQUAL 1900)
        # SDL checks 2015+
        add_compile_options(/sdl)
    endif()
    if(MSVC_VERSION LESS_EQUAL 1920)
        # Enable Minimal Rebuild (required for Edit and Continue) (deprecated)
        add_compile_options(/Gm)
    endif()
    add_compile_options(/fp:fast)
    # Program database for edit and continue
    add_compile_options("$<IF:$<CONFIG:Debug>,/ZI,/Zi>")
    # Optimizations
    add_compile_options("$<IF:$<CONFIG:Debug>,/Od,/O2>")
    # Inline function expansion
    add_compile_options("$<IF:$<CONFIG:Debug>,/Ob0,/Ob2>")
    # Basic runtime checks
    add_compile_options("$<$<CONFIG:Debug>:/RTC1>")
    # Force Visual Studio to actualize __cplusplus version macro
    add_compile_options(/Zc:__cplusplus)

    # Disable incremental linking
    add_link_options("/INCREMENTAL:NO")

endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
    add_definitions(-DDEBUG)
    if(EMSCRIPTEN)
        add_link_options(-g)
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(NOT MSVC)
        # Strip
        add_link_options(-s)
    else()
        # Remove unreferenced sections, merge identical sections
        add_link_options("/OPT:REF /OPT:ICF")
    endif()
endif()

# Set compiler/platform specific flags and dependencies
#--------------------------------------
if(WIN32)

    add_definitions(-DWIN_TARGET)

    if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif()
    add_definitions(-D_WIN32_WINNT=0x0601)  # Windows 7 (we are in 2020)

    if(USE_OPENGL_API)
        list(APPEND SrcLib ${SrcGL})

        add_definitions(-DUSE_OPENGL_API)
    endif()

    list(APPEND SrcLib ${SrcWindows})

elseif(IOS)

    add_definitions(-DIOS_TARGET)

    list(APPEND SrcLib ${SrcIOS})

elseif(APPLE)

    add_definitions(-DMACOS_TARGET)

    if(USE_METAL_API)
        add_definitions(-DUSE_METAL_API)
    endif()

    if(USE_INVERTED_Y_ON_MACOS)
        add_definitions(-DUSE_INVERTED_Y_ON_MACOS)
    endif()

    list(APPEND SrcLib ${SrcMacOSX})

elseif(UNIX)

    if(USE_WAYLAND_API)
        add_definitions(-DUNIX_TARGET -DUSE_WAYLAND_API)

        list(APPEND SrcLib ${SrcWayland})
    elseif(EMSCRIPTEN)
        add_definitions(-DEMSCRIPTEN_TARGET)

        list(APPEND SrcLib ${SrcWeb})
    else()
        add_definitions(-DUNIX_TARGET)

        if(USE_OPENGL_API)
            list(APPEND SrcLib ${SrcGL})

            add_definitions(-DUSE_OPENGL_API)
        endif()
        list(APPEND SrcLib ${SrcX11})
    endif()

endif()

add_definitions(
    -DMFB_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    -DMFB_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    -DMFB_VERSION_PATCH=${PROJECT_VERSION_PATCH}
)

# Versioning
#--------------------------------------
if(WIN32)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.rc
        @ONLY
    )
    list(APPEND SrcLib ${CMAKE_CURRENT_BINARY_DIR}/version.rc)

endif()

# Library
#--------------------------------------
add_library(minifb SHARED
    ${SrcLib}
)
set_target_properties(minifb PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    OUTPUT_NAME "minifb$<IF:$<BOOL:${USE_METAL_API}>,-metal,$<$<BOOL:${USE_WAYLAND_API}>:-wayland>>"
)

# Link
#--------------------------------------
if(APPLE)

    if(IOS)
        target_link_libraries(minifb PRIVATE
            "-framework UIKit"
            "-framework QuartzCore"
            "-framework Metal"
            "-framework MetalKit"
        )
    else()
        target_link_libraries(minifb PRIVATE
            "-framework Cocoa"
            "-framework QuartzCore"
            "-framework Metal"
            "-framework MetalKit"
        )
    endif()

elseif(UNIX)

    if(USE_WAYLAND_API)
        target_link_libraries(minifb PRIVATE
            "-lwayland-client"
            "-lwayland-cursor"
        )
    elseif(EMSCRIPTEN)
        add_link_options(
            "-sSTRICT=1"
            "-sENVIRONMENT=web"
            "-sLLD_REPORT_UNDEFINED"
            "-sMODULARIZE=1"
            "-sALLOW_MEMORY_GROWTH=1"
            "-sALLOW_TABLE_GROWTH"
            "-sMALLOC=emmalloc"
            "-sEXPORT_ALL=1"
            "-sEXPORTED_FUNCTIONS=[\"_malloc\",\"_free\",\"_main\"]"
            "-sEXPORTED_RUNTIME_METHODS=ccall,cwrap"
            "-sASYNCIFY"
            "--no-entry"
            "-sSINGLE_FILE"
        )
    else()
        target_link_libraries(minifb PRIVATE
            "-lX11"
            #"-lxkbcommon"
            #"-lXrandr" DPI NOT WORKING
        )
        if(USE_OPENGL_API)
        target_link_libraries(minifb PRIVATE
            "-lGL"
        )
        endif()
    endif()

elseif(WIN32)

    if(USE_OPENGL_API)
        target_link_libraries(minifb PRIVATE
            "Opengl32.lib"
        )
    endif()

    target_link_libraries(minifb PRIVATE
        "gdi32.lib"
        "winmm.lib"
    )

endif()

# For all projects
#--------------------------------------
target_include_directories(minifb PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_include_directories(minifb PRIVATE src)

link_libraries(minifb)

# Organize IDE Folders
#--------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET minifb PROPERTY FOLDER "Libs")

install(TARGETS minifb EXPORT minifb)
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_LIST_DIR}/include/*.h")
install(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT minifb FILE minifb-config.cmake DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/minifb" NAMESPACE minifb::)

message(STATUS "Done " ${PROJECT_NAME})
