
import java.util.ArrayDeque;
import java.util.Queue;
import java.util.*;
import java.lang.*;
import java.math.*;


/**
 * Radix sort: a non-comparative integer sorting algorithm.
 * Family: Bucket.
 * Space: 10 Buckets with at most n integers per bucket.
 * Stable: True.
 * 
 * Average case = O(n*k)
 * Worst case = O(n*k)
 * Best case = O(n*k)
 * NOTE: n is the number of digits and k is the average bucket size
 * 
 * @author Justin Wetherell <phishman3579@gmail.com>
 */
public class RadixSort {
    
    private static final int numberOfBuckets = 10;
    
    @SuppressWarnings("unchecked")
    private static final Queue<Integer>[] buckets = new ArrayDeque[numberOfBuckets];
    static {
        // 10 for base 10 numbers
        for (int i=0; i<numberOfBuckets; i++) {
            buckets[i] = new ArrayDeque<Integer>();
        }    
    }
    
    private static int[] unsorted = null;

    private RadixSort() { }

    public static int[] sort(int[] unsorted) {
        RadixSort.unsorted = unsorted;

        int numberOfDigits = getMaxNumberOfDigits(); //Max number of digits
        int divisor = 1;
        int digit = 0;
        for (int n=0; n<numberOfDigits; n++) {
            for (int d : RadixSort.unsorted) {
                digit = getDigit(d,divisor);
                buckets[digit].add(d);
            }
            int index = 0;
            for (Queue<Integer> bucket : buckets) {
                while (!bucket.isEmpty()) {
                    int integer = bucket.remove();
                    RadixSort.unsorted[index++] = integer;
                }
            }
            divisor *= 10;
        }

        try {
            return RadixSort.unsorted;
        } finally {
            //Make sure they are actually clear. Although, they should be.
            for (int i=0; i<numberOfBuckets; i++) {
                buckets[i].clear();
            }  
            RadixSort.unsorted = null;
        }
    }

    private static int getMaxNumberOfDigits() {
        int max = Integer.MIN_VALUE;
        int temp = 0;
        for (int i : RadixSort.unsorted) {
            temp = (int)Math.log10(i)+1;
            if (temp>max) max=temp;
        }
        return max;
    }
    
    private static int getDigit(int integer, int divisor) {
        return (integer / divisor) % 10;
    }		

		public static void main(String[] args) {
			Scanner sc = new Scanner(System.in);
			int N = sc.nextInt();
			int i;
			int[] numbers = new int[N];
			for(i=0;i<N;i++){
				sc.nextLine();
				numbers[i] = sc.nextInt();
			}

			System.out.println(Arrays.toString(numbers));
			numbers = sort(numbers);
			//System.out.println(Arrays.toString(numbers));
			int n = N;
			while(n > N-4 && N-4 > 0){
				System.out.println(numbers[--n]+" "+n);
			}
		}
}