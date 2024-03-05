package edu.tongji.sc.network.socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleMainServer {

	// private Collection threadList=new ArrayList();
	public SimpleMainServer() {
		// TODO Auto-generated constructor stub
		try {
			// Create socket for TCP
			ServerSocket server = new ServerSocket(3333);
			//ChatServiceServer.setUserList(threadList);
			System.out.println("Chat Server Start, waitng on Port 5555...");
			
			while (true) {
				//Second socket for data 
				Socket client = server.accept();
				SimpleService service=new SimpleService(client);
				Thread serviceThread = new Thread(service);
				serviceThread.start();
	//			threadList.add(service);
				
			}
			
//			 BufferedReader in = new BufferedReader(new
//			  InputStreamReader(client .getInputStream())); 
//			  PrintWriter out =  new PrintWriter(client.getOutputStream());
//			  System.out.println("---start Service----"); 
//			     while (true) { //			    	 String  str = in.readLine(); 
//			    	 if (str != null) {
//			    		 System.out.println(str);
//			             out.println("has receive...."); 
//			             out.flush(); 
//			  } else { //close
//			 // connection break;
//				  } } out.close(); client.close();
//			  System.out.println("---end service--");
//			 
//			}
//
		} catch (IOException ioe) {
			System.out.println(ioe);
		}

	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SimpleMainServer server = new SimpleMainServer();
	}

}
