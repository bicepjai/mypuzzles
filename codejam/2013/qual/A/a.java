import java.util.*;
import java.lang.*;
import java.math.*;

public class a {
	
	static int[][] board = new int[4][4]; 
	static char PLAYERX = 'X';
	static char PLAYERO = 'Y';
	static char PLAYERT = 'T';
	static char EMPTY = '.';
	static int ROWS = 4;
	static int COLS = 4;
	
	static void getInput() {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int xcount, ocount, tcount, ecount;
		char ch;
		for (int c=1;c<=N;c++){
			sc.nextLine();
			xcount = ocount = tcount = ecount = 0;
			for (int i=0;i<4;i++){
				String line = sc.nextLine();
				for (int j=0;j<4;j++){
					ch = line.charAt(j);
					if( ch == 'X') xcount++;
					else if ( ch == 'O') ocount++;
					else if ( ch == 'T') tcount++;
					else ecount++;
					board[i][j] = ch;
				}
			}
			if(hasWon(PLAYERX)){
				System.out.println("Case #"+c+": X Won");
			} else if(hasWon(PLAYERO)){
				System.out.println("Case #"+c+": O Won");
			} else if (xcount > ocount && ecount > 0){
				System.out.println("Case #"+c+": Game has not completed");
			} else {
				int [] res = minimax(4, 'X');
				System.out.println(res[0]);
				if(res[0] > 0){
					System.out.println("Case #"+c+": X Won");
				} else if (res[0] < 0){
					System.out.println("Case #"+c+": O Won");
				} else {
					System.out.println("Case #"+c+": Draw");
				}
			}
			
		}
	}

	private static int evaluate() {
		int score = 0;
		// Evaluate score for each of the 8 lines (3 rows, 3 columns, 2 diagonals)
		score += evaluateLine(0, 0, 0, 1, 0, 2, 0, 3);  // row 0
		score += evaluateLine(1, 0, 1, 1, 1, 2, 1, 3);  // row 1
		score += evaluateLine(2, 0, 2, 1, 2, 2, 2, 3);  // row 2
		score += evaluateLine(3, 0, 3, 1, 3, 2, 3, 3);  // row 3
		
		score += evaluateLine(0, 0, 1, 0, 2, 0, 3, 0);  // col 0
		score += evaluateLine(0, 1, 1, 1, 2, 1, 3, 1);  // col 1
		score += evaluateLine(0, 2, 1, 2, 2, 2, 3, 2);  // col 2
		score += evaluateLine(0, 3, 1, 3, 2, 3, 3, 3);  // col 2
		
		score += evaluateLine(0, 0, 1, 1, 2, 2, 3, 3);  // diagonal
		score += evaluateLine(0, 3, 1, 2, 2, 1, 3, 0);  // alternate diagonal
		return score;
	}
  
		/** The heuristic evaluation function for the given line of 3 cells
		@Return +100, +10, +1 for 3-, 2-, 1-in-a-line for computer.
		-100, -10, -1 for 3-, 2-, 1-in-a-line for opponent.
		0 otherwise */
	private static int evaluateLine(int row1, int col1, int row2, int col2, int row3, int col3, int row4, int col4) {
		int score = 0;
  
		// First cell
		if (board[row1][col1] == PLAYERX) {
			score = 1;
		} else if (board[row1][col1] == PLAYERO) {
			score = -1;
		}
  
		// Second cell
		if (board[row2][col2] == PLAYERX) {
			if (score == 1) {   // cell1 is PLAYERX
				score = 10;
			} else if (score == -1) {  // cell1 is PLAYERO
				return 0;
			} else {  // cell1 is empty
				score = 1;
			}
			} else if (board[row2][col2] == PLAYERO) {
			if (score == -1) { // cell1 is PLAYERO
				score = -10;
			} else if (score == 1) { // cell1 is PLAYERX
			return 0;
			} else {  // cell1 is empty
				score = -1;
			}
		}
  
		// Third cell
		if (board[row3][col3] == PLAYERX) {
			if (score > 0) {  // cell1 and/or cell2 is PLAYERX
				score *= 10;
			} else if (score < 0) {  // cell1 and/or cell2 is PLAYERO
				return 0;
			} else {  // cell1 and cell2 are empty
				score = 1;
			}
		} else if (board[row3][col3] == PLAYERO) {
			if (score < 0) {  // cell1 and/or cell2 is PLAYERO
				score *= 10;
			} else if (score > 1) {  // cell1 and/or cell2 is PLAYERX
				return 0;
			} else {  // cell1 and cell2 are empty
				score = -1;
			}
		}

		// Fourth cell
		if (board[row3][col3] == PLAYERX) {
			if (score > 10) {  // cell1 and/or cell2 and/or cell3 is PLAYERX
				score *= 10;
			} else if (score < 0) {  // cell1 and/or cell2 and/or cell3 is PLAYERO
				return 0;
			} else {  // cell1 and cell2 and cell3 are empty
				score = 1;
			}
		} else if (board[row3][col3] == PLAYERO) {
			if (score < 10) {  // cell1 and/or cell2 and/or cell3 is PLAYERO
				score *= 10;
			} else if (score > 1) {  // cell1 and/or cell2 and/or cell3 is PLAYERX
				return 0;
			} else {  // cell1 and cell2 and cell3 are empty
				score = -1;
			}
		}		
		
		return score;
	}

	private static long [] winningPatterns = {
		// rows
		0x1111000000000000L, 0x0000111100000000L, 0x0000000011110000L, 0x0000000000001111L,
		// cols
		0x1000100010001000L, 0x0100010001000100L, 0x0010001000100010L, 0x0001000100010001L,
		//diagnols
		0x0001001001001000L, 0x1000010000100001L
	};

	/** Returns true if thePlayer wins */
	private static boolean hasWon(char thePlayer) {
		long pattern = 0x0000000000000000;  // 16 4-bit pattern for the 16 cells
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				if (board[row][col] == thePlayer || board[row][col] == PLAYERT) {
					//System.out.println("===========>"+(row * COLS + col) * 4 + "=>"+Long.toHexString(pattern));
					pattern |= ((long)1 << ((row * COLS + col) * 4) ); // 4 caz of hex
				}
			}
		}
		for (long winningPattern : winningPatterns) {
			//System.out.println("===========>winning: "+Long.toHexString(winningPattern));
			if ((pattern & winningPattern) == winningPattern){
				//System.out.println("winning: "+Long.toHexString(pattern));
				return true;
			}
		}
		return false;
	}

	private static List<int[]> generateMoves() {
		List<int[]> nextMoves = new ArrayList<int[]>(); // allocate List

		// If gameover, i.e., no next move
		if (hasWon(PLAYERX) || hasWon(PLAYERO)) {
			return nextMoves;   // return empty list
		}

		// Search for empty cells and add to the List
		for (int row = 0; row < ROWS; row++) {
			for (int col = 0; col < COLS; col++) {
				if (board[row][col] == EMPTY) {
					nextMoves.add(new int[] {row, col});
				}
			}
		}
		return nextMoves;
	}
	
	private static int[] minimax(int depth, char player) {
		// Generate possible next moves in a List of int[2] of {row, col}.
		List<int[]> nextMoves = generateMoves();

		// mySeed is maximizing; while oppSeed is minimizing
		int bestScore = (player == PLAYERX ) ? Integer.MIN_VALUE : Integer.MAX_VALUE;
		int currentScore;
		int bestRow = -1;
		int bestCol = -1;
		//System.out.println(nextMoves);
		//System.out.println(bestScore);
		if (nextMoves.isEmpty() || depth == 0) {
			// Gameover or depth reached, evaluate score
			bestScore = evaluate();
		} else {
			for (int[] move : nextMoves) {
				// Try this move for the current "player"
				board[move[0]][move[1]] = player;
				if (player == PLAYERX) {  // PLAYERX is maximizing player
					currentScore = minimax(depth - 1, PLAYERO)[0];
					if (currentScore > bestScore) {
						bestScore = currentScore;
						bestRow = move[0];
						bestCol = move[1];
					}
				} else {  // PLAYERO is minimizing player
					currentScore = minimax(depth - 1, PLAYERX)[0];
					if (currentScore < bestScore) {
						bestScore = currentScore;
						bestRow = move[0];
						bestCol = move[1];
					}
				}
				// Undo move
				board[move[0]][move[1]] = EMPTY;
			}
		}
		return new int[] {bestScore, bestRow, bestCol};
	}
	
	public static void main(String[] args) {
		getInput();
		
	}
}