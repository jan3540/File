# 9-2 Wiget2.py
import tkinter as tk
def update_label():
    label.config(text="Button clicked!")
def double_update_label(envent):
    label.config(text="Button 2 double-clicked!")
window = tk.Tk()
window.geometry("200x100")
# 设置按键小部件button及其触发函数
button = tk.Button(window, text="Click Button 1", command=update_label)
button.pack()
# 设置按键小部件button2及其触发函数
button2 = tk.Button(window, text="Double-click Button 2")
button2.bind("<Double-Button-1>", double_update_label)
button2.pack()
# 设置标签小部件
label = tk.Label(window, text="Label")
label.pack()
window.mainloop()