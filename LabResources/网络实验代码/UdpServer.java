package edu.tongji.networklab.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

public class UdpServer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		UdpServer server=new UdpServer();
	}
    private byte[] buffer=new byte[101];
    private DatagramPacket request;
	public UdpServer() {
		try{
		// TODO Auto-generated constructor stub
		DatagramSocket server=new DatagramSocket(5555);
		System.out.println("UDP Server Start, wait on Port 5555 ...");
		request=new DatagramPacket(buffer, buffer.length);
		while(true){
            //receive message
			server.receive(request);
			String req=new String(request.getData()).trim();
			//System.out.println("Request:"+request.getAddress().getHostName());
			System.out.println("Request:"+req);
			//send message
			//DatagramPacket response=new DatagramPacket(buffer, buffer.length);
			server.send(request);
		}
		}catch(SocketException se){
			
		}catch(IOException ioe){
			
		}
	}

}

