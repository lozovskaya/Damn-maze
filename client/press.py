import tkinter


def char_func(arg):
    print("You have pressed that", str(arg.keysym), "with code:", arg.keysym_num)


root = tkinter.Tk()
canvas = tkinter.Canvas(root)
canvas.pack()
root.bind("<Key>", char_func)
root.mainloop()
