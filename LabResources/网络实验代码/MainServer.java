package edu.tongji.sc.network.socket;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collection;

public class MainServer {
	private Collection threadList=new ArrayList();
	public MainServer() {
		// TODO Auto-generated constructor stub
		try {
			// Create socket for TCP
			ServerSocket server = new ServerSocket(5588);
			ServiceServer.setUserList(threadList);
			System.out.println("Chat Server Start, waitng on Port 5555...");
			
			while (true) {
				Socket client = server.accept();
				ServiceServer service = new ServiceServer(client);
				Thread thread=new Thread(service);
				thread.start();
				//service.start();
				threadList.add(service);			
			}
		} catch (IOException ioe) {
			System.out.println(ioe);
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MainServer server=new MainServer();
	}
}
