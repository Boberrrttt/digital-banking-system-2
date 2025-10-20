# src/ui/CMakeLists.txt

# Collect all C files in DBS_UI/src/ui
file(GLOB UI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/DBS_UI/src/ui/*.c"
)

add_library(ui ${UI_SOURCES})

# Include the folders needed by LVGL and your UI
target_include_directories(ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/DBS_UI/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lvgl
)

# Link with LVGL library so it can find lvgl/lvgl.h and symbols
target_link_libraries(ui PRIVATE lvgl)

