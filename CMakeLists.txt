## This file is a quick tutorial on writing CMakeLists for targeting the Vita
cmake_minimum_required(VERSION 2.8)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

## Define project parameters here
# Name of the project
project(rRootage)
# This line adds Vita helper macros, must go after project definition in order
# to build Vita specific artifacts (self/vpk).
include("${VITASDK}/share/vita.cmake" REQUIRED)

set (CMAKE_CXX_STANDARD 14)

## Configuration options for this app
# Display name (under bubble in LiveArea)
set(VITA_APP_NAME "rRootage")
# Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X =
# unique string of developer and Y = a unique number for this app
set(VITA_TITLEID  "RRKK00002")
# Optional version string to show in LiveArea's more info screen
set(VITA_VERSION  "01.00")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

# Add any additional include paths here
include_directories(
    $ENV{VITASDK}/arm-vita-eabi/include/SDL
    $ENV{VITASDK}/arm-vita-eabi/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/tinyxml

    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/boost
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/boost/config
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/boost/detail
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/boost/config/compiler
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/boost/config/platform
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/bulletml/boost/config/stdlib
  
  
    

)

# Add any additional library paths here
# ${CMAKE_CURRENT_BINARY_DIR} lets you use any library currently being built
link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  $ENV{VITASDK}/arm-vita-eabi/lib/
)

## Build and link
# Add all the files needed to compile here
add_executable(${PROJECT_NAME}
  src/attractmanager.c
  src/background.c
  src/barragemanager.cc
  src/boss.cc
  src/degutil.c
  src/foe.cc
  src/foecommand.cc
  src/frag.c
  src/laser.c
  src/letterrender.c
  src/mt19937int.c
  src/rand.c
  src/rr.c
  src/screen.c
  src/ship.c
  src/shot.c
  src/soundmanager.c
  src/vector.c

  
)

# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(${PROJECT_NAME}
  
  vitaGL
  bulletml
  tinyxml

  SDL_gfx
  SDL_mixer
  SDL_image
  SDL_ttf
  SDL
  vorbisfile
  vorbis
  ogg
  mikmod
  jpeg
  png
  webp
  FLAC
  pthread
  imgui
  
  vitashark
  mathneon

  
  SceIofilemgrForDriver_stub 
  SceLibKernel_stub
  SceAppMgr_stub
  SceAppUtil_stub
  SceAudio_stub
  SceCommonDialog_stub
  SceCtrl_stub
  SceDisplay_stub
  SceGxm_stub
  SceHid_stub
  SceKernelDmacMgr_stub
  ScePower_stub
  SceShaccCg_stub
  SceShaccCgExt
  SceSysmodule_stub
  SceTouch_stub
  taihen_stub  
)

## Create Vita files
vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
# The FILE directive lets you add additional files to the VPK, the syntax is
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  FILE sounds sounds
  FILE simple simple
  FILE reversible reversible
  FILE psy psy
  FILE normal normal
  FILE morph morph
  FILE morph_heavy morph_heavy
  FILE images images


)
