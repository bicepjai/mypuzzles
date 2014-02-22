import java.util.*;
import java.lang.*;
import java.math.*;

public class kdiff {
		
	public static void quicksort(int[] numbers) {
		sort(numbers, 0, numbers.length - 1);
	}
	
	private static void sort(int[] numbers, int lo, int hi){
		if(lo >= hi) return;
		int m = partition(numbers, lo, hi);
		sort(numbers, lo, m-1);
		sort(numbers, m+1, hi);
	}
	
	private static int partition(int[] numbers, int lo, int hi){
		int v = numbers[lo];
		int i = lo, j=hi+1;
		while(true){
			//System.out.println(i+" "+j);
			while (numbers[++i] < v) if (i == hi) break;
			while (v < numbers[--j]) if (j == lo) break;
			if (i >= j) break;
			swap(numbers, i, j);
		}
		swap(numbers, lo, j);
		return j;
	}
	
	private static void swap(int[] numbers, int i, int j){
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int K = sc.nextInt();
		int i;
		sc.nextLine();
		int[] numbers = new int[N];
		for(i=0;i<N;i++)
			numbers[i] = sc.nextInt();
		
		System.out.println(Arrays.toString(numbers));
		quicksort(numbers);
		System.out.println(Arrays.toString(numbers));
		int diff = 0, track = 0;
		int solution = 0;
		int prev = numbers[0];
		for(i=1;i<N;i++){
			diff = Math.abs(numbers[i]-numbers[i-1]);
			if(diff == 0) track++;
			else {
				if(diff == K){
					solution ++;
					solution += track;
					track = 0;
				}
			}
		}
		System.out.println(solution);
	}
	
}