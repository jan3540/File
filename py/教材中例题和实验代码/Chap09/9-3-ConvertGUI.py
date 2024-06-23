# 9-3 ConvertGUI.py
import tkinter as tk
def tranDec():
    m = int(decimal_entry.get())
    n = int(convert_entry.get())
    if m>0 and 2<=n<=16:
        base=['0','1','2','3','4','5','6','7','8','9',
            'A','B','C','D','E','F']
        trans=""
        Originalm = m
        while m!=0:
            r = m % n
            trans = base[r] + trans   # trans = trans + base[r]
            m = m // n
        result_label.config(text="十进制数"+ str(Originalm) + "转换成" + str(n) + "进制数是" + str(trans))
    else:        
        result_label.config(text="输入的数不符合要求！")
# 创建主窗口
window = tk.Tk()
window.title("进制转换")
window.geometry("300x150")
# 创建原始数值标签和输入框
decimal_label = tk.Label(window, text="请输入一个十进制的正整数:")
decimal_label.pack()
decimal_entry = tk.Entry(window)
decimal_entry.pack()
# 创建进制标签和输入框
convert_label = tk.Label(window, text="请输入一个二到十六的整数:")
convert_label.pack()
convert_entry = tk.Entry(window)
convert_entry.pack()
# 创建转换按钮
convert_button = tk.Button(window, text="转换", command=tranDec)
convert_button.pack()
# 创建结果标签
result_label = tk.Label(window)
result_label.pack()
# 运行主循环
window.mainloop()