#!/bin/bash

# 记得先 chmod +x run.sh

# =========================================================
# 脚本配置
# =========================================================

# 定义颜色常量，用于彩色输出
G='\033[0;32m'      # 绿色 - Accepted
R='\033[0;31m'      # 红色 - WrongAnswer
Y='\033[0;33m'      # 黄色 - Compile Error
B='\033[0;34m'      # 蓝色 - Time Limit Exceeded
RE='\033[0;35m'     # 品红 - Runtime Error
C='\033[0;36m'      # 青色 - 提示信息
NC='\033[0m'        # 恢复默认颜色

# 模板文件路径
# 请确保这两个文件存在于 /home/kagamiku39/code/ 目录下
tstdio="/home/kagamiku39/code/template.cpp"
tfileio="/home/kagamiku39/code/templateio.cpp"

# =========================================================
# 脚本主逻辑
# =========================================================

# 1. 参数校验
if [[ -z "$1" || -z "$2" || ("$1" != "0" && "$1" != "1") ]]; then
    echo -e "${R}Error: Invalid format! Please check your input.${NC}"
    echo "Usage: $0 [0|1] filename"
    exit 1
fi

type="$1"
name="$2"
# 移除文件名可能带有的 .cpp 后缀，确保后续的文件名拼接正确
name="${name%.cpp}"

# 2. 文件创建
if [[ "$type" == "0" ]]; then
    if [[ ! -f "$name.cpp" ]]; then
        echo -ne "${C}Confirm execution? (y/N): ${NC}"
        read -r ans
        if [[ "$ans" != "y" && "$ans" != "Y" ]]; then
            echo "${C}Execution cancelled.${NC}"
            exit 1
        fi
        cp "$tstdio" "./$name.cpp"
        echo -e "${C}Creating source file: $name.cpp${NC}"
        code "$name.cpp"
        exit 0
    fi
fi

if [[ "$type" == "1" ]]; then
    if [[ ! -f "$name.cpp" ]]; then
        echo -ne "${C}Confirm execution? (y/N): ${NC}"
        read -r ans
        if [[ "$ans" != "y" && "$ans" != "Y" ]]; then
            echo "${C}Execution cancelled.${NC}"
            exit 1
        fi
        cp "$tfileio" "./$name.cpp"
        echo -e "${C}Creating source file: $name.cpp${NC}"
        code "$name.cpp"
    fi
    for file in "$name.ans" "$name.out" "$name.in"; do
        if [[ ! -f "$file" ]]; then
            echo -e "${C}Creating file: $file${NC}"
            touch "$file"
            code "$file"
            if [[ "$file" == "$name.in" ]]; then
                exit 0
            fi
        fi
    done
fi

# 3. 增大栈限制
ulimit -s 524288 > /dev/null 2>&1
ulimit -v unlimited > /dev/null 2>&1

# 4. 编译C++源文件
echo -e "${C}Compiling source file: $name.cpp...${NC}"
if ! g++ -std=c++23 -O2 -Wall -Wextra "$name.cpp" -o "$name"; then
    echo -e "${Y}Error: Compile Error${NC}"
    exit 1
fi

# 5. 根据模式运行程序
if [[ "$type" == "0" ]]; then
    echo -e "${C}Running in standard I/O mode...${NC}"
    ./"$name"
    rm -f "$name"
    exit 0
fi

if [[ "$type" == "1" ]]; then
    ok="true"
    for file in "$name.out" "$name.in"; do
        if [[ ! -s "$file" ]]; then
            echo -e "${R}Error: File '$file' is empty.${NC}"
            ok="false"
        fi
    done
    if [[ "$ok" = "false" ]]; then
        exit 1
    fi
    
    echo -e "${C}Running and checking for errors...${NC}"
    timeout 5s "./$name" < "$name.in" > "$name.tmp"
    exitcode=$?
    
    if [[ $exitcode -ne 0 ]]; then
        if [[ $exitcode -eq 124 ]]; then
            echo -e "${B}Time Limit Exceeded${NC}"
        else
            echo -e "${RE}Runtime Error${NC}"
        fi
        rm -f "$name"
        rm -f "$name".tmp
        exit 1
    fi
    
    mv "$name.tmp" "$name.ans"
    
    # 6. 比较输出结果
    echo -e "${C}Checking output against answer file...${NC}"

    # 使用一个变量来动态存储 diff 参数
    diffoptions="-b --ignore-trailing-space"
    if grep -q -iE '^[[:space:]]*(yes|no)[[:space:]]*$' "$name.ans"; then
        diffoptions="-i $diffoptions"
    fi

    # 执行一次 diff 命令，并检查其退出码
    if diff -q $diffoptions "$name.out" "$name.ans" &>/dev/null; then
        echo -e "${G}Accepted${NC}"
    else
        echo -e "${R}Wrong Answer${NC}"
        # 直接在终端中打印差异
        diff $diffoptions "$name.out" "$name.ans"
        code --diff "$name.ans" "$name.out"
    fi
fi

# 7. 清理可执行文件
rm -f "$name"