public class Handshake {
    private byte[] handshakeInfo = new byte[68];
    Handshake(String info_hash, String peer_id){
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
        if(info_hash.isEmpty()){
            info_hash = "12345678901234567890";
        }
        for(char s: info_hash.toCharArray()){
            handshakeInfo[i] = (byte)s;
            i++;
        }
        if(peer_id.isEmpty()){
            peer_id = "12345678901234567890";
        }
        for(char s: peer_id.toCharArray()){
            handshakeInfo[i] = (byte)s;
            i++;
        }
    }

    public byte[] getHandshake() {
        return handshakeInfo;
    }
}
