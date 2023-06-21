set(LIBHELLO_SRC hello.cpp)

# 指定so文件的输出路径
# ./OUTDIR 的当前路径是bulid的src文件夹
set(OUTPATH "./OUTDIR")
set(LIBRARY_OUTPUT_PATH ${OUTPATH})


# hello 是生成的文件名，如果填入nmae,则生成libname.X
# 生成的类型有三种：
# SHARED      动态库
# STATIC      静态库
# MODULE      在使用dyld的系统有效，如果不支持dyld,会被当成SHARED
add_library(hello SHARED ${LIBHELLO_SRC})



add_library(hello_static STATIC ${LIBHELLO_SRC})
SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
ADD_LIBRARY(hello_static STATIC ${LIBHELLO_SRC})
GET_TARGET_PROPERTY(OUTPUT_VALUE hello_static OUTPUT_NAME)
MESSAGE(STATUS "This is the hello_static OUTPUT_NAME:"${OUTPUT_VALUE})

# VERSION 是动态库版本，SOVERSION 是API版本
Set_target_properties(hello PROPERTIES VERSION 1.2 SOVERSION 1)
