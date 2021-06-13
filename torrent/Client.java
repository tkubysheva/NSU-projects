import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;


public class Client {
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_GREEN = "\u001B[32m";
    private int serverPort;
    private byte[] peerID;
    private ArrayList<Integer> availablePeers = new ArrayList<>();
    /*
    {
        availablePeers.add(4000);
        availablePeers.add(3000);
    }

     */
    DecodedMetafile decodedMetafile;
    private int receivedPiecesCount = 0;
    public boolean[] isReceivedPieces;
    public Map<Integer, byte[]> receivedPieces;
    private Socket clientSocket;

    private void getInfoFromMetaFile() {
        receivedPieces = new HashMap<>();
        isReceivedPieces = new boolean[decodedMetafile.getPiecesCount()];
        for (int i = 0; i < decodedMetafile.getPiecesCount(); ++i) {
            isReceivedPieces[i] = false;
        }

    }


    private boolean handshaking(byte[] info_hash) {
        try {
            Handshake handshake = new Handshake(info_hash, this.peerID);
            clientSocket.getOutputStream().write(handshake.getHandshake());
            byte[] newHandshake = new byte[68];
            clientSocket.getInputStream().read(newHandshake);
            for (int i = 0; i < 48; ++i) {
                if (newHandshake[i] != handshake.getHandshake()[i]) {
                    return false;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return true;
    }

    void collectAllPiecesTogether() {
        System.out.println(ANSI_GREEN+"Loading parts is complete!"+ANSI_RESET);
        System.out.println(ANSI_YELLOW+"Building file..."+ANSI_RESET);
        try (PrintWriter writer = new PrintWriter("src\\ClientFiles\\" + serverPort +decodedMetafile.getFilename(), StandardCharsets.UTF_8)) {
            for (int i = 0; i < decodedMetafile.getPiecesCount(); ++i) {
                for (int j = 0; j < decodedMetafile.getPieceLength(); ++j) {
                    if(receivedPieces.get(i)[j] != 0) {
                        writer.print((char) receivedPieces.get(i)[j]);
                    }
                }
            }
            System.out.println(ANSI_GREEN+"File uploaded successfully!"+ANSI_RESET);
        } catch (IOException e) {
            System.out.println(ANSI_YELLOW+"Can't create output file"+ANSI_RESET);
            e.printStackTrace();
        }
    }
    private void initial(int port, String nameMetaInfoFile, String[] ports){
        serverPort = port;
        availablePeers.add(serverPort);
        for(int i = 3; i < ports.length; ++i){
            availablePeers.add(Integer.parseInt(ports[i]));
        }
        decodedMetafile = new DecodedMetafile(nameMetaInfoFile);
        peerID = "12312312323423445656".getBytes();
        getInfoFromMetaFile();
    }

    private boolean connecting(int peerNum){
        System.out.println();
        try {
            clientSocket = new Socket("localhost", availablePeers.get(peerNum));
            System.out.println(ANSI_YELLOW+"Connect to " + clientSocket+ANSI_RESET);
        } catch (IOException e) {
            System.out.println(ANSI_YELLOW+availablePeers.get(peerNum) + " port not available"+ANSI_RESET);
            return false;
        }
        return true;
    }
    private void waiting(){
        try {
            Thread.sleep (5000);
        } catch (InterruptedException e) {
            e.printStackTrace ();
        }
    }

    private void sendTheReceivedPieceToMyServer(int pieceNum){
        System.out.println(ANSI_CYAN+"Send piece to my Server"+ANSI_RESET);
        try {
            clientSocket = new Socket("localhost", serverPort);
            System.out.println(ANSI_CYAN+"Connect to " + clientSocket+ANSI_RESET);
        } catch (IOException e) {
            System.out.println(ANSI_CYAN+serverPort + " port not available"+ANSI_RESET);
            return;
        }
        byte[] newPiece = new byte[2 + decodedMetafile.getPieceLength()];
        newPiece[0] = 1;
        newPiece[1] = Integer.valueOf(pieceNum).byteValue();
        System.arraycopy(receivedPieces.get(pieceNum), 0, newPiece, 2, decodedMetafile.getPieceLength());
        try{
            clientSocket.getOutputStream().write(newPiece);
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    public Client(int myServerPort, String nameMetaInfoFile, String[] ports) {
        System.out.println(ANSI_YELLOW+"Initial begin"+ANSI_RESET);
        initial(myServerPort, nameMetaInfoFile, ports);
        System.out.println(ANSI_YELLOW+"Initial finish"+ANSI_RESET);
        int i = 0;
        while (receivedPiecesCount != decodedMetafile.getPiecesCount()) {
            for(int p = 0; p < availablePeers.size(); ++p) {
                if(!connecting(p)){
                    continue;
                }
                try {
                    if (!isReceivedPieces[i]) {
                        byte[] sha1 = decodedMetafile.getSHA1IPiece(i);
                        if (handshaking(sha1)) {
                            sendMessage(sha1, i);
                            isReceivedPieces[i] = true;
                            receivedPiecesCount++;
                            if(availablePeers.get(p) != serverPort){
                                sendTheReceivedPieceToMyServer(i);
                            }
                            waiting();
                        } else {
                            System.out.println(ANSI_YELLOW+"Server doesn't have the required part :("+ANSI_RESET);
                            clientSocket.close();
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
                i = (i+1)%decodedMetafile.getPiecesCount();
            }
        }
        collectAllPiecesTogether();
    }

    public void sendMessage(byte[] sha1, int pieceNum) {
        try {
            System.out.println(ANSI_YELLOW+"Client asks the server for piece number "+ pieceNum+ANSI_RESET);
            System.out.println(ANSI_YELLOW+"Piece's SHA1: "+Arrays.toString(sha1)+ANSI_RESET);
            clientSocket.getOutputStream().write(Integer.valueOf(pieceNum).byteValue());
            byte[] buf = new byte[decodedMetafile.getPieceLength()];
            int i = clientSocket.getInputStream().read(buf);
            receivedPieces.put(pieceNum, buf);
            if(i != 0){
                System.out.println(ANSI_YELLOW+"Client gets " + i + " bytes."+ANSI_RESET);
                //System.out.println(ANSI_YELLOW+new String(receivedPieces.get(pieceNum), StandardCharsets.UTF_8)+ANSI_RESET);
            }else{
                System.out.println(ANSI_YELLOW+"Client didn't receive a piece :("+ANSI_RESET);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        //Client client1 = new Client(3000, "src\\x.torrent");
    }
}