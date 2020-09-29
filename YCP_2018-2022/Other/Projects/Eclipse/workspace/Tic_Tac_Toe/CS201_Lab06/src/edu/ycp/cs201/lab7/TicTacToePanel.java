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
		
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g); // paint background
		
		// TODO: draw the tic-tac-toe board
	}
}
