# 10-(2) register
import tkinter as tk
import csv

def register_user():
    username = entry_username.get()
    password = entry_password.get()

    with open("users.csv", "a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow([username, password, email])

    label_result.config(text="User registered successfully!")

root = tk.Tk()
root.title("User Registration")

label_username = tk.Label(root, text="Username:")
label_username.grid(row=0, column=0)
entry_username = tk.Entry(root)
entry_username.grid(row=0, column=1)

label_password = tk.Label(root, text="Password:")
label_password.grid(row=1, column=0)
entry_password = tk.Entry(root, show="*")
entry_password.grid(row=1, column=1)


button_register = tk.Button(root, text="Register", command=register_user)
button_register.grid(row=3, column=0, columnspan=2)

label_result = tk.Label(root, text="")
label_result.grid(row=4, column=0, columnspan=2)

root.mainloop()