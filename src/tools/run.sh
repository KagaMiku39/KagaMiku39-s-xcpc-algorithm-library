#!/bin/bash

# 记得先 chmod +x run.sh

# =========================================================
# 脚本配置
# =========================================================

# 定义颜色常量
G='\033[0;32m'   # Accepted
Y='\033[0;33m'   # Compile Error
RE='\033[0;35m'  # Runtime Error
NC='\033[0m'     # 恢复默认颜色

# =========================================================
# 脚本主逻辑
# =========================================================

# 1. 参数校验
if [[ -z "$1" ]]; then
    echo -e "Usage: $0 filename"
    exit 1
fi

name="$1"

# 2. 编译C++源文件
echo -e "Compiling ${name}.cpp..."
if ! g++ -std=c++20 -O2 -Wall "${name}.cpp" -o "$name"; then
    echo -e "${Y}Compile Error${NC}"
    exit 1
fi

# 3. 运行程序
echo -e "Running program..."
./"$name"
exitcode=$?

# 4. 检查运行时错误
if [[ $exitcode -ne 0 ]]; then
    echo -e "${RE}Runtime Error${NC}"
else
    echo -e "${G}Execution completed${NC}"
fi