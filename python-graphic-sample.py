import tkinter

Rad = 10

def idle_function():
    command = input()
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
    root.after(20, idle_function)

root = tkinter.Tk()
drawingStuff = tkinter.Canvas(root)
ball = drawingStuff.create_oval(50, 50, 50 + Rad, 50 + Rad, fill='blue') # create an ellipse into a rectangle 
                                  # with these coordinates, returns id of the circle
current_coords = [50, 50]
print("type in your cmd commands 'left', 'right', 'up' and 'down' to move the circle")


drawingStuff.pack()
idle_function()
root.mainloop()
