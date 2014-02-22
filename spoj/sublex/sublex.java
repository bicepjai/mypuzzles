import java.util.*;

public class sublex {
    private final String[] suffixes;
    private final int N;
		private int[] sa,lcp,nofsubs,nofusubs,nofusubs_acc;
		
    public sublex(String s) {
        N = s.length();
        suffixes = new String[N];
				sa = new int[N];
				lcp = new int[N];
				nofsubs = new int[N];
				nofusubs = new int[N];
				nofusubs_acc = new int[N];
				
        for (int i = 0; i < N; i++)
            suffixes[i] = s.substring(i);
        Arrays.sort(suffixes);
				
				sa[0] = this.index(0);
				lcp[0] = 0;
				nofsubs[0] = N - sa[0];
				nofusubs[0] = nofsubs[0];
				nofusubs_acc[0] = nofsubs[0];
        for (int i = 1; i < s.length(); i++) {
            sa[i] = this.index(i);
						lcp[i] = lcp(i);
						nofsubs[i] = N - sa[i];
						nofusubs[i] = nofsubs[i] - lcp[i];
						nofusubs_acc[i] = nofusubs_acc[i-1] + nofusubs[i];
        }
    }

    // index of ith sorted suffix
    public int index(int i) { return N - suffixes[i].length(); }

   // length of longest common prefix of s and t
    private static int lcp(String s, String t) {
        int N = Math.min(s.length(), t.length());
        for (int i = 0; i < N; i++)
            if (s.charAt(i) != t.charAt(i)) return i;
        return N;
    }

    // longest common prefix of suffixes(i) and suffixes(i-1)
    public int lcp(int i) {
        return lcp(suffixes[i], suffixes[i-1]);
    }

    public static void main(String[] args) {
			try{
				Scanner sc = new Scanner(System.in);
				String generalized = sc.nextLine();
				sublex suffix = new sublex(generalized);
				/*for (int i = 0; i < generalized.length(); i++) {
					System.out.println(" "+i+" "+suffix.sa[i]+" "+suffix.lcp[i]
						+" "+suffix.nofsubs[i]+" "+suffix.nofusubs[i]+" "+suffix.nofusubs_acc[i]
						+" "+generalized.substring(suffix.sa[i]));
				}*/
						
				int n = sc.nextInt();
				sc.nextLine();
				while(n-- > 0){
					//binary search
					int l = sc.nextInt();
					if(sc.hasNextLine())sc.nextLine();
					//System.out.println(generalized+"=>"+l);
					int m=0, lo = 0, hi = generalized.length();
					while(lo <= hi){
						m = lo + (hi - lo)/2;
						if (suffix.nofusubs_acc[m] > l){
							hi = m - 1;
						} else if (suffix.nofusubs_acc[m] < l){
							lo = m + 1;
						} else {
							lo = m;
							break;
						}
					}
					//System.out.println(lo);
					if(lo -1 > 0){
							System.out.println(generalized.substring(suffix.sa[lo],
								suffix.sa[lo]+suffix.lcp[lo]+l-suffix.nofusubs_acc[lo-1]));
					}else{
						if(l-suffix.nofusubs_acc[lo] == 0){
							System.out.println(generalized.substring(suffix.sa[lo],
								suffix.sa[lo]+suffix.lcp[lo]+1));
						}else{
							System.out.println(generalized.substring(suffix.sa[lo],
								suffix.sa[lo]+suffix.lcp[lo]+l-suffix.nofusubs_acc[lo]));
						}
					}
				}
			}catch(Exception e){
				return;
			}
    }
}