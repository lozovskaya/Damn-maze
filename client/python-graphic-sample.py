import tkinter

Rad = 10

def idle_function():
    # write here your code, which must evaluate every tick
    command = ""
#    command = input() # uncomment it to move the circle, but after that char_func won't work
    if (command == 'left'):
        current_coords[0] -= 10
    elif (command == 'right'):
        current_coords[0] += 10
    elif (command == 'up'):
        current_coords[1] -= 10
    elif (command == 'down'):
        current_coords[1] += 10
    drawingStuff.coords(ball, current_coords[0], current_coords[1],
                            current_coords[0] + Rad, current_coords[1] + Rad)
                            # creation of new object is too long. I think, you should
                            # keep all your objects, and move it. Remove - move to the point (-179, -179)
    root.after(20, idle_function)


def char_func(arg):
    print("You have pressed that", str(arg.keysym), "with code:", arg.keysym_num)

root = tkinter.Tk()
drawingStuff = tkinter.Canvas(root)
ball = drawingStuff.create_oval(50, 50, 50 + Rad, 50 + Rad, fill='blue') # create an ellipse into a rectangle 
                                  # with these coordinates, returns id of the circle
current_coords = [50, 50]
print("type in your cmd commands 'left', 'right', 'up' and 'down' to move the circle")


drawingStuff.pack()
idle_function()
root.bind("<Key>", char_func)
#  see help("tkinter.Tk.bind") for more callbacks
root.mainloop()
