
# set (CMAKE_INCLUDE_DIRECTORIES_BEFORE on)

# 指定共享库的路径
link_directories(~/Study/CMake/library/lib)
add_executable(Main main.cpp)

# 包含头文件
INCLUDE_DIRECTORIES( ~/Study/CMake/library/src )
TARGET_LINK_LIBRARIES(Main libhello.so)

# TARGET_LINK_LIBRARIES(Main hello)
# or
# TARGET_LINK_LIBRARIES(Main libhello.so)


