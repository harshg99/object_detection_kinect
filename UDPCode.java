import java.net.*;

public class UDPCode {
    static DatagramSocket socket;
    static byte[] data;

    public static void main(String[] args) throws Exception{
        InetAddress  address;
        socket=new DatagramSocket(5198)  ;
        //System.out.println(socket .getLocalAddress().getHostAddress());
        //System.out.println(socket.getLocalSocketAddress());
        int portSend=24215;
        address=InetAddress.getByName("172.31.1.147");


        //Socket socket_s=new Socket("172.31.1.147",30001);
        data=new byte[1024];

            while(true)
            {
                //receive data
                DatagramPacket receivePacket = new DatagramPacket(data, data.length);
                socket.receive(receivePacket);

                //display
                String sentence = new String( receivePacket.getData());
                System.out.println("RECEIVED: " + sentence);
                int i;
                for(i=0;i<sentence.length();i++){
                    if(sentence.charAt(i)>127)
                        break;
                }
                String Sent2=sentence.substring(0,i);
                System.out.println(Sent2);
                InetAddress IPAddress = receivePacket.getAddress();
                int port = receivePacket.getPort();
                String capitalizedSentence = sentence.toUpperCase();
                System.out.println(IPAddress.getHostAddress()+" : "+port);

               //send to server on other computer

                /*try{
                    DataOutputStream dout=new DataOutputStream(socket_s.getOutputStream());
                    dout.writeUTF(Sent2);
                    dout.flush();
                    dout.close();
                }
                catch(Exception e){
                    System.out.println(e);
                }
                */
            }
    }
}
