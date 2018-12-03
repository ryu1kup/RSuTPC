#
# CMakeLists.txt
#

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(NAME_MAIN_PROGRAM RSuTPC_G4p10)
project(${NAME_MAIN_PROGRAM})

# set cxx flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++11")

# ---------- Geant4 ----------
# set the path to Geant4 library
set(Geant4_DIR  /home/ueno/local/geant4/lib64/Geant4-10.3.3)

# locate Geant4 package
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

# Geant4 include directories
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
# ---------------------------

# ---------- ROOT -----------
# tell cmake where to find ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# locate ROOT package
find_package(ROOT REQUIRED COMPONENTS RIO)

# ROOT include directories
include_directories(${CURRENT_SOURCE_DIR}/include)
include_directories(${ROOT_INCLUDE_DIRS})
# ---------------------------

# locate sources and headers
file(GLOB SRCS ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB INCS ${PROJECT_SOURCE_DIR}/include/*.hh)

# compile and link your application
add_executable(${NAME_MAIN_PROGRAM} ${NAME_MAIN_PROGRAM}.cc ${SRCS} ${INCS})
target_link_libraries(${NAME_MAIN_PROGRAM} ${Geant4_LIBRARIES})
target_link_libraries(${NAME_MAIN_PROGRAM} ${ROOT_LIBRARIES})

# install
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
install(TARGETS ${NAME_MAIN_PROGRAM} DESTINATION bin)
