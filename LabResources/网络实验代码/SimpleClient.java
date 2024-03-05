package edu.tongji.sc.network.socket;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ConnectException;
import java.net.Socket;

public class SimpleClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			// Open your connection to a server, at port 5432
			// localhost used here
			System.out.println("Start client");
			Socket s1 = new Socket("127.0.0.1", 3333);
			PrintWriter out = new PrintWriter(s1.getOutputStream());
			out.println("A request from client1");
			out.flush();

			// Get an input stream from the socket
			InputStream is = s1.getInputStream();
			// Decorate it with a "data" input stream
			// DataInputStream dis = new DataInputStream(is);
			BufferedReader in = new BufferedReader(new InputStreamReader(is));
			// Read the input and print it to the screen
			while (true) {
				String str = in.readLine();
				if (str != null) {
					System.out.println(str);
				} else { // closeconnection
					break;
				}

			}

			// When done, just close the steam and connection
			out.close();
			in.close();
			s1.close();

		} catch (ConnectException connExc) {
			System.err.println("Could not connect.");

		} catch (IOException e) {
			// ignore
		} // END of try-catch

	} // END of main method

} // END of SimpleClient program

