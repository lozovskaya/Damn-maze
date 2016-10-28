import tkinter as tk


def to_hex_digit(i):
    if (i < 10):
        return str(i)
    return chr(ord('a') + i - 10)


def to_hex(i):
    curr_pow = 16 ** 10
    answer = []
    while (curr_pow >= 0):
        if (i >= curr_pow):
            div, remainer = divmod(i, curr_pow)
            answer.append(to_hex_digit(div))
            i = remainer
        elif (len(answer) > 0):
            answer.append('0')
        curr_pow /= 16
    return ''.join(answer).rjust(2, '0')

root = tk.Tk()
canvas = tk.Canvas(root, height=300, width=300)
canvas.pack()
for i in range(5, -1, -1):
    hole = canvas.create_rectangle(110 + i * 2, 110 + i * 2, 
                                   100 - i * 2, 100 - i * 2, outline="black",
                                   fill="#" + to_hex(i * 40) * 6)
# print(hole)
root.mainloop()
