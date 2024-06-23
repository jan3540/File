score=eval(input("请输入学生的成绩：")) 
if score<60:
    grade="不及格"
elif score<80:
    grade="及格"
elif score<90:
    grade="良好"
else:
    grade="优秀"
print("等级为：{}".format(grade))
