import java.io.DataInputStream;
import java.io.FileOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Force {

    private static int port;
    private static String DatafilePath;
    public static void init(){


    }
    public static void fileHandle(){

    }
    public static void main(String[] args){
        boolean ok=true;
        ServerSocket socket_recieve=null;
        Socket recieve=null;
        FileOutputStream fOut=null;
        try {
            InetAddress address;
            String ad="172.031.001.154";
            address=InetAddress.getByAddress(ad.getBytes());
            socket_recieve = new ServerSocket(1235,0,address);
            socket_recieve.setSoTimeout(100000);
            fOut = new FileOutputStream("FTOUT.txt");
            recieve = socket_recieve.accept();
            System.out.println(socket_recieve.toString());
            recieve.setSoTimeout(100000);
        }
        catch (Exception E){
            E.printStackTrace();
            ok=false;
        }
        while(ok) {
            try {

                DataInputStream dis = new DataInputStream(recieve.getInputStream());
                String info=dis.readUTF();
                dis.close();
                fOut.write(info.getBytes());
            } catch (Exception E) {
                E.printStackTrace();
                break;
            }
        }
    }
}
