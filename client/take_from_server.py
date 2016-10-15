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
    data = sock.recv(255, socket.MSG_CONFIRM)
    curr_idx = 0
    height = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
    curr_idx += 4
    width = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
    curr_idx += 4
    arr = [[0] * width for i in range(height)]
    for i in range(height):
        for j in range(width):
            arr[i][j] = int.from_bytes(data[curr_idx:curr_idx + 4], byteorder)
            curr_idx += 4
    return arr