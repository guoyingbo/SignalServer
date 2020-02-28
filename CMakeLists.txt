# CMakeList.txt: SignalServer 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 2.7)

# 并将名称保存到 DIR_SRCS 变量

aux_source_directory(. DIR_SRCS)

# 指定生成目标

add_executable(SignalServer ${DIR_SRCS})
IF (WIN32)
	target_link_libraries(SignalServer ws2_32)
ENDIF ()

# TODO: 如有需要，请添加测试并安装目标。
