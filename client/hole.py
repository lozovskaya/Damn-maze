import tkinter as tk


def to_hex_digit(i):
    if (i < 10):
        return str(i)
    return chr(ord('a') + i - 10)


def to_hex(i):
    curr_pow = 16 ** 10
    answer = []
    while (curr_pow >= 1):
        if (i >= curr_pow):
            div, remainer = divmod(i, curr_pow)
            answer.append(to_hex_digit(div))
            i = remainer
        elif (len(answer) > 0):
            answer.append('0')
        curr_pow //= 16
    return ''.join(answer).rjust(2, '0')


def create_hole(canvas, x, y):
    hole = []
    for i in range(5, -1, -1):
        hole += [canvas.create_rectangle(x + i * 2, y + i * 2, 
                                         x - 50 - i * 2, y - 50 - i * 2, 
                                         outline="black", 
                                         fill="#" + to_hex(i * 40) * 6)]
    return hole
