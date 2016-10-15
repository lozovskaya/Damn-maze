import tkinter as tk
import take_from_server
width_of_square = 50

def close():
    root.destroy()
    root.quit()


def create_player(x1, y1, x2, y2):
    player = canvas.create_oval(x1, y1, x2, y2, fill="blue")
    

# def create_one_wall(x1, y1, x2, y2):
  #  wall = canvas.create_rectangle(x1, y1, x2, y2, fill="brown", outline="black", width=4)
    
    
def create_squares(x1, y1, x2, y2, array):
    maze = canvas.create_rectangle(x1, y1, x2, y2, outline="black", width=5)
    array.append(maze)
    return array


def create_one_square(x1, y1, x2, y2, colour="black"):
    square = canvas.create_rectangle(x1, y1, x2, y2, outline=colour)


def create_button(text_on_button, x1, y1, command1):
    button = tk.Button(root, width=3, height=3, bg="white", fg="black", text=text_on_button, font="arial 15", command=command1)
    button.place(x=x1, y=y1)


def hide_me(event):
    widget.pack_forget()

    
def draw_field(field):
    clouds = ["black", "white", "grey", "red", "green", "blue", "cyan", "magenta", "yellow"]
    cloud_idx = 0
    for i in range(len(field)):
        for j in range(len(field[0])):
            create_one_square(j * width_of_square, i * width_of_square, j * width_of_square + width_of_square, i* width_of_square + width_of_square, clouds[cloud_idx % 9])
            cloud_idx += 1
            


root = tk.Tk()
array_of_squares = []
canvas = tk.Canvas(root, width=300, height=300)
canvas.pack()
create_button("Exit", 329, 329, command1=close)
sock = take_from_server.init()
field = take_from_server.return_array(sock)
draw_field(field)
root.mainloop()