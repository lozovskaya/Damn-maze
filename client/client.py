import socket
from sys import byteorder
ip = "127.0.0.1"
Port = 5051
sock = socket.socket()
while (sock.connect_ex((ip, Port))):
    Port += 1
        
print(sock.send(bytearray([1, 1]), socket.MSG_CONFIRM))
data = sock.recv(255, socket.MSG_CONFIRM)
print(data, len(data))
height, width = int.from_bytes(data[:4], byteorder), int.from_bytes(data[4:8], byteorder)
arr = [[int.from_bytes(data[8 + i * width * 4 + j * 4:12 + i * width * 4 + j * 4], byteorder) for j in range(width)] 
for i in range(height)]
print('\n'.join(map(str, arr)))
#передача числа
print("type a number")
n = int(input())
ba = n.to_bytes(4, byteorder)
sock.send(n.to_bytes(4, byteorder)) 
#(что передать).to_bytes(сколько байт получить, byteorder)
print(int.from_bytes(sock.recv(255), byteorder))

#число из байт - int.from_bytes(bytarray, byteorder)
#bytearray - последовательность байтов, как массив, только каждое от 0 до 255
#recv возвращает именно его, и send принимает его
