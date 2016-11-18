import tkinter as tk
import hole
width_of_square = 40


def draw_cell(x1, y1, x2, y2):
    if x2 == -1 and y2 == -1:                               
        x1, y1 = x1 * width_of_square, y1 * width_of_square
        x2, y2 = x1 + width_of_square, y1 + width_of_square
    return (x1 + 20, y1 + 20), (x2 + 20, y2 + 20)


class drawing:
    def __init__(self, root):
        self.array_of_squares = []
        self.canvas = tk.Canvas(root, height=750, width=1400)
        self.canvas.pack()

    def start_draw(self):
        self.index_squares = 0
    
    def draw_square(self, x, y, colour, x2=-1, y2=-1):
        coords = draw_cell(x, y, x2, y2)
        x, y = coords[0][0], coords[0][1]  
        x2, y2 = coords[1][0], coords[1][1]
        if self.index_squares < len(self.array_of_squares):
            self.canvas.coords(self.array_of_squares[self.index_squares], x, y, x2, y2)
        else:
            new_square = self.canvas.create_rectangle(x, y, x2, y2,
                                                 outline="black", fill=colour)
            self.array_of_squares.append(new_square)
        self.index_squares += 1
    
    def draw_hole(self, x, y):
        for i in range(6):
            self.draw_square(x * width_of_square + i * 2, y * width_of_square + i * 2,
                            "#" + hole.to_hex((5 - i) * 40) * 6, 
                             x2=x * width_of_square - i * 2 + width_of_square, 
                             y2=y * width_of_square - i * 2 + width_of_square)
    
    def stop_draw(self):
        for i in range(self.index_squares, len(self.array_of_squares)):
            self.canvas.coords(self.array_of_squares[i], -51, -51, -1, -1)
