import java.io.FileInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.*;

public class Server {
    private int portNum;
    private String[] availableTorrents = {"src\\x.torrent"};
    DecodedMetafile decodedMetafile = new DecodedMetafile(availableTorrents[0]);
    private ArrayList<byte[]> SHAList = new ArrayList<>();
    private boolean[] isAvailablePieces = new boolean[decodedMetafile.getPiecesCount()];

    {
        for (int i = 0; i < decodedMetafile.getPiecesCount(); ++i) {
            isAvailablePieces[i] = false;
        }
    }

    private Map<Integer, byte[]> availablePieces = new HashMap<>();

    Server(int portNum) {
        this.portNum = portNum;
        initializeServer();
        go();
    }

    //4000 have 2 first parts
    //3000 have 3 second parts
    //3500 have nothing
    private void initializeServer() {

        try {
            FileInputStream fis = new FileInputStream("src\\serverFiles\\" + decodedMetafile.getFilename());
            int pieceLength = decodedMetafile.getPieceLength();

            for (int i = 0; i < 2; ++i) {
                byte[] bytes = new byte[pieceLength];
                int l = fis.read(bytes);
                if (l < pieceLength) {
                    for (int j = l; j < pieceLength; ++j) {
                        bytes[j] = 0;
                    }
                }
                if (portNum == 4000) {
                    availablePieces.put(i, bytes);
                    //System.out.println(Arrays.toString(availablePieces.get(i)));
                    isAvailablePieces[i] = true;
                    byte[] sha = decodedMetafile.getSHA1IPiece(i);
                    //System.out.println(Arrays.toString(sha));
                    SHAList.add(sha);
                }
            }
            //System.out.println("What I found: ");
            //System.out.println(new String(bytes));

            if (portNum == 3000) {
                for (int i = 2; i < decodedMetafile.getPiecesCount(); ++i) {
                    byte[] bytes = new byte[pieceLength];
                    int l = fis.read(bytes);
                    if (l < pieceLength) {
                        for (int j = l; j < pieceLength; ++j) {
                            bytes[j] = 0;
                        }
                    }
                    availablePieces.put(i, bytes);
                    //System.out.println(Arrays.toString(availablePieces.get(i)));
                    isAvailablePieces[i] = true;
                    byte[] sha = decodedMetafile.getSHA1IPiece(i);
                    //System.out.println(Arrays.toString(sha));
                    SHAList.add(sha);

                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public boolean isSHAContains(byte[] sha) {
        for (byte[] b : SHAList) {
            int c = 0;
            for (int i = 0; i < 20; ++i) {
                if (b[i] == sha[i]) {
                    c++;
                }
            }
            if (c == 20) {
                return true;
            }
        }
        return false;
    }

    private void receivingNewPieceFromMyClient(SocketChannel channel, byte[] partOfMessage){
        String ANSI_PURPLE = "\u001B[35m";
        String ANSI_RESET = "\u001B[0m";
        System.out.println(ANSI_PURPLE+"Receiving new part from my Client!"+ANSI_RESET);
        byte[] otherPart = new byte[130 - partOfMessage.length];
        int pieceNum = partOfMessage[1];
        byte[] newPiece = new byte[128];
        System.arraycopy(partOfMessage, 2, newPiece, 0, 66);
        try {
            while(channel.read(ByteBuffer.wrap(otherPart)) < otherPart.length);
            System.arraycopy(otherPart, 0, newPiece, 66, 62);
            System.out.println(ANSI_PURPLE+"Received piece with number "+ pieceNum + ANSI_RESET);
            availablePieces.put(pieceNum, newPiece);
            System.out.println(ANSI_PURPLE+Arrays.toString(availablePieces.get(pieceNum))+ ANSI_RESET);
            isAvailablePieces[pieceNum] = true;
            byte[] sha = decodedMetafile.getSHA1IPiece(pieceNum);
            //System.out.println(Arrays.toString(sha));
            SHAList.add(sha);
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    private boolean handshaking(SocketChannel channel) {
        try {
            byte[] handshake = new byte[68];
            while(channel.read(ByteBuffer.wrap(handshake)) < 68);
            if(handshake[0] != Byte.parseByte("19")){
                receivingNewPieceFromMyClient(channel, handshake);
                return false;
            }
            byte[] clientSHA = new byte[20];
            System.arraycopy(handshake, 28, clientSHA, 0, 20);
            //System.out.println(Arrays.toString(clientSHA));
            if (isSHAContains(clientSHA)) {
                System.out.println("Handshake is correct, data exchanging...");
                channel.write(ByteBuffer.wrap(handshake));
                return true;
            } else {
                System.out.println("Handshake is not correct, closing channel...");
                for (int i = 28; i < 48; ++i) {
                    handshake[i] = 0;
                }
                channel.write(ByteBuffer.wrap(handshake));
                channel.close();
                return false;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    private void dataExchanging(SocketChannel socketChannel) {
        buf.clear();
        try {
            System.out.println("Reading...");
            while ( socketChannel.read(buf) < 1) ;
            System.out.println("Server read " + 1 + " bites");
            buf.flip();
            int pieceNum = 0;
            if (buf.hasRemaining()) {
                byte[] arr = new byte[buf.remaining()];
                buf.get(arr);
                if (arr.length == 1) {
                    pieceNum = arr[0];
                } else {
                    System.out.println("Message from the Client is larger than needed");
                }
                System.out.println("Server sent to Client piece with number " + pieceNum);
            } else {
                System.out.println("I don't know what i should do anymore...");
            }
            buf.clear();
            System.out.println("Writing...");
            byte[] pieceC = availablePieces.get(pieceNum);
            ByteBuffer b = ByteBuffer.allocateDirect(decodedMetafile.getPieceLength());
            b = ByteBuffer.wrap(pieceC);
            System.out.println(Arrays.toString(availablePieces.get(pieceNum)));
            socketChannel.write(b);
            buf.clear();

        } catch (IOException e) {
            System.out.println("Can't read or write. Mb connection reset");

        }
    }

    private boolean connecting() {
        Socket socket = null;
        SocketChannel channel = null;
        try {
            socket = serverSocket.accept();
            System.out.println();
            System.out.println("Connection from: " + socket);
            channel = socket.getChannel();
            if (channel != null) {
                channel.configureBlocking(false);
                channel.register(selector, SelectionKey.OP_READ);
                return true;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }

    private Selector selector = null;
    private ServerSocket serverSocket = null;
    ByteBuffer buf = ByteBuffer.allocateDirect(1024);

    public void go() {
        ServerSocketChannel serverSocketChannel;
        try {
            selector = Selector.open();
            serverSocketChannel = ServerSocketChannel.open();
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
                    if (selKey.isAcceptable()) {
                        if (!connecting()) {
                            selKey.cancel();
                        }
                    }
                    if (selKey.isReadable()) {
                        SocketChannel socketChannel = (SocketChannel) selKey.channel();
                        if (handshaking(socketChannel)) {
                            dataExchanging(socketChannel);
                        }
                        try {
                            System.out.println("Closing...");
                            socketChannel.close();
                        } catch (IOException e) {
                            e.printStackTrace();
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
        Server server = new Server(3000);
    }
}
