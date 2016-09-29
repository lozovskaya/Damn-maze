from tkinter import * 


def player(x1, y1, x2, y2):
    player = canvas.create_oval(x1, y1, x2, y2, fill="blue")
    

def create_one_wall(x1, y1, x2, y2):
    wall = canvas.create_rectangle(x1, y1, x2, y2, fill="brown", outline="black", width=4)
    
    
def maze(x1, y1, x2, y2):
    maze = canvas.create_rectangle(x1, y1, x2, y2, outline="black", width=5)

    
root = Tk() 
canvas = Canvas(root, width=500, height=500)
canvas.pack()
root.mainloop()