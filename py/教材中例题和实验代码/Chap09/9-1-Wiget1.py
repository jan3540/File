# 9-1 Wiget1
import tkinter as tk

window = tk.Tk()
frame = tk.Frame(window)
frame.place(x=0,y=0,width=200,height=50)
frame.config(bg='blue')

bottomframe = tk.Frame(window)
bottomframe.place(x=0,y=50,width=200,height=50)
bottomframe.config(bg='red')

redbutton = tk.Button(frame, text="Red", fg="red")
redbutton.place(x=0,y=0,width=50,height=50)

greenbutton = tk.Button(frame, text="Green", fg="green")
greenbutton.place(x=50,y=0,width=50,height=50)

bluebutton = tk.Button(frame, text="Blue", fg="blue")
bluebutton.place(x=100,y=0,width=50,height=50)

label = tk.Label(bottomframe, text="Black", fg="black")
label.pack()

window.mainloop()