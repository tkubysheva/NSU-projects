import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;

public class Server {
    private int portNum;

    Server(int portNum) {
        this.portNum = portNum;
        go();
    }


    public void go() {

        Selector selector = null;
        ServerSocket serverSocket = null;
        ByteBuffer buf = ByteBuffer.allocateDirect(1024);

        try {
            selector = Selector.open();
            ServerSocketChannel serverSocketChannel =
                    ServerSocketChannel.open();
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.socket().bind(new InetSocketAddress(portNum));
            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
            serverSocket = serverSocketChannel.socket();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(-1);
        }
        try {
            System.out.println("Server is running!");
            while (true) {
                int count = selector.select();
                if (count == 0) {
                    continue;
                }
                Iterator it = selector.selectedKeys().iterator();
                while (it.hasNext()) {
                    SelectionKey selKey = (SelectionKey) it.next();
                    it.remove();
                    Socket socket;
                    SocketChannel channel = null;
                    if (selKey.isAcceptable()) {
                        try {
                            socket = serverSocket.accept();
                            System.out.println("Connection from: " + socket);
                            channel = socket.getChannel();
                            channel.configureBlocking(false);
                            channel.register(selector, SelectionKey.OP_READ);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    if (selKey.isReadable() ) {
                        SocketChannel socketChannel = (SocketChannel) selKey.channel();
                        buf.clear();
                        try {
                            while (socketChannel.read(buf) > 0) {
                                System.out.println("Reading...");
                                buf.flip();
                                while (buf.hasRemaining()) {
                                    System.out.println("Writing...");
                                    socketChannel.write(buf);
                                }
                                buf.clear();
                            }
                        } catch (IOException e) {
                            System.out.println("Can't read or write. Mb connection reset");
                            selKey.cancel();
                        }
                    }
                    System.out.println("Next...");
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        Server server = new Server(4000);
    }
}
