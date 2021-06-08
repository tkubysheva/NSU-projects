

public class Handshake {
    private byte[] handshakeInfo = new byte[68];
    Handshake(byte[] info_hash, byte[] peer_id){
        handshakeInfo[0] = Byte.parseByte("19");
        String c = "BitTorrent Protocol";
        int i = 1;
        for(char s: c.toCharArray()){
            handshakeInfo[i] = (byte) s;
            i++;
        }
        for(int j = 20; j < 28; ++j ){
            handshakeInfo[j] = ' ';
        }
        i = 28;
        if(info_hash.length == 0){
            info_hash = "12345678901234567890".getBytes();
        }
        for(byte s: info_hash){
            handshakeInfo[i] = s;
            i++;
        }
        if(peer_id.length == 0){
            peer_id = "12345678901234567890".getBytes();
        }
        for(byte s: peer_id){
            handshakeInfo[i] = s;
            i++;
        }
    }

    public byte[] getHandshake() {
        return handshakeInfo;
    }
}
