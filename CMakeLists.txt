PROJECT(ralph)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# 输出编译过程详细信息
set(CMAKE_VERBOSE_MAKEFILE on)


# gtest 如果没有在标准安装位置
# INCLUDE_DIRECTORIES(/data/users/berniezhao/usr/include/)
# 
# LINK_DIRECTORIES(/data/users/berniezhao/usr/lib)



#
# for ut
#
ADD_EXECUTABLE(test_options ut/test_option.cpp)
TARGET_INCLUDE_DIRECTORIES(test_options PUBLIC ..)

ADD_EXECUTABLE(test_arrlist ut/test_arrlist.cpp)
TARGET_INCLUDE_DIRECTORIES(test_arrlist PUBLIC ..)
TARGET_LINK_LIBRARIES(test_arrlist gtest pthread)

ADD_EXECUTABLE(test_string_util ut/test_string_util.cpp
                                common/string_util.cpp)
TARGET_INCLUDE_DIRECTORIES(test_string_util PUBLIC  ..)
TARGET_LINK_LIBRARIES(test_string_util gtest pthread)

ADD_EXECUTABLE(test_logger ut/test_logger.cpp
                           common/logger.cpp
                           common/wrapper.cpp)
TARGET_INCLUDE_DIRECTORIES(test_logger PUBLIC  ..)

#
# for server
#
ADD_EXECUTABLE(server common/notifier.cpp
                      common/logger.cpp
                      common/wrapper.cpp
                      server/configure.cpp
                      server/acceptor.cpp
                      server/main.cpp)
TARGET_INCLUDE_DIRECTORIES(server PUBLIC  ..)
TARGET_LINK_LIBRARIES(server gtest jsoncpp pthread)

set(CMAKE_CXX_FLAGS "-std=c++11 -g -Wall -Wreturn-type -Wunused-value -Wunused-parameter -Wsign-conversion -Wparentheses")

# 可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH bin)
