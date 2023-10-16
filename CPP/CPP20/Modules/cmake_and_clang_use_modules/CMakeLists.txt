set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
cmake_minimum_required(VERSION 3.27)
project(Test CXX)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)

# Skip this line if you're using Clang (>= 16)
include(cxx_modules_rules_clang.cmake)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




# find_package(Qt6 COMPONENTS
#         Core
#         Gui
#         Widgets
#         Charts
#         REQUIRED)





add_library(TestModules)
target_sources(TestModules
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        Temp.cppm
)


add_executable(Test
    main.cpp 
)
 target_link_libraries(Test
#         Qt::Core
#         Qt::Gui
#         Qt::Widgets
#         Qt::Charts
         TestModules
         )

