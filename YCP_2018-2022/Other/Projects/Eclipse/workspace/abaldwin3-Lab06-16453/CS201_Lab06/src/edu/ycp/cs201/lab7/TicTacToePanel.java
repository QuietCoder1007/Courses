package edu.ycp.cs201.lab7;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JPanel;

public class TicTacToePanel extends JPanel {
	private static final long serialVersionUID = 1L;

	private static final int WIDTH = 300;
	private static final int HEIGHT = 300;
	
	// TODO: add fields to store state
	int[][] Board = new int[3][3];
	
	// constructor
	public TicTacToePanel() {
		setPreferredSize(new Dimension(WIDTH, HEIGHT));
		setBackground(Color.BLACK);
		
		addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				handleMouseClick(e);
			}
		});
	}
	
	private void handleMouseClick(MouseEvent e) {
		int x = e.getX();
		int y = e.getY();
		if (e.getButton() == MouseEvent.BUTTON1) {
		    // left button
			Board[y/100][x/100] = 1;
		} else if (e.getButton() == MouseEvent.BUTTON3) {
		    // right button
			Board[y/100][x/100] = 2;
		}
		repaint();
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g); // paint background
		// TODO: draw the tic-tac-toe board
		g.setColor(Color.WHITE);
		g.fillRect(99, 0, 1, 300);
		g.fillRect(199, 0, 1, 300);
		g.fillRect(0, 99, 300, 1);
		g.fillRect(0, 199, 300, 1);
		for(int i = 0; i < Board.length; i++) {
			for(int j = 0; j < Board.length; j++) {
				int temp = 10;
				if(j == 1)
					temp = 110;
				if(j == 2)
					temp = 210;
				if(Board[i][j] == 1)
					g.setColor(Color.GREEN);
				if(Board[i][j] == 2)
					g.setColor(Color.BLUE);
				if(Board[i][j] == 1 && i == 0) { 
					g.fillRect(temp, 10, 79, 79);
				}if(Board[i][j] == 2 && i == 0) { 
					g.fillOval(temp, 10, 79, 79);
				}if(Board[i][j] == 1 && i == 1) { 
					g.fillRect(temp, 110, 79, 79);
				}if(Board[i][j] == 2 && i == 1) { 
					g.fillOval(temp, 110, 79, 79);
				}if(Board[i][j] == 1 && i == 2) {
					g.fillRect(temp, 210, 79, 79);
				}if(Board[i][j] == 2 && i == 2) {
					g.fillOval(temp, 210, 79, 79);
				}
			}
		}	
	}
	
}
