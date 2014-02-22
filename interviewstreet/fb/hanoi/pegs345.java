import java.util.*;

public class pegs345 {
	public static ArrayList<Integer[]> otherStates(Integer[] towers, Integer nof_towers, Integer fromtoweri){
		ArrayList<Integer[]> states = new ArrayList<Integer[]>();
		ArrayList<Stack<Integer>> towers_disks = new ArrayList<Stack<Integer>>();
		int nof_disks = towers.length;
		
		for(int i=0; i<nof_towers; i++)
			towers_disks.add(new Stack<Integer>());
		
		for(int i=towers.length-1; i>=0; i--){
			towers_disks.get(towers[i]).push(i);
		}
		System.out.println("current state:"+Arrays.toString(towers));
		System.out.println("current matrix:"+towers_disks);
		
		//for(int k=0; k<nof_towers; k++){
			Stack<Integer> fromtower = towers_disks.get(fromtoweri);
			if (!fromtower.empty()){
				int top_fromtower = fromtower.pop();
				for(int j=0; j<nof_towers; j++){
					if(fromtoweri != j && (towers_disks.get(j).empty() || top_fromtower < towers_disks.get(j).peek()) ){
							towers_disks.get(j).push(top_fromtower);
							System.out.println(j+"=>"+towers_disks.toString());
							Integer[] state = new Integer[nof_disks];
							for(int i=0; i<nof_towers; i++){
								Stack<Integer> tower = towers_disks.get(i);
									Stack<Integer> cloneStack = (Stack<Integer>)tower.clone();
									while(!cloneStack.empty())
									state[cloneStack.pop()] = i;
							}
							System.out.println("     "+Arrays.toString(state));
							towers_disks.get(j).pop();
					}
				}
			//}
			
		}
		return states;
	}
	
	public static void main(String[] args) {
    /*Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int k = sc.nextInt();
        System.out.println("=> " + n+" "+k);
					
		int i;
		sc.nextLine();
		int[] init_disc_on_peg = new int[n];
		for(i=0;i<n;i++)
			init_disc_on_peg[i] = sc.nextInt();
		System.out.println("=> " + Arrays.toString(init_disc_on_peg));
		
		sc.nextLine();
		int[] final_disc_on_peg = new int[n];
		for(i=0;i<n;i++)
			final_disc_on_peg[i] = sc.nextInt();	
		System.out.println("=> " + Arrays.toString(final_disc_on_peg));		
		*/
		
		// k = 2 towers, n = 3 pegs
		int n = 3;
		Integer[] towers = {0,0}; 
		//Node root = new Node(towers);
		otherStates(towers,n,0);
		System.out.println("====");
		Integer[] towers1 = {1,0}; 
		//Node root = new Node(towers);
		otherStates(towers1,n,1);		
		
	}
}

class Node{
	Integer[] towers;
	ArrayList<Node> nodes;
	public Node(Integer[] towers) {
		this.towers = towers.clone();
		this.nodes = null;
	}
}

