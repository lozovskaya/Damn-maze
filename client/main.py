import tkinter as tk
import take_from_server
import drawing as dr
width_of_square = 40


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
