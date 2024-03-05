package edu.tongji.sc.network.socket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class SimpleService implements Runnable {
	private Socket clientSocket;

	public SimpleService(Socket serviceSocket) {
		this.clientSocket = serviceSocket;
	}

	@Override
	public void run() {
		try {
			// TODO Auto-generated method stub
			System.out.println("---start Service----");
			BufferedReader in = new BufferedReader(new InputStreamReader(
					clientSocket.getInputStream()));
			// Get output stream associated with the socket
			OutputStream out = clientSocket.getOutputStream();
			PrintWriter bw = new PrintWriter(out);
			while (true) {
				String str = in.readLine();
				if (str != null) {

					System.out.println("Request:" + str);
					bw.println("Received");
bw.flush();
					// out.println("has receive....");
					// out.flush();
				} else { // closeconnection
					break;
				}
			}
			in.close();
			bw.close();
			out.close();
			clientSocket.close();

			// Close the connection, but not the server socket
			System.out.println("--end service--");
		} catch (IOException e) {
			System.out.println(e.getMessage());

		}
	}

}
