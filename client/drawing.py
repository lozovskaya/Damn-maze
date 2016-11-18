import tkinter as tk
import hole
width_of_square = 40


class drawing:
    def __init__(self, root):
        self.array_of_squares = []
        self.canvas = tk.Canvas(root, height=750, width=1400)
        self.canvas.pack()

    def start_draw(self):
        self.index_squares = 0
    
    def draw_square(self, x1, y1, x2, y2, colour):
        if self.index_squares < len(self.array_of_squares):
            self.canvas.coords(self.array_of_squares[self.index_squares], x1, y1, x2, y2)
        else:
            new_square = self.canvas.create_rectangle(x1, y1,
                                                      x2, y2,
                                                 outline="black", fill=colour)
            self.array_of_squares.append(new_square)
        self.index_squares += 1
    
    def draw_hole(self, x, y):
        for i in range(6):
            self.draw_square(x * width_of_square + i * 2 + 20, 
                             y * width_of_square + i * 2 + 20,
                             x * width_of_square - i * 2 + width_of_square + 20, 
                             y * width_of_square - i * 2 + width_of_square + 20,
                            "#" + hole.to_hex((5 - i) * 40) * 6)
    
    def stop_draw(self):
        for i in range(self.index_squares, len(self.array_of_squares)):
            self.canvas.coords(self.array_of_squares[i], -51, -51, -1, -1)
