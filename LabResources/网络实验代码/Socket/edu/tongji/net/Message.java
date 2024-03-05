package edu.tongji.net;

import java.io.Serializable;

public class Message implements Serializable {
	private String user;
	private String word;
	public Message(){
		
	}
	public String getUser() {
		return user;
	}
	public void setUser(String user) {
		this.user = user;
	}
	public String getWord() {
		return word;
	}
	public void setWord(String word) {
		this.word = word;
	}

}
