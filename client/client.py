import socket
from sys import byteorder
ip = "127.0.0.1"
Port = 5050
sock = socket.socket()
while (Port < 5060 and sock.connect_ex((ip, Port))):
    Port += 1
if (Port == 5060):
    print("couldn't connect")
    exit(0)

print(sock.send(bytearray([1]), socket.MSG_CONFIRM))
#it's a query for server, it understands, that we need field after that message
data = sock.recv(255, socket.MSG_CONFIRM)
print(data, len(data))
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
print('\n'.join(map(str, arr)))

#число из байт - int.from_bytes(bytarray, byteorder)
#bytearray - последовательность байтов, как массив, только каждое от 0 до 255
#recv возвращает именно его, и send принимает его
