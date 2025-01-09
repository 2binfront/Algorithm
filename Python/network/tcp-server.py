import socket
import threading


class TCPServer:
    def __init__(self, host="127.0.0.1", port=9999):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        self.clients = []
        print(f"服务器启动成功，监听地址：{self.host}:{self.port}")

    def handle_client(self, client_socket, address):
        """处理单个客户端连接"""
        print(f"新的连接来自: {address}")

        try:
            while True:
                # 接收数据
                data = client_socket.recv(1024)
                if not data:
                    break

                message = data.decode("utf-8")
                print(f"收到来自 {address} 的消息: {message}")

                # 广播消息给所有客户端
                self.broadcast(f"客户端 {address}: {message}", client_socket)

                # 发送确认消息给发送方
                response = f"服务器已收到消息: {message}"
                client_socket.send(response.encode("utf-8"))

        except Exception as e:
            print(f"处理客户端 {address} 时发生错误: {e}")
        finally:
            self.clients.remove(client_socket)
            client_socket.close()
            print(f"客户端 {address} 断开连接")

    def broadcast(self, message, sender_socket=None):
        """向所有客户端广播消息，除了发送者"""
        for client in self.clients:
            if client != sender_socket:
                try:
                    client.send(message.encode("utf-8"))
                except:
                    self.clients.remove(client)

    def start(self):
        """启动服务器并接受连接"""
        try:
            while True:
                client_socket, address = self.server_socket.accept()
                self.clients.append(client_socket)

                # 为每个客户端创建一个新线程
                client_thread = threading.Thread(
                    target=self.handle_client, args=(client_socket, address)
                )
                client_thread.daemon = True
                client_thread.start()

        except KeyboardInterrupt:
            print("\n服务器关闭")
        finally:
            self.server_socket.close()


if __name__ == "__main__":
    server = TCPServer("0.0.0.0", 8080)
    server.start()
