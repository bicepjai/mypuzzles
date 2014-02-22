import java.util.Arrays;

public class mergesort {
	public static int[] merge (int[] a1, int[] a2){
		int i=0, k=0, j=0;
		int[] b = new int[a1.length + a2.length];
		
		while (i<a1.length && j<a2.length) {
			System.out.println("i="+i+" j="+j);
			if (a1[i] < a2[j])
				b[k++] = a1[i++];
			else
				b[k++] = a2[j++];
		}
		while (i< a1.length) b[k++] = a1[i++];
		while (j< a2.length) b[k++] = a2[j++];
		return b;
	}
	
	public static void main (String[] args){
		int[] a1 = {4,7,14};
		int[] a2 = {1,3,9,17};
		System.out.println("a1="+Arrays.toString(a1)+" a2="+Arrays.toString(a2)+" merged"+Arrays.toString(merge(a1,a2)));
	}
}