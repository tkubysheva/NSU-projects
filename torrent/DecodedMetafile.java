import be.adaxisoft.bencode.BDecoder;
import be.adaxisoft.bencode.BEncodedValue;
import be.adaxisoft.bencode.InvalidBEncodingException;

import java.io.FileInputStream;
import java.util.Map;

public class DecodedMetafile {
    public DecodedMetafile(String torrentName){
        metaName = torrentName;
        decodeMetaFile();
        getInfoFromMetaFile();
    }
    private String[] URL;
    private String metaName;
    private byte[] sha1;
    private int length;
    private int pieceLength;
    private int piecesCount;
    private String filename;
    private Map<String, BEncodedValue> document;
    private Map<String, BEncodedValue> info;


    public int getLength() {
        return length;
    }

    public int getPieceLength() {
        return pieceLength;
    }

    public int getPiecesCount() {
        return piecesCount;
    }

    public String getFilename() {
        return filename;
    }

    public void decodeMetaFile() {
        try {
            FileInputStream inputStream = new FileInputStream(metaName);
            BDecoder reader = new BDecoder(inputStream);
            document = reader.decodeMap().getMap();
            info = document.get("info").getMap();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public String getURL(){
        return URL[0];
    }
    public int getNumPort(){
        return Integer.parseInt(URL[1]);
    }
    public void getInfoFromMetaFile() {
        try {
            URL = document.get("announce").getString().split(" ");
            sha1 = info.get("pieces").getBytes();
            length = info.get("length").getInt();
            filename = info.get("name").getString();
            pieceLength = info.get("piece length").getInt();
        } catch (InvalidBEncodingException e) {
            e.printStackTrace();
        }
        piecesCount = (int) Math.ceil((double) length / (double) pieceLength);
    }

    public byte[] getSHA1IPiece(int i) {
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

    public int searchRequiredSHAPart(byte[] clientSHA) {
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
}
