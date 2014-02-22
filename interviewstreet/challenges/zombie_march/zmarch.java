/*
https://www.interviewstreet.com/challenges/dashboard/#problem/4ff1484963063
*/
	import java.util.*;
	import java.lang.*;
	import java.math.*;
	import java.io.*;

	public class zmarch {
		
		public static void main(String[] args) {
			Scanner sc = new Scanner(System.in);
			int t = sc.nextInt();
			// t testcases
			while(t-- > 0){
				int N = sc.nextInt();
				int M = sc.nextInt();
				int k = sc.nextInt();
				
				Map<Integer,ArrayList<Integer>> graph = new HashMap<Integer,ArrayList<Integer>>();
				ArrayList<Integer> neighbours;
			 	double [] nof_zombies = new double[N];
				
				// getting athe graph filled up with node -> neighbour list format
				int m = M;
				while(m-- > 0){
					int a = sc.nextInt();
					int b = sc.nextInt();
					if(graph.containsKey(a)){
						neighbours = graph.get(a);
						neighbours.add(b);
						graph.put(a,neighbours);
					} else {
						neighbours = new ArrayList<Integer>();
						neighbours.add(b);
						graph.put(a,neighbours);
					}
					if(graph.containsKey(b)){
						neighbours = graph.get(b);
						neighbours.add(a);
						graph.put(b,neighbours);
					} else {
						neighbours = new ArrayList<Integer>();
						neighbours.add(a);
						graph.put(b,neighbours);
					}
				}
				// getting the number of zombies at each nodes
				int n = N;
				while(n > 0){
					nof_zombies[N-n] = (double)sc.nextInt();
					n--;
				}

				//System.out.println(N+" "+M+" "+k);
				//System.out.println(graph);
				//System.out.println(Arrays.toString(nof_zombies));
				PriorityQueue<Integer> pr = new PriorityQueue<Integer>(5);
				while(k-- > 0){
					double [] nof_zombies_stepped = new double[N];
					for (int  current_node : graph.keySet()) {
						neighbours = graph.get(current_node);
						for (int neighbour_node : neighbours){
							nof_zombies_stepped[current_node] += (double)nof_zombies[neighbour_node] / (double)graph.get(neighbour_node).size();
						}
						if(k==0){
							pr.add((int)Math.round(nof_zombies_stepped[current_node]));
							if(pr.size() > 5)
								pr.poll();
						}
					}
					System.arraycopy( nof_zombies_stepped, 0, nof_zombies, 0, N);
				}
				
				//System.out.println(pr);
				
				int [] zombies = new int[5];
				for(int i=0; i<5 ;i++)
					zombies[i] = pr.poll();
				for(int i=4; i>=0 ;i--)
					System.out.print(zombies[i]+" ");
				System.out.println();
				/*
				int [] zombies = new int[N];
				for(int i=0; i<N ;i++) {
					zombies[i] = (int)Math.round(nof_zombies[i]);
					//System.out.println(zombies[i]);
				}
				System.out.println(Arrays.toString(zombies));
				Arrays.sort(zombies);
				for(int i=N-1;i>N-6;i--)
					System.out.print(zombies[i]+" ");
				System.out.println();
				*/
			}
		}
	}