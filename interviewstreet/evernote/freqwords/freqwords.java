import java.util.*;
import java.lang.*;
import java.math.*;

public class freqwords {
		
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		sc.nextLine();
		int i;
		String[] words = new String[N];
		
		Map<String, Integer> hm = new TreeMap<String, Integer>();
		CustomCompare comp = new CustomCompare(hm);
		TreeMap<String, Integer> stm = new TreeMap<String, Integer>(comp);
		
		for(i=0;i<N;i++){
			String word = sc.nextLine();
			
			if(hm.containsKey(word)){
				int value = hm.get(word);
				value++;
				hm.put(word, value); 
			} else {
				hm.put(word, 0); 
			}
		}
		int k = sc.nextInt();
		
		stm.putAll(hm);
		//System.out.println(hm.toString());
		//System.out.println(stm.toString());
		int j = k;
		//iterating over keys only
		for (String key : stm.keySet()) {
		    System.out.println(key);
				if(--j == 0) break;
		}
		
	}
	
}

class CustomCompare implements Comparator<Object> {

    Map theMapToSort;

    public CustomCompare(Map theMapToSort) {
        this.theMapToSort = theMapToSort;
    }

    public int compare(Object key1, Object key2) {
        Integer val1 = (Integer) theMapToSort.get(key1);
        Integer val2 = (Integer) theMapToSort.get(key2);
        if (val1 > val2) {
            return -1;
        } else {
            return 1;
        }
    }
}