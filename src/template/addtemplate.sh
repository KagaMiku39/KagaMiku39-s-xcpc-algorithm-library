#!/bin/bash

# 极简纯净版：可以选择是否输入Markdown内容
# 使用方法: ./addtemplate.sh

MD_FILE=/home/kagamiku39/code/KagaMiku39-s-xcpc-algorithm-library/KagaMiku39-s-xcpc-algorithm-library.md

echo "📄 添加代码模板"
echo "-----------------------"

# 输入文件名（不需要.cpp）
read -p "输入文件名（不加.cpp）: " base_name
filename="${base_name}.cpp"

# 检查文件是否存在
if [ ! -f "$filename" ]; then
    echo "❌ 错误：文件 $filename 不存在！"
    exit 1
fi

# 询问是否要添加Markdown内容
read -p "是否要添加Markdown内容？(y/n): " add_markdown

if [[ "$add_markdown" =~ ^[Yy]$ ]]; then
    echo "粘贴题目Markdown内容（Ctrl+D结束）:"
    markdown_content=$(cat)
    
    # 追加Markdown内容和代码
    {
        echo "$markdown_content"
        echo -e "\n<div style=\"page-break-after: always;\"></div>\n"
        echo -e '```cpp'
        cat "$filename"
        echo -e '\n```'
        echo -e "\n<div style=\"page-break-after: always;\"></div>\n"
    } >> "$MD_FILE"
else
    # 只追加代码
    {
        echo -e '```cpp'
        cat "$filename"
        echo -e '\n```'
        echo -e "\n<div style=\"page-break-after: always;\"></div>\n"
    } >> "$MD_FILE"
fi

echo "✅ 已完成！"