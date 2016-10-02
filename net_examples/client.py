import socket
from sys import byteorder
ip = "127.0.0.1"
Port = 5050
sock = socket.socket()
sock.connect((ip, Port))
#передача строки
sock.send(bytearray("Hello, world".encode("utf-8")))
data = sock.recv(255)
print(data, len(data))
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
