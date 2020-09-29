package edu.ycp.cs201.lab7;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

// You won't need to modify this class.
public class TicTacToeFrame extends JFrame {
	private static final long serialVersionUID = 1L;

	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				TicTacToeFrame frame = new TicTacToeFrame();
				frame.add(new TicTacToePanel());
				frame.pack();
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.setTitle("TicTacToe game");
				frame.setVisible(true);
			}
		});
	}
}
