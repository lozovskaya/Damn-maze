import tkinter as tk

root = tk.Tk()
canvas = tk.Canvas(root, height=300, width=300)
canvas.pack()
for i in range(5):
    hole = canvas.create_rectangle(110 + i * 2, 110 + i * 2, 
                                   100 - i * 2, 100 - i * 2, outline="black")
# print(hole)
root.mainloop()
