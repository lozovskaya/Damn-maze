import tkinter as tk
width_of_square = 50
root = tk.Tk()



class drawing:
    array_of_squares = []
    canvas = tk.Canvas(root)
    canvas.pack()
    def start_draw(self):
        self.index = 0
    def draw(self, x, y, colour, canvas=canvas, array_of_squares=array_of_squares):
        if self.index < len(array_of_squares):
            canvas.coords(array_of_squares[self.index], x, y, x + width_of_square, y + width_of_square)
            self.index += 1
        else:
            new_square = canvas.create_rectangle(x * width_of_square + 10,
                                             y * width_of_square + 10, 
                                             x * width_of_square + width_of_square + 10, 
                                             y * width_of_square + width_of_square + 10, 
                                             outline="black", fill=colour)
            array_of_squares.append(new_square)
            self.index += 1
    def stop_draw(self, canvas=canvas, array_of_squares=array_of_squares):
        for i in range(self.index, len(array_of_squares)):
            canvas.coords(array_of_squares[i], -1, -1)


d = drawing()
d.start_draw()
d.draw(1, 1, "black")
d.draw(2, 2, "red")
d.start_draw()
d.draw(3, 3, "blue")
root.mainloop()
