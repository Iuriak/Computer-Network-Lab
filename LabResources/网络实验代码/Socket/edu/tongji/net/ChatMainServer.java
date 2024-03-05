package edu.tongji.net;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collection;

public class ChatMainServer {

	private Collection threadList=new ArrayList();
	public ChatMainServer() {
		// TODO Auto-generated constructor stub
		try {
			// Create socket for TCP
			ServerSocket server = new ServerSocket(5555);
			ChatServiceServer.setUserList(threadList);
			System.out.println("Chat Server Start, waitng on Port 5555...");
			
			while (true) {
				Socket client = server.accept();
				ChatServiceServer service = new ChatServiceServer(client);
				//Thread serviceThread = new Thread(service);
				service.start();
				//serviceThread.start();
				threadList.add(service);
				
			}
			/*
			 * BufferedReader in = new BufferedReader(new
			 * InputStreamReader(client .getInputStream())); PrintWriter out =
			 * new PrintWriter(client.getOutputStream());
			 * System.out.println("---start Service----"); while (true) { String
			 * str = in.readLine(); if (str != null) { System.out.println(str);
			 * out.println("has receive...."); out.flush(); } else { //close
			 * connection break; } } out.close(); client.close();
			 * System.out.println("---end service--");
			 */
			// }

		} catch (IOException ioe) {
			System.out.println(ioe);
		}

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ChatMainServer server=new ChatMainServer();
	}

}
