import socket
from sys import byteorder


def init():
    ip = "127.0.0.1"
    Port = 5050
    sock = socket.socket()
    while (Port < 5060 and sock.connect_ex((ip, Port))):
        Port += 1
    if (Port == 5060):
        print("couldn't connect")
        exit(0)
    return sock


def return_array(sock):
    sock.send(bytearray([1]), socket.MSG_CONFIRM)
    #it's a query for server, it understands, that we need field after that message
    data = sock.recv(1024 * 1024, socket.MSG_CONFIRM)
    curr_idx = 0
    height = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
    curr_idx += 4
    width = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
    curr_idx += 4
    field = [[0] * width for i in range(height)]
    for i in range(height):
        for j in range(width):
            field[i][j] = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
            curr_idx += 4
    count = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
    curr_idx += 4
    list_of_coords = [0] * count
    for i in range(count):
        x = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
        y = int.from_bytes(data[curr_idx + 4:curr_idx + 8], byteorder)
        list_of_coords[i] = (x, y)
        curr_idx += 8
    return field, list_of_coords
