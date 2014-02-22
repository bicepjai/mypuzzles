import java.util.*;
import java.lang.*;
import java.math.*;
import java.util.regex.Pattern;

public class balances {

	public static ArrayList<Node> balances;
	
	static class Node	{
    boolean balanced;
    int wleft; //weights
    int wright;
    int addedleft; //added weights
    int addedright;
    int totalleft; //total weight of balances on the left side
    int totalright;
    List<Integer> leftIds;
    List<Integer> rightIds;

    public Node (int wl, List<Integer> ln, int wr, List<Integer> rn) {
      balanced = false;
      wleft = wl;
      wright = wr;
      addedleft = 0;
      addedright = 0;
      totalleft = 0;
      totalright = 0;
      leftIds = ln;
      rightIds = rn;
    }
 
    public boolean isBalanced() {
      return balanced;
    }
 
    public void setBalanced() {
      balanced = true;
    }
 
    public int getLeftW() {
      return wleft;
    }
 
    public int getRightW() {
      return wright;
    }
 
    public void setLeftW(int w) {
      totalleft += w;
    }
 
    public void setRightW(int w) {
      totalright += w;
    }
 
    public int getTotalLeft() {
      return totalleft + wleft; // both weights and balances on the left
    }
 
    public int getTotalRight() {
      return totalright + wright;
    }
 
    public int getAddedLeftW() {
      return addedleft;
    }
 
    public int getAddedRightW() {
      return addedright;
    }
 
    public void setAddedLeft(int w) {
      addedleft = w;
    }
 
    public void setAddedRight(int w) {
      addedright = w;
    }
 
    public int getTotalWeight() {
      return 10 + wleft + wright + totalleft + totalright + addedleft + addedright;
    }
 
    public List<Integer> getLefts() {
      return leftIds;
    }
 
    public List<Integer> getRights() {
      return rightIds;
    }
	}
	
	public static void main(String[] args) {
		balances = new ArrayList<Node>();
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		if(sc.hasNextLine()) sc.nextLine();
		int wl, wr;
		
		for (int i=0;i<(N*2);i+=2){
			List<Integer> leftIds = new ArrayList<Integer>();
			List<Integer> rightIds = new ArrayList<Integer>();
			
			int nodeId = i%2;
			Scanner sc1 = new Scanner(sc.nextLine());
			wl = sc1.nextInt();
			while(sc1.hasNextInt()){
				leftIds.add(sc1.nextInt());
			}
			//System.out.println(wl);				
			Scanner sc2 = new Scanner(sc.nextLine());
			wr = sc2.nextInt();
			while(sc2.hasNextInt()){
				rightIds.add(sc2.nextInt());
			}
			//System.out.println(wr);
			//System.out.println(leftIds);
			//System.out.println(rightIds);
			Node node = new Node(wl, leftIds, wr, rightIds)	;
			balances.add(node);
		}
		System.out.println(balances);
	}
}










