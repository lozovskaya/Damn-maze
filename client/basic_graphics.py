#!/usr/bin/python3

import tkinter as tk
import take_from_server
width_of_square = 50

def close():
    root.destroy()
    root.quit()


def create_player(x1, y1, x2, y2):
    player = canvas.create_oval(x1, y1, x2, y2, fill="blue")
    return player

'''
def create_one_wall(x1, y1, x2, y2):
    wall = canvas.create_rectangle(x1, y1, x2, y2, fill="brown", outline="black", width=4)   
def add_square(maze, array):
    # maze = canvas.create_rectangle(x1, y1, x2, y2, outline="black", width=5)
    array.append(maze)
    return array'''


def create_one_square(x1, y1, x2, y2, colour="white"):
    square = canvas.create_rectangle(x1, y1, x2, y2, outline="black", fill=colour)


def create_button(text_on_button, x1, y1, command1):
    button = tk.Button(root, width=3, height=3, bg="white", fg="black",
    text=text_on_button, font="arial 15", command=command1)
    button.place(x=x1, y=y1)


def hide_me(event):
    widget.pack_forget()

    
def add_new_square(array_of_squares, i, j, colour="white"):
    # clouds = ["black", "white", "grey", "ref", "green", "blue", "cyan", "magenta", "yellow"]
    new_square = create_one_square(j * width_of_square + 10, i * width_of_square + 10,
                                   j * width_of_square + width_of_square + 10, 
                                   i * width_of_square + width_of_square + 10, colour)
    array_of_squares.append(new_square)
    return array_of_squares


root = tk.Tk()
array_of_squares = []
canvas = tk.Canvas(root, height=1000, width=1500)
canvas.pack()
sock = take_from_server.init()
field = take_from_server.return_array(sock)
for i in range(len(field)):
    for j in range(len(field[i])):
        if field[i][j] == 0:
            array_of_squares = add_new_square(array_of_squares, i, j)
        elif field[i][j] == 1:
            array_of_squares = add_new_square(array_of_squares, i, j, "brown")
root.mainloop()
