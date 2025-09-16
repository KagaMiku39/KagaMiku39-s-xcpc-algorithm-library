#!/bin/bash

# 极简纯净版：只输入文件名和Markdown内容
# 使用方法: ./addtemplate.sh

MD_FILE=/home/kagamiku39/code/KagaMiku39-s-xcpc-algorithm-library/KagaMiku39-s-xcpc-algorithm-library.md

echo "📄 添加代码模板"
echo "-----------------------"

# 输入Markdown内容
echo "粘贴题目Markdown内容（Ctrl+D结束）:"
markdown_content=$(cat)

# 输入文件名（不需要.cpp）
read -p "输入文件名（不加.cpp）: " base_name
filename="${base_name}.cpp"

# 检查文件是否存在
if [ ! -f "$filename" ]; then
    echo "❌ 错误：文件 $filename 不存在！"
    exit 1
fi

# 直接追加到文件：换页 + 用户Markdown + 换页 + 代码块
{
    echo "$markdown_content"
    echo -e "\n<div style=\"page-break-after: always;\"></div>\n"
    echo -e '```cpp'
    cat "$filename"
    echo -e '\n```'
    echo -e "\n<div style=\"page-break-after: always;\"></div>\n"
} >> "$MD_FILE"

echo "✅ 已完成！"