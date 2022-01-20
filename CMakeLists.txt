cmake_minimum_required(VERSION 3.8)
project(generator)
enable_language(C CXX)

include (${PROJECT_SOURCE_DIR}/cmake/extensions.cmake)

#====================
# Configure options
#====================
option(CONFIG_UNIT_TEST     "Enable uint test for module" OFF)

#Log
option(SPDLOG_COMPILED_LIB  "Enable spdlog library" ON)
option(SPDLOG_SHARED_LIB    "Build spdlib as shared library" OFF)


if (POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif(POLICY CMP0076)
message(STATUS "CONFIG_UNIT_TEST = ${CONFIG_UNIT_TEST}")

#=========================
# Select operation system
#=========================
message(STATUS "OS Platform: ${CMAKE_SYSTEM_NAME}")
if (CMAKE_HOST_WIN32)
    enable_language(RC)
    set(WINDOWS TRUE)
    add_compile_options(/wd4819)
    add_compile_options(/wd4996)
    add_compile_options(/wd5105)
    add_compile_options(/wd4129)
    add_compile_options(/wd4200)
elseif (CMAKE_HOST_APPLE)
    set(MACOS TRUE)
elseif (CMAKE_HOST_UNIX)
    set(LINUX TRUE)
else ()
  message(FATAL_ERROR "Unknown operation system")
endif ()

#=====================
# Find depend package
#=====================
set(SOURCE_FILES empty.c)
set(EXTRA_LIBS )
if (LINUX)
  add_definitions(-include config.h)
elseif (WINDOWS)
    set(PREINCLUDE /FI"config.h")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${PREINCLUDE}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PREINCLUDE}")
    add_compile_options(/utf-8)
endif()

#=========================
# Global compile options
#=========================
include_directories(
  ${PROJECT_SOURCE_DIR}
)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

# Generate executable file
if (CONFIG_UNIT_TEST)
    set(TARGET_NAME gtest_main)
else()
    set(TARGET_NAME ${PROJECT_NAME})
endif()

add_executable(${TARGET_NAME} ${SOURCE_FILES})

# Add subdirectories
if (CONFIG_UNIT_TEST)
    add_subdirectory(testsuite)
endif()
add_subdirectory(lib)
add_subdirectory(base)
add_subdirectory(src)


#=================
# Link target
#=================
collect_link_libraries(libs ${TARGET_NAME})
if (LINUX)
  target_link_libraries(${TARGET_NAME} 
    -Wl,--start-group
    ${libs}
    -Wl,--end-group
    ${SDL2_LIBRARIES}
    ${EXTRA_LIBS}
  )
else()
  target_link_libraries(${TARGET_NAME} 
    ${libs}
    ${SDL2_LIBRARIES}
    ${EXTRA_LIBS}
  )
endif()

#==========================
# Generate configure file
#==========================
configure_file(${PROJECT_SOURCE_DIR}/config.h.in 
               ${PROJECT_SOURCE_DIR}/config.h 
               @ONLY)

#================
# Debug command
#================
if (LINUX)
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
  add_custom_target(gdb 
    COMMAND 
    {CMAKE_DEBUGER} ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}
  )
endif()