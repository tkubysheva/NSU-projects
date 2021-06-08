import be.adaxisoft.bencode.BDecoder;
import be.adaxisoft.bencode.BEncodedValue;
import be.adaxisoft.bencode.InvalidBEncodingException;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Map;


public class Client {
    //private SocketChannel socketChannel;
    private byte[] peerID;
    private int numPort;
    private String[] URL;
    private String filename;
    private String nameMetaInfoFile;
    private byte[] sha1;
    private int length;
    private int pieceLength;
    private int piecesCount;
    private int receivedPiecesCount = 0;
    private boolean[] isReceivedPieces;
    private byte[][] receivedPieces;
    private Map<String, BEncodedValue> document;
    private Map<String, BEncodedValue> info;
    private ByteBuffer buffer;
    private Socket clientSocket;

    private void decodeMetaFile() {
        try {
            FileInputStream inputStream = new FileInputStream(nameMetaInfoFile);
            BDecoder reader = new BDecoder(inputStream);
            document = reader.decodeMap().getMap();
            info = document.get("info").getMap();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void stop() {
        try {
            clientSocket.close();
        } catch (IOException e) {
            System.out.println("Error in closing client socket");
        }

    }

    private void getInfoFromMetaFile() {
        try {
            URL = document.get("announce").getString().split(" ");
            filename = info.get("name").getString();
            sha1 = info.get("pieces").getBytes();
            length = info.get("length").getInt();
            pieceLength = info.get("piece length").getInt();
        } catch (InvalidBEncodingException e) {
            e.printStackTrace();
        }
        piecesCount = (int) Math.ceil((double) length / (double) pieceLength);
        receivedPieces = new byte[piecesCount][pieceLength];
        isReceivedPieces = new boolean[piecesCount];
        for (int i = 0; i < piecesCount; ++i) {
            isReceivedPieces[i] = false;
        }
        numPort = Integer.parseInt(URL[1]);
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

    private boolean handshaking(byte[] info_hash) {
        try {
            Handshake handshake = new Handshake(info_hash, this.peerID);
            System.out.println("I want piece");
            clientSocket.getOutputStream().write(handshake.getHandshake());
            byte[] newHandshake = new byte[68];
            clientSocket.getInputStream().read(newHandshake);
            for (int i = 0; i < 48; ++i) {
                if (newHandshake[i] != handshake.getHandshake()[i]) {
                    return false;
                }
            }
            System.out.println("Server have my piece!");
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    void collectAllPiecesTogether() {
        try (PrintWriter writer = new PrintWriter("src\\ClientFiles\\" + filename, StandardCharsets.UTF_8)) {
            for (int i = 0; i < piecesCount; ++i) {
                for (int j = 0; j < pieceLength; ++j) {
                    if(receivedPieces[i][j] != 0) {
                        writer.print((char) receivedPieces[i][j]);
                    }
                }
            }
        } catch (IOException e) {
            System.out.println("Can't create output file");
            e.printStackTrace();
        }
    }


    public Client(String nameMetaInfoFile, String peerID) {
        this.peerID = peerID.getBytes();
        this.nameMetaInfoFile = nameMetaInfoFile;
        decodeMetaFile();
        getInfoFromMetaFile();
        try {
            clientSocket = new Socket(URL[0], numPort);
            buffer = ByteBuffer.allocate(pieceLength);
            System.out.println(pieceLength);
            while (receivedPiecesCount != piecesCount) {
                for (int i = 0; i < piecesCount; ++i) {
                    if (!isReceivedPieces[i]) {
                        if (!handshaking(getSHA1IPiece(i))) {
                            System.out.println("Server doesn't have the required part :(");
                            clientSocket.close();
                        } else {
                            sendMessage(i);
                            isReceivedPieces[i] = true;
                            receivedPiecesCount++;
                            //clientSocket.
                        }
                    }
                }
            }
            collectAllPiecesTogether();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void sendMessage(int pieceNum) {
        buffer.clear();
        buffer = ByteBuffer.wrap(getSHA1IPiece(pieceNum));
        try {

            System.out.println("Give me this piece");
            clientSocket.getOutputStream().write(buffer.array());
            buffer.clear();
            System.out.println("I'm waiting for your answer!!!");
            int i = clientSocket.getInputStream().read(receivedPieces[pieceNum]);

            if(i != 0){
                System.out.println("I get " + i + " bytes:");
                System.out.println(new String(receivedPieces[pieceNum], StandardCharsets.UTF_8));
            }else{
                System.out.println("I didn't get it :(");
            }



        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        Client client1 = new Client("src\\x.torrent", "12312312323423445656");
        /*
        client1.sendMessage("Hello!!");
        client1.sendMessage("exit");
        client1.sendMessage("My name is Client!");
        //client1.stop();
        Client client2 = new Client();
        client2.sendMessage("I'm second");
        client2.sendMessage("I'm happy");
        client2.sendMessage("exit");

         */
    }
}