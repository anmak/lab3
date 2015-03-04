package network;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class network {

	// server socket set
  public final static int SOCKET_PORT = 55958;  
  // destination of the  file where  file uploaded is saved
  public final static String FILE_TO_RECEIVED = "C:\\Users\\anam\\Desktop\\file1.txt";;  
  // size of the file
  public final static int FILE_SIZE = 6022986;
  public static void main (String [] args ) throws IOException {
	  int bytesRead;  
	  int current=0;
	FileOutputStream fos = null;
	BufferedOutputStream bos = null;
    OutputStream os = null;
    ServerSocket servsock = null;
    Socket sock = null;
    try {
      servsock = new ServerSocket(SOCKET_PORT);
      while (true) {
    	  
        System.out.println("Waiting.");
        try {
          sock = servsock.accept();
          System.out.println("Accepted connection : " + sock);
          // send file
          byte [] mybytearray  = new byte [FILE_SIZE];
          InputStream is = sock.getInputStream();
          fos = new FileOutputStream(FILE_TO_RECEIVED);
          bos = new BufferedOutputStream(fos);
          bytesRead = is.read(mybytearray,0,mybytearray.length);
          current = bytesRead;

          do {
             bytesRead =
                is.read(mybytearray, current, (mybytearray.length-current));
             if(bytesRead >= 0) current += bytesRead;
          } while(bytesRead > -1);

          bos.write(mybytearray, 0 , current);
          bos.flush();
          System.out.println("File " + FILE_TO_RECEIVED
              + " downloaded (" + current + " bytes read)");
          
        }
        finally {
          if (bos != null) bos.close();
          if (os != null) os.close();
          if (sock!=null) sock.close();
        }
      }
    }
    finally {
      if (servsock != null) 
    	  servsock.close();
    }
  }
}
