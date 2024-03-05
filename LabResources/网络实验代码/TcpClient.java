package edu.tongji.sc.network.socket;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;
public class TcpClient extends JFrame {
	// Attributes
	private User user;
	private Socket serviceSocket;
	private PrintWriter out;
	private BufferedReader in;
	private ObjectOutputStream os;
	private ObjectInputStream is;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		TcpClient client1 = new TcpClient("Jin");
		client1.pack();
		client1.setSize(400, 360);
		client1.setVisible(true);
		TcpClient client2 = new TcpClient("zhang");
		client2.pack();
		client2.setSize(400, 360);
		client2.setVisible(true);

	}
	public TcpClient(String userId) {
		user = new User(userId);
		this.initComponents();
		this.setTitle(user.getUserID());
		this.btnSend.setEnabled(false);
	}

	public TcpClient() {
		initComponents();
	}
	private void btnExitActionPerformed(ActionEvent e) {
		// TODO add your code here
		out.close();
		try {
			//close socke  t
			serviceSocket.close();
		} catch (IOException ioe) {
			System.out.println(ioe);
		}
		this.dispose();
		//System.exit(0);
	}

	private void btnSendActionPerformed(ActionEvent e) {
		// TODO add your code here
		//1锛屽彂閫佸璇�
		out.println(this.textMessage.getText());
		out.flush();
		try {
			// received chat
			//while (true) {
				String str = in.readLine();
				System.out.println("response:" + str);
				if (str != null) {
					this.textChat.setText(this.textChat.getText() + "\r\n"
							+ user.getUserID() + ":" + textMessage.getText());
				} 
				//Comet 
               // out.println("wait");
			//}

		} catch (IOException ioe) {

		}
		this.textMessage.setText("");

	}

	private void btnConnectActionPerformed(ActionEvent e) {
		// TODO add your code here
		try {
			//1.Open a Socket
			serviceSocket = new Socket(this.txtFieldIP.getText(), 5588);
			if (serviceSocket!=null){
			//2.韬唤璁よ瘉锛屼互瀵硅薄鏂瑰紡杩涜浜や簰
			//2.1transfer message to Server with socket
			os = new ObjectOutputStream(serviceSocket.getOutputStream());
			os.writeObject(user);
			os.flush();
			//2.2.Receive response from server 
			is = new ObjectInputStream(serviceSocket.getInputStream());
			System.out.println("Connection is  Success");
			user = (User) is.readObject();
			//3.寤虹珛杈撳叆杈撳嚭瀛楃娴侊紝
			//Charater Stream
			out = new PrintWriter(serviceSocket.getOutputStream());
			in = new BufferedReader(new InputStreamReader(serviceSocket
					.getInputStream()));
			this.btnSend.setEnabled(true);
			}else{
			    this.btnSend.setEnabled(false);	
			}
		} catch (UnknownHostException uh) {

		} catch (IOException ioe) {

		} catch (ClassNotFoundException ce) {

		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner Open Source Project license - unknown
		displayPanel = new JPanel();
		scrollPane2 = new JScrollPane();
		textChat = new JTextArea();
		buttonBar2 = new JPanel();
		txtFieldIP = new JTextField();
		btnConnect = new JButton();
		btnExit2 = new JButton();
		dialogPane = new JPanel();
		contentPanel = new JPanel();
		scrollPane1 = new JScrollPane();
		textMessage = new JTextArea();
		buttonBar = new JPanel();
		btnSend = new JButton();
		btnExit = new JButton();

		//======== this ========
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		//======== displayPanel ========
		{
			displayPanel.setLayout(new BorderLayout());

			//======== scrollPane2 ========
			{
				scrollPane2.setViewportView(textChat);
			}
			displayPanel.add(scrollPane2, BorderLayout.CENTER);

			//======== buttonBar2 ========
			{
				buttonBar2.setBorder(new EmptyBorder(12, 0, 0, 0));
				buttonBar2.setLayout(new GridBagLayout());
				((GridBagLayout)buttonBar2.getLayout()).columnWidths = new int[] {0, 85, 80};
				((GridBagLayout)buttonBar2.getLayout()).columnWeights = new double[] {1.0, 0.0, 0.0};

				//---- txtFieldIP ----
				txtFieldIP.setText("127.0.0.1");
				buttonBar2.add(txtFieldIP, new GridBagConstraints(0, 0, 1, 1, 0.0, 0.0,
					GridBagConstraints.CENTER, GridBagConstraints.BOTH,
					new Insets(0, 0, 0, 5), 0, 0));

				//---- btnConnect ----
				btnConnect.setText("\u8fde\u63a5");
				btnConnect.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						btnConnectActionPerformed(e);
					}
				});
				buttonBar2.add(btnConnect, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0,
					GridBagConstraints.CENTER, GridBagConstraints.BOTH,
					new Insets(0, 0, 0, 5), 0, 0));

				//---- btnExit2 ----
				btnExit2.setText("\u5173\u95ed");
				buttonBar2.add(btnExit2, new GridBagConstraints(2, 0, 1, 1, 0.0, 0.0,
					GridBagConstraints.CENTER, GridBagConstraints.BOTH,
					new Insets(0, 0, 0, 0), 0, 0));
			}
			displayPanel.add(buttonBar2, BorderLayout.SOUTH);
		}
		contentPane.add(displayPanel, BorderLayout.CENTER);

		//======== dialogPane ========
		{
			dialogPane.setBorder(new EmptyBorder(12, 12, 12, 12));
			dialogPane.setLayout(new BorderLayout());

			//======== contentPanel ========
			{
				contentPanel.setLayout(new GridBagLayout());
				((GridBagLayout)contentPanel.getLayout()).columnWidths = new int[] {0, 0, 309, 0};
				((GridBagLayout)contentPanel.getLayout()).rowHeights = new int[] {0, 0, 66, 0, 0};
				((GridBagLayout)contentPanel.getLayout()).columnWeights = new double[] {0.0, 0.0, 0.0, 1.0E-4};
				((GridBagLayout)contentPanel.getLayout()).rowWeights = new double[] {0.0, 0.0, 0.0, 0.0, 1.0E-4};

				//======== scrollPane1 ========
				{
					scrollPane1.setViewportView(textMessage);
				}
				contentPanel.add(scrollPane1, new GridBagConstraints(0, 0, 3, 3, 0.0, 0.0,
					GridBagConstraints.CENTER, GridBagConstraints.BOTH,
					new Insets(0, 0, 5, 0), 0, 0));
			}
			dialogPane.add(contentPanel, BorderLayout.CENTER);

			//======== buttonBar ========
			{
				buttonBar.setBorder(new EmptyBorder(12, 0, 0, 0));
				buttonBar.setLayout(new GridBagLayout());
				((GridBagLayout)buttonBar.getLayout()).columnWidths = new int[] {0, 85, 80};
				((GridBagLayout)buttonBar.getLayout()).columnWeights = new double[] {1.0, 0.0, 0.0};

				//---- btnSend ----
				btnSend.setText("\u53d1\u9001");
				btnSend.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						btnSendActionPerformed(e);
					}
				});
				buttonBar.add(btnSend, new GridBagConstraints(1, 0, 1, 1, 0.0, 0.0,
					GridBagConstraints.CENTER, GridBagConstraints.BOTH,
					new Insets(0, 0, 0, 5), 0, 0));

				//---- btnExit ----
				btnExit.setText("\u5173\u95ed");
				btnExit.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						btnExitActionPerformed(e);
					}
				});
				buttonBar.add(btnExit, new GridBagConstraints(2, 0, 1, 1, 0.0, 0.0,
					GridBagConstraints.CENTER, GridBagConstraints.BOTH,
					new Insets(0, 0, 0, 0), 0, 0));
			}
			dialogPane.add(buttonBar, BorderLayout.SOUTH);
		}
		contentPane.add(dialogPane, BorderLayout.SOUTH);
		pack();
		setLocationRelativeTo(getOwner());
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner Open Source Project license - unknown
	private JPanel displayPanel;
	private JScrollPane scrollPane2;
	private JTextArea textChat;
	private JPanel buttonBar2;
	private JTextField txtFieldIP;
	private JButton btnConnect;
	private JButton btnExit2;
	private JPanel dialogPane;
	private JPanel contentPanel;
	private JScrollPane scrollPane1;
	private JTextArea textMessage;
	private JPanel buttonBar;
	private JButton btnSend;
	private JButton btnExit;
	// JFormDesigner - End of variables declaration //GEN-END:variables
}
