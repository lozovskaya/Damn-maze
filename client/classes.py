import tkinter as tk
import hole
import take_from_server
width_of_square = 50
root = tk.Tk()


class drawing:
    array_of_squares = []
    array_of_holes = []
    canvas = tk.Canvas(root, height=750, width=1400)
    canvas.pack()
    def start_draw(self):
        self.index_squares = 0
       
    def draw_square(self, x, y, colour, x2=-1, y2=-1, canvas=canvas, 
                    array_of_squares=array_of_squares):
        if self.index_squares < len(array_of_squares):
            canvas.coords(array_of_squares[self.index_squares], x, y, x + width_of_square, y + width_of_square)
            self.index_squares += 1
        else:
            if x2 == -1 and y2 == -1:
                x, y = x * width_of_square, y * width_of_square 
                x2, y2 = x + width_of_square, y + width_of_square
            new_square = canvas.create_rectangle(x + 10, y + 10, 
                                                 x2 + 10, y2 + 10, 
                                                 outline="black", fill=colour)
            array_of_squares.append(new_square)
            self.index_squares += 1
    def draw_hole(self, x, y):
        for i in range(5, -1, -1):
            self.draw_square(x + i * 2, y + i * 2,         
                             "#" + hole.to_hex(i * 40) * 6,                   
                             x2=x - 60 - i * 2, y2=y - 60 - i * 2)
    def stop_draw(self, canvas=canvas, array_of_squares=array_of_squares):
        for i in range(self.index_squares, len(array_of_squares)):
            canvas.coords(array_of_squares[i], -1, -1)


def main(field, d):
    d.start_draw()
    for i in range(len(field)):
        for j in range(len(field[i])):
            if field[i][j] == 0:
                d.draw_square(j, i, "white")
            elif field[i][j] == 1:
                d.draw_square(j, i, "brown")
            elif field[i][j] == 2:
                d.draw_hole(j, i)


sock = take_from_server.init()
field = take_from_server.return_array(sock)
d = drawing()
main(field, d)
root.mainloop()
