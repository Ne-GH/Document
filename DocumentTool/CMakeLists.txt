cmake_minimum_required(VERSION 3.26)
project(DocumentTool)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        MainWindow.h MainWindow.cpp MainWindow.ui


        SettingDialog.cpp SettingDialog.h)
target_link_libraries(${PROJECT_NAME}
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Sql

        )

