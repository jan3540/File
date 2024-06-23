#!/bin/bash

# 执行命令并获取结果
result=$(ls *px* *ct* 2>/dev/null)

# 初始化计数器
px_count=0
ct_count=0

# 处理结果，统计包含"px"和"ct"的文件或目录数
for item in $result; do
    if [[ "$item" == *px* ]]; then
        px_count=$((px_count + 1))
    fi
    if [[ "$item" == *ct* ]]; then
        ct_count=$((ct_count + 1))
    fi
done

# 输出包含"px"和"ct"的文件或目录数
echo "包含'px'的文件或目录数: $px_count"
echo "包含'ct'的文件或目录数: $ct_count"

# 根据统计结果计算得分
if [[ $px_count -gt 0 && $ct_count -gt 0 ]]; then
    score=100
elif [[ $px_count -gt 0 || $ct_count -gt 0 ]]; then
    score=50
else
    score=0
fi

# 输出得分
echo "实验项目得分: $score"