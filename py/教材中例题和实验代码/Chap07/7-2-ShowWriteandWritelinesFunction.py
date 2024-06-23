# 7-2 ShowWriteandWritelinesFunction.py
with open(r'scores.txt', 'r', encoding='utf-8') as scores_file, open(r'scores_english.txt', 'r', encoding='utf-8') as scores_english_file, open(r'scores_all.txt', 'w', encoding='utf-8') as scores_all_file, open(r'scores_all_lines.txt', 'w', encoding='utf-8') as scores_all_lines_file:
  scores_readlines = scores_file.readlines()
  scores_english_readlines = scores_english_file.readlines()
  # 以list数据类型声明待输入writelines()的变量write_lines
  write_lines = []
  for scores_line, scores_english_line in zip(scores_readlines, scores_english_readlines):
    # 遍历scores_readlines与scores_english_readlines的每个元素，并且删除元素中的'\n'，以方便合并
    scores_line = scores_line.strip()
    scores_english_line = scores_english_line.strip()
    # 将scores_english_line字符串按照','分割，并以list形式返回为scores_english_line
    scores_english_line = scores_english_line.split(',')
    # 将'scores.txt'中的数据与'scores_english.txt'中英语成绩合并成一个字符串
    merged_line = scores_line + ',' + scores_english_line[-1] + '\n'
    # 调用write()函数将合并后的字符串写入'scores_all.txt'
    scores_all_file.write(merged_line)
    # 将合并后的字符串加入到write_lines
    write_lines.append(merged_line)
    # 调用writelinees()函数将write_lines写入'scores_all_lines.txt'
  scores_all_lines_file.writelines(write_lines)