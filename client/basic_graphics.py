import tkinter as tk

def close(event):
    root.destroy()
    root.quit()


def create_player(x1, y1, x2, y2):
    player = canvas.create_oval(x1, y1, x2, y2, fill="blue")
    

# def create_one_wall(x1, y1, x2, y2):
  #  wall = canvas.create_rectangle(x1, y1, x2, y2, fill="brown", outline="black", width=4)
    
    
def create_square(x1, y1, x2, y2, array):
    maze = canvas.create_rectangle(x1, y1, x2, y2, outline="black", width=5)
    array.append(maze)
    return array


def create_button(text_on_button, x1, y1):
    button = tk.Button(root, width=15, height=3, bg="white", fg="black", text=text_on_button, font="arial 15")
    button.place(x=x1, y=y1)


def hide_me(event):
    widget.pack_forget()


root = tk.Tk()
array_of_squares = []
canvas = tk.Canvas(root, width=300, height=300)
canvas.pack()
create_button("Exit", 0, 0)
root.mainloop()