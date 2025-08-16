# 定义目标系统为裸机环境
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# 禁用所有编译器测试
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 设置编译器路径
set(CMAKE_C_COMPILER "d:/GUN/Cortex_m/14.2_rel1/bin/arm-none-eabi-gcc.exe")
set(CMAKE_CXX_COMPILER "d:/GUN/Cortex_m/14.2_rel1/bin/arm-none-eabi-g++.exe")
set(CMAKE_ASM_COMPILER "d:/GUN/Cortex_m/14.2_rel1/bin/arm-none-eabi-gcc.exe")

# 设置二进制工具链
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_NM arm-none-eabi-nm)
set(CMAKE_RANLIB arm-none-eabi-ranlib)

# 添加ARM架构特定选项
# 完全禁用所有库和运行时支持
add_compile_options(
    #硬件编译选项
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=soft      #有soft、fpv4-sp-d16可选
    # -mfpu=fpv4-sp-d16

    # 代码优化和段管理
    -ffunction-sections   # 将每个函数放入独立section
    -fdata-sections       # 将全局数据放入独立section
    -fno-common           # 禁止未初始化变量放在公共段
    
    # 消息控制
    -fmessage-length=0    # 不限制编译器消息长度
    
    # 标准库控制
    -nostdinc             # 禁止搜索标准头文件目录
    -nostdlib             # 禁止链接标准库
    -ffreestanding        # 独立运行环境
    
    # 内置函数控制
    -fno-builtin          # 完全禁用所有GCC内置函数
    -fno-builtin-memcpy   # 特别禁用memcpy内置实现
    -fno-builtin-memset   # 特别禁用memset内置实现
    -fno-builtin-printf   # 禁用printf相关内置优化
    
    # C++特性禁用
    -fno-exceptions       # 禁用C++异常处理
    -fno-rtti             # 禁用运行时类型信息
    
    # 低级系统控制
    -fno-unwind-tables    # 禁用异常栈展开表
    -fno-use-cxa-atexit   # 禁用全局析构注册机制
    
    # 其他优化选项
    -fno-tree-vectorize   # 禁用自动向量化
    -fno-jump-tables      # 禁用跳转表优化
    -fno-pic              # 禁用位置无关代码生成
)

# 链接选项 
add_link_options(
    -nostdlib                                             # 不链接标准系统库
    -nostartfiles                                         # 不使用编译器提供的标准启动文件
    -nodefaultlibs                                        # 不链接默认系统库
    -Wl,--gc-sections                                     # 链接时垃圾回收，移除未使用的代码段和数据段
    -Wl,--print-memory-usage                              # 链接完成后打印内存使用报告
    -T${CMAKE_SOURCE_DIR}/linker/stm32f103c6t6.ld         # 指定链接脚本路径，定义内存布局
    -Wl,--entry=Reset_Handler                             # 显式指定入口
    -Wl,--no-undefined                                    # 严格检查未定义符号，禁止隐式忽略
    -Wl,--warn-common                                     # 警告公共符号冲突，避免意外覆盖
    -Wl,--nmagic                                          # 禁用链接器自动对齐/填充，严格遵循脚本
    -Wl,-Map,${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}.map  # 生成map文件
    -Wl,--cref                                            # 启用交叉引用，在map文件中添加符号引用关系
    # -Wl,--retain-symbols-file=${CMAKE_SOURCE_DIR}/symbols.retain  # 仅保留指定符号
)

# 禁用特定平台特性
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)