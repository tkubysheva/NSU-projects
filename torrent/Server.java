import be.adaxisoft.bencode.BDecoder;
import be.adaxisoft.bencode.BEncodedValue;
import be.adaxisoft.bencode.InvalidBEncodingException;

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
import java.util.Arrays;
import java.util.Iterator;
import java.util.Map;

public class Server {
    private int portNum;
    private String[] availableTorrents = {"src\\x.torrent"};
    private byte[] sha1;
    private int length;
    private int pieceLength;
    private int piecesCount;
    private String filename;
    private Map<String, BEncodedValue> document;
    private Map<String, BEncodedValue> info;

    private void decodeMetaFile() {
        try {
            FileInputStream inputStream = new FileInputStream(availableTorrents[0]);
            BDecoder reader = new BDecoder(inputStream);
            document = reader.decodeMap().getMap();
            info = document.get("info").getMap();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void getInfoFromMetaFile() {
        try {
            sha1 = info.get("pieces").getBytes();
            length = info.get("length").getInt();
            filename = info.get("name").getString();
            pieceLength = info.get("piece length").getInt();
        } catch (InvalidBEncodingException e) {
            e.printStackTrace();
        }
        piecesCount = (int) Math.ceil((double) length / (double) pieceLength);
    }

    private byte[] getSHA1IPiece(int i) {
        byte[] iSHA = new byte[20];
        for (int j = 0; j < 20; ++j) {
            if (i * 20 + j < sha1.length) {
                iSHA[j] = sha1[i * 20 + j];
            } else {
                iSHA[j] = 0;
            }
        }
        return iSHA;
    }

    private int searchRequiredSHAPart(byte[] clientSHA) {
        decodeMetaFile();
        getInfoFromMetaFile();
        for (int i = 0; i < piecesCount; ++i) {
            byte[] s = getSHA1IPiece(i);
            int c = 0;
            for (int j = 0; j < 20; j++) {
                if (s[j] == clientSHA[j]) {
                    c++;
                }
            }
            if (c == 20) {
                return i;
            }
        }
        return -1;
    }

    Server(int portNum) {
        this.portNum = portNum;
        go();
    }

    private boolean handshaking() {
        Socket socket = null;
        SocketChannel channel = null;
        try {
            //Handshake handshake = new Handshake("".getBytes(), "".getBytes());
            socket = serverSocket.accept();
            System.out.println("Connection from: " + socket);
            channel = socket.getChannel();


            byte[] clientHandshake = new byte[68];
            channel.read(ByteBuffer.wrap(clientHandshake));
            byte[] clientSHA = new byte[20];
            System.arraycopy(clientHandshake, 28, clientSHA, 0, 20);
            if (searchRequiredSHAPart(clientSHA) != -1) {
                channel.configureBlocking(false);
                channel.register(selector, SelectionKey.OP_READ);
                System.out.println("handshake ok");
                channel.write(ByteBuffer.wrap(clientHandshake));
                return true;
            } else {
                System.out.println("handshake wrong");
                channel.close();
                return false;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    private void getIPartOfFile(int pieceNum){

        try{
            FileInputStream fis = new FileInputStream("src\\serverFiles\\"+filename);
            byte[] bytes = new byte[pieceLength];
            int lengthP = pieceLength;
            System.out.println(pieceLength*(pieceNum + 1));
            System.out.println(length);
            if(pieceLength*(pieceNum + 1) > length){
                lengthP = length - pieceLength*pieceNum;
                System.out.println(lengthP);
            }

            fis.read(bytes, pieceLength*pieceNum, lengthP);
            //System.out.println("What I found: ");
            //System.out.println(new String(bytes));
            buf = ByteBuffer.wrap(bytes);
            /*
            if(buf.hasRemaining()) {
                byte[] arr = new byte[buf.remaining()];
                buf.get(arr);
                System.out.println(Arrays.toString(arr));
            }
             */
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    private void dataExchanging(SelectionKey selKey) {
        SocketChannel socketChannel = (SocketChannel) selKey.channel();
        buf.clear();
        try {
            socketChannel.read(buf);
            buf.flip();
            System.out.println("Reading...");
            int pieceNum = 0;
            if(buf.hasRemaining()) {
                byte[] arr = new byte[buf.remaining()];
                buf.get(arr);
                System.out.println("SHA1:");
                System.out.println(Arrays.toString(arr));
                pieceNum = searchRequiredSHAPart(arr);
                if(pieceNum == -1){
                    System.out.println("THAT IS ALL");
                }
                //System.out.println(pieceNum);
            }
            else{
                System.out.println("I don't know what i should do anymore...");
            }
            buf.clear();
            System.out.println("Writing...");
            getIPartOfFile(pieceNum);
            /*
            if(buf.hasRemaining()) {
                byte[] arr = new byte[buf.remaining()];
                buf.get(arr);
                System.out.println(Arrays.toString(arr));
            }
             */
            socketChannel.write(buf);
            buf.clear();
        } catch (IOException e) {
            System.out.println("Can't read or write. Mb connection reset");
            selKey.cancel();
        }
    }

    private Selector selector = null;
    private ServerSocket serverSocket = null;
    ByteBuffer buf = ByteBuffer.allocateDirect(1024);

    public void go() {
        int c = 0;
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
                    if (selKey.isAcceptable() ) {

                        if (!handshaking()) {
                            continue;
                        }
                    }
                    if (selKey.isReadable()) {
                        dataExchanging(selKey);

                    }
                    else{
                        System.out.println("Not readable");
                    }
                    c++;
                    System.out.println("Next...");
                    if(c > 10){
                        break;
                    }
                }
                if(c > 10){
                    break;
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
