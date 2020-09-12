cmake_minimum_required(VERSION 2.8.3)
project(ReadRomeConfig)


find_package(OpenCV REQUIRED)

#-------------------------------------------路径添加-----------------------

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)


#----------------------------------------------宏定义第三方库---------------

set(THIRDPARTY_LIBS
        #暂时使用的是OpenCV3.4
        ${OpenCV_LIBS}
        # 还可以继续往下面添加
        #${PROJECT_SOURCE_DIR}/thirdparty/g2o/lib/libg2o.so
        #${PROJECT_SOURCE_DIR}/thirdparty/DBoW2/lib/libDBoW2.so
        )


#------------------------------------------------编译自己的库-----------------

add_library(config_lib
#cpp files
  src/config/config.cpp
#header
  include/config/config.h
        )

target_link_libraries(config_lib ${THIRDPARTY_LIBS}  )



#--------------------------------------------------------
#测试文件
add_executable( config_test test/config_test.cpp)
target_link_libraries(config_test ${THIRDPARTY_LIBS}  config_lib )
