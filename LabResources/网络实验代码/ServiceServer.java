package edu.tongji.sc.network.socket;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Collection;
import java.util.Iterator;

public class ServiceServer implements Runnable {
	private static Collection userList;
	private User user;
	private Socket client;
	private ObjectInputStream is;
	private ObjectOutputStream os;
	PrintWriter out;
	public ServiceServer(Socket c)throws IOException{
		this.client=c;
		is=new ObjectInputStream(client.getInputStream());
		os=new ObjectOutputStream(client.getOutputStream());
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try{
		Object obj=is.readObject();
		if (obj instanceof User){
			user=(User)obj;
			System.out.println("--User:"+user.getUserID());
			os.writeObject(obj);
		}
		BufferedReader in = new BufferedReader(new InputStreamReader(client
				.getInputStream()));
		out = new PrintWriter(client.getOutputStream());
		System.out.println(user.getUserID()+": start Service----");
		while (true) {
			//received chat
			String str = in.readLine();
			if (str != null) {
				//if (!str.equals("wait")){
				System.out.println(str);
				this.Response(str);
				//}
				//out.println("has receive:"+str);
				//out.flush();
			} else {
				//close connection
				break;
			}
		}
		in.close();
		out.close();
		client.close();
		System.out.println(user.getUserID()+": end service--");
		}catch(IOException ioe){
			System.out.println(ioe);
		}catch(ClassNotFoundException ce){
			System.out.println(ce);
		
		}

	}
	private  synchronized void sendResponse(String message){
		System.out.println(user.getUserID()+":"+message);
		out.println("has receive:"+message);
		out.flush();
		
	}
	private static void Response(String message){
		Iterator it=userList.iterator();
		while(it.hasNext()){
			ServiceServer aServer=(ServiceServer)it.next();
			aServer.sendResponse(message);
		}
	}
	public static void setUserList(Collection userList) {
		ServiceServer.userList = userList;
	}


}
