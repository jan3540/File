# 9-1 GUI的布局
import tkinter as tk
window = tk.Tk()
window.geometry("400x350")
window.title('My GUI')
frame1 = tk.Frame(window, bg='red') # 在容器window中生成框架frame1，并设定背景颜色
frame1.place(x=100, y=50, width=200, height=100) # 定义frame1左上角在父容器window中的坐标，以及frame1的尺寸
frame2 = tk.Frame(window, bg='orange')
frame2.place(x=100, y=200, width=200, height=100)
window.mainloop()