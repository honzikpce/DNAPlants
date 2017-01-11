cmake_minimum_required(VERSION 3.6)
project(DNAPlants)

# directories with header files
include_directories(
        ~/Dropbox/dev/headers)

# directories with libraries
link_directories(
        ~/Dropbox/dev/libs)

set(LIBS_PATH ~/Dropbox/dev/libs)

#file(GLOB DYN_LIBRARIES "/Users/cablegibbon443/Dropbox/dev/libs/*.dylib")
#message("Dynamic libraries : = ${DYN_LIBRARIES}")


#file(GLOB GLEW_LIB "/usr/local/lib/libGLEW.dylib")
#message("GLEW lib : = ${GLEW_LIB}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


# OPENGL load
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# SDL2 load
find_package(SDL2 REQUIRED)
set(SDL2_LIBRARY "/Library/Frameworks/SDL2.framework")
include_directories(${SDL2_INCLUDE_DIR})

# SDL_mixer and SDL_ttf
#find_package(SDL_mixer REQUIRED)
#find_package(SDL_ttf REQUIRED)

# load Box2d
#set(BOX2D_LIB_PATH ~/Dropbox/dev/libs)
#FIND_LIBRARY(BOX2D_LIB
#        NAMES Box2D
#        PATHS ${BOX2D_LIB_PATH}
#        )



# load JN framework
set(JN_LIB_PATH ~/Dropbox/dev)
set(JN_INC_PATH ~/Dropbox/dev/JN.framework)

FIND_LIBRARY(JN_LIB
        NAMES JN
        PATHS ${JN_LIB_PATH}
        )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JN REQUIRED_VARS JN_LIB JN_INC_PATH)


# load ROCKET framework
set(ROCKET_LIB_PATH ~/Dropbox/dev/libs)
set(JN_INC_PATH ~/Dropbox/dev/libs/Rocket.framework)

FIND_LIBRARY(ROCKET_LIB
        NAMES Rocket
        PATHS ${ROCKET_LIB_PATH}
        )
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(Rocket REQUIRED_VARS ROCKET_LIB ROCKET_LIB_PATH)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        App.cpp
        App.h GreenHouse.cpp GreenHouse.h ConstsAndTypes.h Flower.cpp Flower.h DragDropListener.cpp DragDropListener.h FlowerContainer.cpp FlowerContainer.h ProgressBar.cpp ProgressBar.h MainMenu.cpp MainMenu.h InsectBug.cpp InsectBug.h
        RandomNumbers.cpp RandomNumbers.hpp)
add_executable(DNAPlants ${SOURCE_FILES})

target_link_libraries(DNAPlants ${OPENGL_LIBRARIES} ${SDL2_LIBRARY} ${JN_LIB} ${ROCKET_LIB})