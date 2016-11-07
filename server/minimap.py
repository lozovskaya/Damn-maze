import dependencies.png as png


def get_color(x):
    if x == 0:
        return (200, 200, 200, 255)
    elif  x == 1:
        return (64, 32, 0, 255)
    else:
        return (255, 0, 0, 255)

def get_pixel(i, j):
    if (i % width == 0 or j % width == 0):
        return (0, 0, 0, 255)
    else:
        return isWall[i // width][j // width]

try:
    f = open("field.txt")
except:
    f = open("field")
n, m = map(int, f.readline().rstrip().split())
width = 2000 // (n + m)
isWall = [0 for i in range(n)]
for i in range(n):
    isWall[i] = list(map(get_color, map(int, f.readline().rstrip().split())))
new_array = [[get_pixel(i, j) for j in range(m * width)] for i in range(n * width)]

png.from_array(new_array, "RGBA").save("field.png")
