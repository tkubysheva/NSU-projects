import java.io.IOException;
import java.net.Socket;
import java.nio.ByteBuffer;


public class Client {
    //private SocketChannel socketChannel;
    private ByteBuffer buffer;
    private Socket clientSocket;


    public Client() {
        try {
            //socketChannel = SocketChannel.open(new InetSocketAddress("localhost", 4000));
            clientSocket = new Socket("localhost", 4000);
            buffer = ByteBuffer.allocate(1024);
            Handshake handshake = new Handshake("", "");
            clientSocket.getOutputStream().write(handshake.getHandshake());
            byte[] newHandshake = new byte[68];
            clientSocket.getInputStream().read(newHandshake);
            boolean flagConnection = true;
            for (int i = 0; i < 68; ++i) {
                if (newHandshake[i] != handshake.getHandshake()[i]) {
                    flagConnection = false;
                    break;
                }
            }
            if (!flagConnection) {
                clientSocket.close();
            }
            else{
                sendMessage("Hello!");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Client is ready!");
    }

    public void sendMessage(String msg) {
        buffer = ByteBuffer.wrap(msg.getBytes());
        try {
            clientSocket.getOutputStream().write(buffer.array());
            buffer.clear();

            clientSocket.getInputStream().read(buffer.array());
            System.out.println(new String(buffer.array()));
            buffer.clear();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        Client client1 = new Client();
        client1.sendMessage("Hello!!");/*
        client1.sendMessage("My name is Client!");
        client1.sendMessage("exit");
        Client client2 = new Client();
        client2.sendMessage("I'm second");
        client2.sendMessage("I'm happy");
        client2.sendMessage("exit");

         */
    }
}
