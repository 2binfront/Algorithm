#!/bin/bash

# 检查是否提供了输入文件
if [ $# -ne 1 ]; then
    echo "用法: $0 <C源文件路径>"
    exit 1
fi

# 获取输入文件路径
input_file="$1"

# 检查文件是否存在
if [ ! -f "$input_file" ]; then
    echo "错误: 文件 '$input_file' 不存在"
    exit 1
fi

# 检查是否为.c文件
if [[ ! "$input_file" =~ \.c$ ]]; then
    echo "错误: '$input_file' 不是C源文件(.c)"
    exit 1
fi

# 提取文件名（不含路径和扩展名）
filename=$(basename "$input_file" .c)

# 创建唯一的时间戳后缀
timestamp=$(date +%Y%m%d%H%M%S)

# 创建build目录（如果不存在）
build_dir="./build"
mkdir -p "$build_dir"

# 定义带时间戳的文件名（全部放在build目录下）
unique_basename="${filename}_${timestamp}"
obj_file="${build_dir}/${unique_basename}.o"
thread_obj_file="${build_dir}/thread_${timestamp}.o"
executable="./${unique_basename}"

echo "正在编译 $input_file..."
echo "中间文件和可执行文件将保存在 $build_dir 目录下"

# 编译主C文件
gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS -I./lib/ "$input_file" -c -o "$obj_file"
if [ $? -ne 0 ]; then
    echo "编译主C文件失败"
    exit 1
fi

# 假设thread.c文件在同一目录下
# 如果thread.c在其他位置，可以修改这个路径
thread_c="./lib/thread.c"
if [ ! -f "$thread_c" ]; then
    echo "错误: thread.c 文件未找到"
    exit 1
fi

# 编译thread.c文件
gcc -g -Wall -Werror -D_POSIX_THREAD_SEMANTICS -I./lib/ "$thread_c" -c -o "$thread_obj_file"
if [ $? -ne 0 ]; then
    echo "编译thread.c失败"
    exit 1
fi

# 链接目标文件
gcc "$obj_file" "$thread_obj_file" -lpthread -o "$executable"
if [ $? -ne 0 ]; then
    echo "链接失败"
    exit 1
fi

echo "编译成功! 执行程序..."

# 执行编译后的程序
"$executable"

echo "完成"
