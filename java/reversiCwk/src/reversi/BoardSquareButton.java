package reversi;
import javax.swing.*;
import java.awt.*;

public class BoardSquareButton extends JButton {
    
    private int row;
    private int col;
    private IModel model;
    
    public BoardSquareButton(int row, int col, IModel model) {
        this.row = row;
        this.col = col;
        this.model = model;
        
        setBackground(Color.GREEN);
        setFocusPainted(false);
        setPreferredSize(new Dimension(40, 40));
    }
    
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);        
        
        int value = model.getBoardContents(row, col);
        
        if (value == 1 || value == 2) {
            int padding = 5;
            int diameter = Math.min(getWidth(), getHeight()) - 2 * padding;
            
            // Fill circle
            if (value == 1) {
                g2d.setColor(Color.WHITE);
            } else {
                g2d.setColor(Color.BLACK);
            }
            
            g2d.fillOval(padding, padding, diameter, diameter);
            
            if (value == 1) {
                g2d.setColor(Color.BLACK);
            } else {
                g2d.setColor(Color.WHITE);
            }
            
            g2d.setStroke(new BasicStroke(1)); 
            g2d.drawOval(padding, padding, diameter, diameter);
        }
    }
}