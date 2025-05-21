package reversi;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.HashMap;
import java.util.Map;

public class GUIView implements IView {

    IModel model;
    IController controller;
    JFrame whiteFrame;
    JFrame blackFrame;
    JLabel whitePlayerLabel;
    JLabel blackPlayerLabel;
    
    private final Map<Integer, BoardSquareButton[][]> playerBoards = new HashMap<>();

    @Override
    public void initialise(IModel model, IController controller) {
        this.model = model;
        this.controller = controller;

        System.out.println("Initialising GUI");
        
        whiteFrame = createPlayerFrame("White", 1);
        blackFrame = createPlayerFrame("Black", 2);
       
        
        refreshView();
    }
   

    public JFrame createPlayerFrame(String playerColour, int playerNumber) {
        JFrame frame = new JFrame();
        frame.setTitle("Reversi - " + playerColour + " player");
        frame.setSize(400, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel mainPanel = new JPanel(new BorderLayout());

        JLabel topLabel = new JLabel(playerColour + " player - Needs to be Implemented");
        mainPanel.add(topLabel, BorderLayout.NORTH);
        
        if (playerNumber == 1) {
            whitePlayerLabel = topLabel;
        } else if (playerNumber == 2) {
            blackPlayerLabel = topLabel;
        }

        JPanel gamePanel = createGamePanel(playerNumber);
        mainPanel.add(gamePanel, BorderLayout.CENTER);

        mainPanel.add(createSouthButtonsPanel(playerColour), BorderLayout.SOUTH);
         
        frame.add(mainPanel);
        frame.setVisible(true);

        return frame;
    }

    public JPanel createSouthButtonsPanel(String playerColour) {
        JPanel southButtonsPanel = new JPanel(new GridLayout(2, 1));
        southButtonsPanel.add(createAiButton(playerColour));
        southButtonsPanel.add(createRestartButton());
        return southButtonsPanel;
    }

    public JButton createRestartButton() {
        JButton restartButton = new JButton("Restart");
        restartButton.addActionListener(e -> {
        	controller.startup();
        	refreshView();
        });
        
        return restartButton;
    }

    public JButton createAiButton(String playerColour) {
        JButton useAiButton = new JButton("Greedy AI (play " + playerColour + ")");
        useAiButton.addActionListener(e -> {
            if (playerColour.equals("White")) {
                controller.doAutomatedMove(1);
            } else if (playerColour.equals("Black")) {
                controller.doAutomatedMove(2);
            } else {
                controller.doAutomatedMove(0);
            }
        });
        return useAiButton;
    }

    public JPanel createGamePanel(int playerNumber) {
        int width = model.getBoardWidth();
        int height = model.getBoardHeight();
        
        JPanel panel = new JPanel(new GridLayout(height, width));
        panel.setBackground(Color.GREEN);
        
        BoardSquareButton[][] boardButtons = new BoardSquareButton[height][width];
        playerBoards.put(playerNumber, boardButtons);

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int displayRow = playerNumber == 2 ? (height - 1) - row : row;
                int displayCol = playerNumber == 2 ? (width - 1) - col : col;

                BoardSquareButton button = new BoardSquareButton(displayCol, displayRow, model);
                
                button.setBackground(Color.GREEN);
                button.setActionCommand(displayCol + "," + displayRow);

                button.addActionListener(e -> {
                    String[] parts = e.getActionCommand().split(",");
                    int c = Integer.parseInt(parts[0]); // x coordinate (col)
                    int r = Integer.parseInt(parts[1]); // y coordinate (row)
                    controller.squareSelected(playerNumber, c, r);
                });

                boardButtons[displayRow][displayCol] = button;
                panel.add(button);
            }
        }

        return panel;
    }

    @Override
    public void refreshView() {
        // First validate the frames exist
        if (whiteFrame != null && blackFrame != null) {
            // Force repaint on both frames
            whiteFrame.repaint();
            blackFrame.repaint();
            
            // Explicitly repaint each button
            for (BoardSquareButton[][] board : playerBoards.values()) {
                int height = model.getBoardHeight();
                int width = model.getBoardWidth();
                
                for (int row = 0; row < height; row++) {
                    for (int col = 0; col < width; col++) {
                        if (board[row][col] != null) {
                            board[row][col].repaint();
                        }
                    }
                }
            }
        }
    }

    @Override
    public void feedbackToUser(int player, String message) {
        if (player == 1) {
            this.whitePlayerLabel.setText(message);
        } else if (player == 2) {
            this.blackPlayerLabel.setText(message);
        } else {
            System.out.println(player + " - " + message);
        }
    }
}