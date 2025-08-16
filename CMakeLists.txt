cmake_minimum_required(VERSION 3.20)
project(X LANGUAGES CXX C ASM)  # 添加 ASM 支持（嵌入式常需汇编启动文件）

# 选择build方式：0-ARM、1-Win
set(BUILD_FLGS 0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Using C++ standard: ${CMAKE_CXX_STANDARD}")

# 输出目录（ELF 文件生成路径）
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})

include_directories(${PROJECT_SOURCE_DIR}/inc
    ${PROJECT_SOURCE_DIR}/inc/datastruct
    ${PROJECT_SOURCE_DIR}/inc/posix
    ${PROJECT_SOURCE_DIR}/inc/res
    ${PROJECT_SOURCE_DIR}/inc/res/other"
    ${PROJECT_SOURCE_DIR}/inc/res/other/stm32f103c6t6"
)

if(BUILD_FLGS)
message("Windows of Build")

# 添加可执行目标
add_executable(${PROJECT_NAME})

# 递归添加所有源文件
file(GLOB_RECURSE SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
)

# 添加源文件到目标
target_sources(${PROJECT_NAME} PRIVATE
    ${SOURCES}
)

else()
message("ARM Cortex-m of Build")

# 添加源文件（需包含启动文件 startup_*.s 等汇编文件）
file(GLOB_RECURSE SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.c
    ${PROJECT_SOURCE_DIR}/startup/stm32f103c6t6.s  
)

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(X PROPERTIES OUTPUT_NAME "X.elf")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin
)
endif()








