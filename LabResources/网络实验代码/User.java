package edu.tongji.sc.network.socket;
import java.io.Serializable;
public class User implements Serializable {
	private String userID;
	private String name;
	public User(){
	}
	public User(String user){
		this.userID=user;
	}
	public String getUserID() {
		return userID;
	}
	public void setUserID(String userID) {
		this.userID = userID;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
}
