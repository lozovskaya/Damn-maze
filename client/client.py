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
height, width = int.from_bytes(data[:4], byteorder), int.from_bytes(data[4:8], byteorder)
arr = [[int.from_bytes(data[8 + i * width * 4 + j * 4:12 + i * width * 4 + j * 4], byteorder) for j in range(width)] 
for i in range(height)]
print('\n'.join(map(str, arr)))

#число из байт - int.from_bytes(bytarray, byteorder)
#bytearray - последовательность байтов, как массив, только каждое от 0 до 255
#recv возвращает именно его, и send принимает его
