import tkinter as tk
import take_from_server
import drawing as dr
width_of_square = 40


def draw_cell(x1, y1, x2, y2):
    if x2 == -1 and y2 == -1:                               
        x1, y1 = x1 * width_of_square, y1 * width_of_square
        x2, y2 = x1 + width_of_square, y1 + width_of_square
    return (x1 + 20, y1 + 20), (x2 + 20, y2 + 20)


def main():
    receive = take_from_server.return_array(sock)
    field = receive[0]
    d.start_draw()
    for i in range(len(field)):
        for j in range(len(field[i])):
            if field[i][j] == 0:
                d.draw_square(j, i, "white")
            elif field[i][j] == 1:
                d.draw_square(j, i, "brown")
            elif field[i][j] == 2:
                d.draw_hole(j, i)
    d.stop_draw()
    root.after(50, main)


root = tk.Tk()
d = dr.drawing(root)
sock = take_from_server.init()
main()
root.mainloop()
