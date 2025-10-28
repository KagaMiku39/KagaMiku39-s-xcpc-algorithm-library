#!/bin/bash

# =========================================================
# 脚本配置部分
# =========================================================

# 定义颜色常量，用于彩色输出
G='\033[0;32m'  # 绿色 - Accepted (答案正确)
R='\033[0;31m'  # 红色 - Wrong Answer (答案错误)
Y='\033[0;33m'  # 黄色 - 警告信息 (编译/运行提示)
NC='\033[0m'    # 无色 - 恢复终端默认颜色

# =========================================================
# 脚本主逻辑部分
# =========================================================

# 1. 参数校验
# 检查是否提供了cpp文件名作为参数
if [[ -z "$1" ]]; then
    echo "Usage: $0 <cpp_file>"  # 显示正确用法
    exit 1
fi

# 获取文件名并移除可能的.cpp后缀
file="$1"
name="${file%.*}"

# 2. 编译阶段
echo -e "${Y}Compiling ${file}...${NC}"  # 显示编译开始提示
# 使用g++编译，启用C++20标准，O2优化，显示所有警告
g++ -std=c++20 -O2 -Wall "$file" -o "$name" || exit 1

# 3. 运行测试阶段
# 检查是否存在输入文件(in)
if [[ -f "in" ]]; then
    echo -e "${Y}Running with input file...${NC}"
    # 使用in作为输入，输出到out文件
    ./"$name" < "in" > "out"
else
    echo -e "${Y}Running without input file...${NC}"
    # 无输入文件时，直接运行并将输出保存到out
    ./"$name" > "out"
fi

# 4. 检查运行结果
# 检查上一条命令的退出状态码
if [[ $? -ne 0 ]]; then
    echo -e "${R}Runtime Error${NC}"  # 运行出错提示
    exit 1
fi

# 5. 结果对比阶段
# 检查是否存在答案文件(ans)
if [[ -f "ans" ]]; then
    # 比较输出文件(out)和答案文件(ans)，忽略末尾空白差异
    if diff -w -q "out" "ans" >/dev/null; then
        echo -e "${G}Accepted${NC}"  # 答案正确
    else
        echo -e "${R}Wrong Answer${NC}"  # 答案错误
        echo "=== Differences ==="  # 显示差异标题
        diff -w "out" "ans"  # 显示具体差异内容
    fi
else
    # 没有答案文件时，直接显示输出内容
    echo "=== Output ==="
    cat "out"
fi

# 6. 清理阶段
# 删除生成的可执行文件
rm -f "$name"