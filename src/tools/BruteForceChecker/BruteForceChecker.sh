#!/bin/bash

# 记得先 chmod +x BruteForceChecker.sh

# 定义颜色常量
G='\033[0;32m'   # 绿色 - Accepted
R='\033[0;31m'   # 红色 - WrongAnswer
NC='\033[0m'     # 恢复默认颜色

# 编译所有程序
g++ -std=c++20 -O2 data.cpp -o data
g++ -std=c++20 -O2 std.cpp -o std
g++ -std=c++20 -O2 solve.cpp -o solve

echo "-------------------------------------"
echo "Starting BruteForceChecker..."
echo "-------------------------------------"

t=0
while true; do
    t=$((t+1))
    echo -n "Test $t: "
    
    # 运行程序并生成输入输出文件
    ./data > solve.in
    ./std < solve.in > solve.out
    ./solve < solve.in > solve.ans
    
    # 使用 diff 比较结果
    if diff -q -b solve.out solve.ans > /dev/null; then
        echo -e "${G}Accepted${NC}"
    else
        echo -e "${R}Wrong Answer${NC}"
        code --diff solve.ans solve.out
        code solve.in
        break
    fi
done

# 清理生成的文件
rm -f data std solve