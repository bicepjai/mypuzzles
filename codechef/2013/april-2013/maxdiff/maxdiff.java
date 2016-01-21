import java.util.*;
import java.lang.*;
import java.math.*;

public class maxdiff
{
	private static int[] aux; // auxiliary array for merges
	public static void sort(int[] a)	{
		aux = new int[a.length]; // Allocate space just once.
		sort(a, 0, a.length - 1);
	}
	
	public static void merge(int[] a, int lo, int mid, int hi)
	{ 
		// Merge a[lo..mid] with a[mid+1..hi].
		int i = lo, j = mid+1;
		for (int k = lo; k <= hi; k++) // Copy a[lo..hi] to aux[lo..hi].
			aux[k] = a[k];
		for (int k = lo; k <= hi; k++) // Merge back to a[lo..hi].
			if (i > mid) a[k] = aux[j++];
			else if (j > hi ) a[k] = aux[i++];
			else if (aux[j] < aux[i]) a[k] = aux[j++];
			else a[k] = aux[i++];
	}

	private static void sort(int[] a, int lo, int hi)
	{ // Sort a[lo..hi].
	if (hi <= lo) return;
		int mid = lo + (hi - lo)/2;
		sort(a, lo, mid); // Sort left half.
		sort(a, mid+1, hi); // Sort right half.
		merge(a, lo, mid, hi); // Merge results (code on page 271).
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int i;
		int T = sc.nextInt();
		for (int c=1;c<=T;c++){
			int N = sc.nextInt();
			int K = sc.nextInt();
			int[] W = new int[N];
			for (i=0;i<N;i++) W[i] =  sc.nextInt();
			sort(W);
			//System.out.println(Arrays.toString(W));
			int dad1 = 0, son1 = 0;
			int dad2 = 0, son2 = 0;
			
			for(i=0;i<K;i++) son1 += W[i];
			for(;i<N;i++) dad1 += W[i];

			for(i=N-1;i>K;i--) son2 += W[i];
			for(;i>=0;i--) dad2 += W[i];
			//System.out.println("dad1: "+dad1+" son1: "+son1+" dad1-son1: "+(dad1-son1));
			//System.out.println("dad2: "+dad2+" son2: "+son2+" dad2-son2: "+(dad2-son2));
			
			if(Math.abs(dad1-son1) > Math.abs(dad2-son1))
				System.out.println(Math.abs(dad1-son1));
			else
				System.out.println(Math.abs(dad2-son2));			
		}
	}
}