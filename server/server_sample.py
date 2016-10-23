import socket
sock = socket.socket()
sock.bind(("127.0.0.1", 5050))
sock.listen(1)
client = sock.accept()[0]
field = bytearray([1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0])
client.send(field)
