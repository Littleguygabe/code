package reversi;

import java.awt.Point;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.ArrayList;

public class ReversiController implements IController {

	IModel model;
	IView view;
	
	private Map<Integer,ArrayList<Point>> validMoves = new HashMap<>();

	
	@Override
	public void initialise(IModel model, IView view) {
		this.model = model;
		this.view = view;
		
		
	}

	@Override
	public void startup() {
//		need to place the initial pieces on the board
		this.model.clear(0);
		this.model.setPlayer(1);
		this.model.setFinished(false);
				
		int height = this.model.getBoardHeight();
		int width = this.model.getBoardWidth();
		
		int startHeight = (height/2)-1;
		int startWidth = (width/2)-1;
		
//		initialise the valid moves hashmap
		ArrayList<Point> initialisationHash = new ArrayList<>();
		
		validMoves.put(1, initialisationHash);
		validMoves.put(2, initialisationHash);
		
		
		
		this.model.setBoardContents(startWidth, startHeight, 1);
		this.model.setBoardContents(startWidth+1, startHeight+1, 1);
		
		this.model.setBoardContents(startWidth+1, startHeight, 2);
		this.model.setBoardContents(startWidth, startHeight+1, 2);
		
//		this.model.setBoardContents(0, 0, 1);
//		this.model.setBoardContents(0, 1, 2);
//		this.model.setBoardContents(0, 2, 2);
//		this.model.setBoardContents(0, 3, 2);
//		this.model.setBoardContents(0, 4, 2);
//		this.model.setBoardContents(0, 5, 2);
//		
		
		updateValidMovesCache();
		updateTurnFeedbackMessages();

		this.view.refreshView();
		
	}

	public void updateTurnFeedbackMessages() {
		if (this.model.getPlayer()==1) {
			this.view.feedbackToUser(1, "White Player - choose where to put your piece");
			this.view.feedbackToUser(2, "Black Player - not your turn");
		}
		else {
			this.view.feedbackToUser(2, "Black Player - choose where to put your piece");
			this.view.feedbackToUser(1, "White Player - not your turn");
			
		}
	}
	
	public ArrayList<Point> getValidPoints(){
		ArrayList<Point> validPoints = new ArrayList<>();
		
		int[][] directions = {
			    {-1, -1}, 
			    {-1,  0}, 
			    {-1,  1}, 
			    { 0, -1}, 
			    { 0,  1}, 
			    { 1, -1}, 
			    { 1,  0}, 
			    { 1,  1}  
			};
		
		int player = this.model.getPlayer();
		
		
		int opponent = (player == 1) ? 2 : 1;
	    int width = model.getBoardWidth();
	    int height = model.getBoardHeight();
		
		
	    for (int x = 0; x < width; x++) {
	        for (int y = 0; y < height; y++) {
	            if (model.getBoardContents(x, y) != 0) continue; // not empty

	            for (int[] dir : directions) {
	                int dx = dir[0], dy = dir[1];
	                int nx = x + dx, ny = y + dy;
	                boolean hasOpponentBetween = false;

	                while (nx >= 0 && nx < width && ny >= 0 && ny < height) {
	                    int val = model.getBoardContents(nx, ny);
	                    if (val == opponent) {
	                        hasOpponentBetween = true;
	                    } else if (val == player) {
	                        if (hasOpponentBetween) {
	                            validPoints.add(new Point(x, y));
	                        }
	                        break;
	                    } else {
	                        break;
	                    }
	                    nx += dx;
	                    ny += dy;
	                }
	            }
	        }
	    }

	    return validPoints;
	}
	
	
	
	public void updateValidMovesCache() {
//		first need to get all the possible valid moves for each colour
//		[ ] function to get the valid position for a colour
//			-> pass in the colour we want the valid positions for
		ArrayList<Point> validPlayerPoints = getValidPoints();
		validMoves.put(this.model.getPlayer(),validPlayerPoints);
//		System.out.println("The current Valid Positions are: "+validMoves);
		
	}
	
	public boolean checkPlayerHasValidMoves() {
		ArrayList<Point> moves = validMoves.get(this.model.getPlayer());
//		System.out.println(this.model.getPlayer() + " " + moves);
		return moves != null && !moves.isEmpty();
	}

	public void moveModelToNextTurn() {
		this.model.setPlayer(3 - this.model.getPlayer());
	
		update();
	}
	
	public void finishGame() {
//		System.out.println("Game finished");
		
//		create logic to check the who won
		Map<Integer,Integer> scoreCount = new HashMap<>();
		scoreCount.put(1, 0);
		scoreCount.put(2, 0);
		
		for (int x=0;x<this.model.getBoardWidth();x++) {
			for (int y=0;y<this.model.getBoardHeight();y++) {
				if (this.model.getBoardContents(x, y)!=0) {					
					scoreCount.put(this.model.getBoardContents(x, y), scoreCount.get(this.model.getBoardContents(x, y))+1);
				}
			}
		}
		
//		System.out.println(scoreCount);
		if (scoreCount.get(1)>scoreCount.get(2)) {
//			player 1 won
			this.view.feedbackToUser(1, "White won. White "+scoreCount.get(1)+" to Black "+scoreCount.get(2)+". Reset the game to replay.");
			this.view.feedbackToUser(2, "White won. White "+scoreCount.get(1)+" to Black "+scoreCount.get(2)+". Reset the game to replay.");		
		}
		else if (scoreCount.get(1)<scoreCount.get(2)) {
//			player 2 won
			this.view.feedbackToUser(1, "Black won. Black "+scoreCount.get(2)+" to White "+scoreCount.get(1)+". Reset the game to replay.");
			this.view.feedbackToUser(2, "Black won. Black "+scoreCount.get(2)+" to White "+scoreCount.get(1)+". Reset the game to replay.");
			
		}
		
		else {
//			draw


			this.view.feedbackToUser(1, "Draw. Both players ended with "+scoreCount.get(1)+" pieces. Reset the game to replay.");
			this.view.feedbackToUser(2, "Draw. Both players ended with "+scoreCount.get(1)+" pieces. Reset the game to replay.");
		}
		this.view.refreshView();
	}
	
	public Boolean bothPlayersHaveNoValidMoves() {
		updateValidMovesCache();
		
		this.model.setPlayer(3-this.model.getPlayer());
		updateValidMovesCache();
		
		this.model.setPlayer(3-this.model.getPlayer());
		
		
		if (this.validMoves.get(1).isEmpty() && this.validMoves.get(2).isEmpty()) {
			return true;
		}
	
		return false;
			
	}
	
	@Override
	public void update() {
		// TODO Auto-generated method stub
//		call the code that updates the valid moves cache in here, then this is called everytime a move is made
//		or it changes whose turn it is
		updateValidMovesCache();
//		check that the current player has a valid move somewhere
		if (!checkPlayerHasValidMoves()) {
//			skip player cause no moves available
			
			if (bothPlayersHaveNoValidMoves()) {
				this.model.setFinished(true);
				finishGame();
			}
			else {
//				System.out.println("player "+this.model.getPlayer()+" has no valid moves, moving onto the next player");
				this.model.setFinished(false);
				this.view.feedbackToUser(this.model.getPlayer(), "You do not Currently have any Valid Moves to play");
				this.model.setPlayer(3 - this.model.getPlayer());
				
				this.view.refreshView();
			}
//			need to have a check to see if both players are invalid
			
		}
		
		else {			
			updateTurnFeedbackMessages();
		}
			
		view.refreshView();
	}

	public ArrayList<Point> getPiecesToBeFlipped(int x, int y) {
		int player = this.model.getPlayer();
		ArrayList<Point> positionsToBeFlipped = new ArrayList<>();
		
		int[][] directions = {
			    {-1, -1}, 
			    {-1,  0}, 
			    {-1,  1}, 
			    { 0, -1}, 
			    { 0,  1}, 
			    { 1, -1}, 
			    { 1,  0}, 
			    { 1,  1}  
			};
		
		int opponent = (player == 1) ? 2 : 1;
	    int width = model.getBoardWidth();
	    int height = model.getBoardHeight();
		
	    for (int[] dir : directions) {
            int dx = dir[0], dy = dir[1];
            int nx = x + dx, ny = y + dy;
            
            ArrayList<Point> lineCache = new ArrayList<>();
            
            while (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                int val = model.getBoardContents(nx, ny);
                if (val == opponent) {
                	if (!positionsToBeFlipped.contains(new Point(nx,ny))) {
                		lineCache.add(new Point(nx,ny));
                	}
                } else if (val == player) {
                	positionsToBeFlipped.addAll(lineCache);
                    break;
                } else {
                    break;
                }
                nx += dx;
                ny += dy;
            }
        }
		
		return positionsToBeFlipped;
	}

	public void flipPieces(ArrayList<Point> points) {
		for (Point p : points) {
			int curVal = this.model.getBoardContents(p.x, p.y);
			this.model.setBoardContents(p.x, p.y, 3-curVal);
		}
	}
	
	@Override
	public void squareSelected(int player, int x, int y) {
		if (player!=this.model.getPlayer()) {
			view.feedbackToUser(player, "It is not your turn!");
			return;
		}
		
		Point tempPoint = new Point(x,y);
		ArrayList<Point> curPlayerValidPoints = validMoves.get(player);
		
		if (curPlayerValidPoints.contains(tempPoint)) {
			this.model.setBoardContents(x, y, player);
//			1. add function to return all the pieces that need to be flipped
			ArrayList<Point> piecesToBeFlipped = getPiecesToBeFlipped(x,y);
			
//			2. add function that takes the array of pieces and flips them
			flipPieces(piecesToBeFlipped);
			
			
			moveModelToNextTurn();
		}
		
		else {
			view.feedbackToUser(player, "Invalid location to play a piece");
		}
		
	}

	@Override
	public void doAutomatedMove(int player) {
//		take all the cached valid moves, iterate over each one to find which one has the highest number of 
//		captures, then play that once finished
		
		if (this.model.getPlayer()!=player) {
			this.view.feedbackToUser(player, "It is not your turn!");
			return;
		}
		
		ArrayList <Point> potentialMoves = validMoves.get(player);
		
		Point optimalPoint = new Point();
		int curCaptureMax = 0;
		
		for (Point move : potentialMoves) {
			int numCaptures = getPiecesToBeFlipped(move.x,move.y).size();
			if (numCaptures>curCaptureMax) {
				curCaptureMax = numCaptures;
				optimalPoint = move;
			}
		}
		
//		System.out.println("Optimal Move @ "+optimalPoint);
		squareSelected(player,optimalPoint.x,optimalPoint.y);
		
		// TODO Auto-generated method stub
		
	}

}
