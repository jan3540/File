# Hello world
import tkinter as tk
window = tk.Tk()
window.geometry("200x50")
frame = tk.Frame(window).pack()
tk.Label(frame, text="Hello World!").pack()
tk.Button(frame, text="Quit", command=window.destroy).pack()
window.mainloop()