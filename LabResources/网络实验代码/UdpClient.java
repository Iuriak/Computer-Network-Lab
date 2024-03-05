package edu.tongji.networklab.udp;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.border.EmptyBorder;
public class UdpClient extends JFrame {
	private DatagramSocket client;
	private DatagramPacket request, response;
	private byte[] bufferSended;
	private byte[] bufferReceived;
	private InetAddress server;
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		UdpClient client = new UdpClient();
		client.pack();
		client.setSize(400, 370);
		client.setVisible(true);

	}
	public UdpClient(){
		initComponents();
		this.btnSend.setEnabled(false);		
	}
	private void btnSendActionPerformed(ActionEvent e) {
		// TODO add your code here
		try {
			// TODO add your code here
			// System.out.println(this.textMessage.getText());
			bufferSended = this.textMessage.getText().getBytes();
			client = new DatagramSocket();// client
			request = new DatagramPacket(bufferSended, bufferSended.length,
					server, 5555);
			// send
			client.send(request);   
			this.textMessage.setText("");
			// receive
			client.receive(response);
			this.textChat.setText(this.textChat.getText() + "\r\n"
					+ new String(response.getData()).trim());
		} catch (SocketException se) {
			System.out.println("Socket Exception:"+se);

		} catch (IOException ioe) {
			System.out.println("IOE Error:"+ioe);

		}
	}

	private void btnExitActionPerformed(ActionEvent e) {
		// TODO add your code here
		client.close();
		System.exit(0);
	}

	private void btnConnectActionPerformed(ActionEvent e) {
		// TODO add your code here
		String serverIP = "";
		try {
			serverIP = this.textFieldIP.getText();
			server = InetAddress.getByName(serverIP);
			System.out.println("Server:" + server.getHostAddress());
			// if (server == null) {
			// } else {
			byte[] bufferReceived = new byte[101];
			response = new DatagramPacket(bufferReceived, bufferReceived.length);
			this.btnSend.setEnabled(true);
			// }
		} catch (UnknownHostException ue) {
			System.out.println(ue);
			System.out.println("Error IP Address:" + serverIP);
			this.textFieldIP.setText("");
		}

	}
	
	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner Open Source Project license - unknown
		dialogPane2 = new JPanel();
		contentPanel2 = new JPanel();
		scrollPane2 = new JScrollPane();
		textChat = new JTextArea();
		buttonBar2 = new JPanel();
		textFieldIP = new JTextField();
		btnConnect = new JButton();
		btnExit2 = new JButton();
		dialogPane = new JPanel();
		contentPanel = new JPanel();
		scrollPane1 = new JScrollPane();
		textMessage = new JTextArea();
		buttonBar = new JPanel();
		btnSend = new JButton();
		btnExit = new JButton();

		// ======== this ========
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout());

		// ======== dialogPane2 ========
		{
			dialogPane2.setBorder(new EmptyBorder(12, 12, 12, 12));
			dialogPane2.setLayout(new BorderLayout());

			// ======== contentPanel2 ========
			{
				contentPanel2.setLayout(new GridBagLayout());
				((GridBagLayout) contentPanel2.getLayout()).columnWidths = new int[] {0, 0 };
				((GridBagLayout) contentPanel2.getLayout()).rowHeights = new int[] {65, 0, 0 };
				((GridBagLayout) contentPanel2.getLayout()).columnWeights = new double[] {1.0, 1.0E-4 };
				((GridBagLayout) contentPanel2.getLayout()).rowWeights = new double[] {0.0, 1.0, 1.0E-4 };
				// ======== scrollPane2 ========
				{
					scrollPane2.setViewportView(textChat);
				}
				contentPanel2.add(scrollPane2, new GridBagConstraints(0, 0, 1,1, 0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

				// ======== buttonBar2 ========
				{
					buttonBar2.setBorder(new EmptyBorder(12, 0, 0, 0));
					buttonBar2.setLayout(new GridBagLayout());
					((GridBagLayout) buttonBar2.getLayout()).columnWidths = new int[] {0, 85, 80 };
					((GridBagLayout) buttonBar2.getLayout()).columnWeights = new double[] {1.0, 0.0, 0.0 };

					// ---- textFieldIP ----
					textFieldIP.setText("127.0.0.1");
					buttonBar2.add(textFieldIP, new GridBagConstraints(0, 0, 1,1, 0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 5), 0,0));
					// ---- btnConnect ----
					btnConnect.setText("\u8fde\u63a5");
					btnConnect.addActionListener(new ActionListener() {
						public void actionPerformed(ActionEvent e) {
							btnConnectActionPerformed(e);
						}
					});
					buttonBar2.add(btnConnect, new GridBagConstraints(1, 0, 1,1, 0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 5), 0,0));

					// ---- btnExit2 ----
					btnExit2.setText("\u5173\u95ed");
					buttonBar2.add(btnExit2, new GridBagConstraints(2, 0, 1, 1,0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0,0));
				}
				contentPanel2.add(buttonBar2, new GridBagConstraints(0, 1, 1,1, 0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
			dialogPane2.add(contentPanel2, BorderLayout.CENTER);
		}
		contentPane.add(dialogPane2, BorderLayout.NORTH);

		// ======== dialogPane ========
		{
			dialogPane.setBorder(new EmptyBorder(12, 12, 12, 12));
			dialogPane.setLayout(new BorderLayout());

			// ======== contentPanel ========
			{
				contentPanel.setLayout(new GridBagLayout());
				((GridBagLayout) contentPanel.getLayout()).columnWidths = new int[] {0, 0 };
				((GridBagLayout) contentPanel.getLayout()).rowHeights = new int[] {65, 0, 0 };
				((GridBagLayout) contentPanel.getLayout()).columnWeights = new double[] {1.0, 1.0E-4 };
				((GridBagLayout) contentPanel.getLayout()).rowWeights = new double[] {0.0, 1.0, 1.0E-4 };

				// ======== scrollPane1 ========
				{
					scrollPane1.setViewportView(textMessage);
				}
				contentPanel.add(scrollPane1, new GridBagConstraints(0, 0, 1,1, 0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));

				// ======== buttonBar ========
				{
					buttonBar.setBorder(new EmptyBorder(12, 0, 0, 0));
					buttonBar.setLayout(new GridBagLayout());
					((GridBagLayout) buttonBar.getLayout()).columnWidths = new int[] {0, 85, 80 };
					((GridBagLayout) buttonBar.getLayout()).columnWeights = new double[] {1.0, 0.0, 0.0 };

					// ---- btnSend ----
					btnSend.setText("\u53d1\u9001");
					btnSend.addActionListener(new ActionListener() {
						public void actionPerformed(ActionEvent e) {
							btnSendActionPerformed(e);
						}
					});
					buttonBar.add(btnSend, new GridBagConstraints(1, 0, 1, 1,0.0, 0.0, GridBagConstraints.CENTER,
							GridBagConstraints.BOTH, new Insets(0, 0, 0, 5), 0,0));

					// ---- btnExit ----
					btnExit.setText("\u5173\u95ed");
					btnExit.addActionListener(new ActionListener() {
						public void actionPerformed(ActionEvent e) {
							btnExitActionPerformed(e);
						}
					});
					buttonBar.add(btnExit, new GridBagConstraints(2, 0, 1, 1,0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0,0));
				}
				contentPanel.add(buttonBar, new GridBagConstraints(0, 1, 1, 1,0.0, 0.0, GridBagConstraints.CENTER,GridBagConstraints.BOTH, new Insets(0, 0, 0, 0), 0, 0));
			}
			dialogPane.add(contentPanel, BorderLayout.CENTER);
		}
		contentPane.add(dialogPane, BorderLayout.SOUTH);
		pack();
		setLocationRelativeTo(getOwner());
		// JFormDesigner - End of component initialization
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner Open Source Project license - unknown
	private JPanel dialogPane2;
	private JPanel contentPanel2;
	private JScrollPane scrollPane2;
	private JTextArea textChat;
	private JPanel buttonBar2;
	private JTextField textFieldIP;
	private JButton btnConnect;
	private JButton btnExit2;
	private JPanel dialogPane;
	private JPanel contentPanel;
	private JScrollPane scrollPane1;
	private JTextArea textMessage;
	private JPanel buttonBar;
	private JButton btnSend;
	private JButton btnExit;
	// JFormDesigner - End of variables declaration //GEN-END:variables}
}

