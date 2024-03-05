package edu.tongji.net;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class HTTPServer {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			// TODO Auto-generated method stub
			ServerSocket server = new ServerSocket(88);
			Socket client = server.accept();

			BufferedReader in = new BufferedReader(new InputStreamReader(client
					.getInputStream()));
			PrintWriter out = new PrintWriter(client.getOutputStream());
			System.out.println("---start Service----");

			while (true) {
				String str = in.readLine();
				if (str != null) {
					System.out.println(str);
					out.println("has receive....");
					out.flush();
				} else {
					// close connection
					break;
				}
			}
			out.close();
			client.close();
			System.out.println("---end service--");

		} catch (IOException ioe) {
			System.out.println(ioe);
		}

	}

}
