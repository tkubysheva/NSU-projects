import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;


public class Client {
    private SocketChannel socketChannel;
    private ByteBuffer buffer;
    private Socket clientSocket;
    private BufferedReader in;
    private BufferedWriter out;

    public Client() {
        try {
            socketChannel = SocketChannel.open(new InetSocketAddress("localhost", 4000));
            clientSocket = new Socket("localhost", 4000);
            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
            out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
            buffer = ByteBuffer.allocate(256);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Client is ready!");
    }

    public void sendMessage(String msg) {
        buffer = ByteBuffer.wrap(msg.getBytes());
        try {
            socketChannel.write(buffer);
            buffer.clear();

            socketChannel.read(buffer);
            System.out.println(new String(buffer.array()));
            buffer.clear();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        Client client1 = new Client();
        client1.sendMessage("Hello!");
        client1.sendMessage("My name is Client!");
        client1.sendMessage("exit");
        Client client2 = new Client();
        client2.sendMessage("I'm second");
        client2.sendMessage("I'm happy");
        client2.sendMessage("exit");
    }
}
