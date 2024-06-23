# 10-(3) login
import tkinter as tk
import csv
from tkinter import messagebox

def login_user():
    username = entry_username.get()
    password = entry_password.get()

    with open("users.csv", "r") as file:
        reader = csv.reader(file)
        for row in reader:
            if row[0] == username and row[1] == password:
                messagebox.showinfo("Login", "Login successful!")
                return

    messagebox.showerror("Login", "Incorrect username or password.")

root = tk.Tk()
root.title("User Login")

label_username = tk.Label(root, text="Username:")
label_username.grid(row=0, column=0)
entry_username = tk.Entry(root)
entry_username.grid(row=0, column=1)

label_password = tk.Label(root, text="Password:")
label_password.grid(row=1, column=0)
entry_password = tk.Entry(root, show="*")
entry_password.grid(row=1, column=1)

button_login = tk.Button(root, text="Login", command=login_user)
button_login.grid(row=2, column=0, columnspan=2)

root.mainloop()