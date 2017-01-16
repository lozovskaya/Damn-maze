import tkinter as tk
import take_from_server
import drawing as dr
width_of_square = 40


def char_func(arg):
    print("You have pressed that", str(arg.keysym), "with code:", arg.keysym_num)


def draw_cell(dr, x, y, colour):
    x1, y1 = x * width_of_square, y * width_of_square
    x2, y2 = x1 + width_of_square, y1 + width_of_square
    dr.draw_square(x1 + 20, y1 + 20, x2 + 20, y2 + 20, colour)


def main():
    receive = take_from_server.what_draw(sock)
    field = receive[0]
    d.start_draw()
    for i in range(len(field)):
        for j in range(len(field[i])):
            if field[i][j] == 0:
                draw_cell(d, j, i, "white")
            elif field[i][j] == 1:
                draw_cell(d, j, i, "brown")
            elif field[i][j] == 2:
                d.draw_hole(j, i)
    d.stop_draw()
    root.after(50, main)


root = tk.Tk()
d = dr.drawing(root)
sock = take_from_server.init()
my_id = take_from_server.return_my_id(sock)
main()
root.bind("<Key>", char_func)
root.mainloop()
