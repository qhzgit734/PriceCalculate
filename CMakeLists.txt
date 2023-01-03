cmake_minimum_required(VERSION 3.5) # CMake install : https://cmake.org/download/
project(PriceCalculate LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "d:/soft/Qt/6.4.1/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

aux_source_directory(./src SRC_LIST)
qt6_add_resources(QRC_LIST ./resource/Resource.qrc)

add_executable(${PROJECT_NAME}
    WIN32 # If you need a terminal for debug, please comment this statement 
    ${SRC_LIST} 
    ${QRC_LIST}
    ./resource/logo.rc
) 

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)