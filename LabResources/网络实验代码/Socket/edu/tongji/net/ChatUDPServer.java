package edu.tongji.net;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class ChatUDPServer {
    private byte[] buffer=new byte[101];
    private DatagramPacket request;
	public ChatUDPServer() {
		try{
		// TODO Auto-generated constructor stub
		DatagramSocket server=new DatagramSocket(5555);
		System.out.println("UDP Server Start, wait on Port 5555 ...");
		request=new DatagramPacket(buffer, buffer.length);
		while(true){
            //receive message
			server.receive(request);
			String req=new String(request.getData()).trim();
			System.out.println("Request:"+request.getAddress().getHostName());
			//send message
			//DatagramPacket response=new DatagramPacket(buffer, buffer.length);
			server.send(request);
		}
		}catch(SocketException se){
			
		}catch(IOException ioe){
			
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
ChatUDPServer server=new ChatUDPServer();
	}

}
