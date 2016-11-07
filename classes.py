import tkinter as tk
width_of_square = 50


class draw:
    # def __init__(self):
    def start_draw(self):
        self.k = 0
    def draw(self, canvas, array_of_squares, x, y, colour):
        if self.k < len(array_of_squares):
            canvas.coords(array_of_squares[self.k], x, y, x + width_of_square, y + width_of_square)
            self.k += 1
        else:
            new_square = canvas.create_rectangle(x * width_of_square + 10,
                                             y * width_of_square + 10, 
                                             x * width_of_square + width_of_square + 10, 
                                             y * width_of_square + width_of_square + 10, 
                                             outline="black", fill=colour)
            array_of_squares.append(new_square)
            self.k += 1


root = tk.Tk()
canvas = tk.Canvas(root)
canvas.pack()
array_of_squares = []
drawit = draw()
drawit.start_draw()
drawit.draw(canvas, array_of_squares, 1, 2, "black")
drawit.start_draw()
drawit.draw(canvas, array_of_squares, 2, 3, "red")
print(drawit.k)
root.mainloop()
