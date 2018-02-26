cmake_minimum_required(VERSION 3.9)
project(spacePaint)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Widgets REQUIRED)


set(SOURCE_FILES MainWindow/MainWindow.cpp
        MainWindow/MainWindow.h
        PaintViewWidget/PaintTool.h
        PaintViewWidget/PaintViewWidget.cpp
        PaintViewWidget/PaintViewWidget.h
        PaintToolsPalette/PaintToolsPalette.cpp
        PaintToolsPalette/PaintToolsPalette.h
        GlobalNames.h
        main.cpp MdiChild/MdiChild.cpp MdiChild/MdiChild.h GlobalNames.cpp
        resources.qrc)

add_executable(spacePaint ${SOURCE_FILES})
target_include_directories(spacePaint PRIVATE "../build-spacePaint-Desktop_Qt_5_10_1_GCC_64bit2-Debug")
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)