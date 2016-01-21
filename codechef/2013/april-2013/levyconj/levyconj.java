import java.util.*;
import java.lang.*;
import java.math.*;

public class levyconj {
		public static void main(String[] args) { 
        int N = 10000;
        // initially assume all integers are prime
        boolean[] isPrime = new boolean[N + 1];
        for (int i = 2; i <= N; i++) {
            isPrime[i] = true;
        }
        // mark non-primes <= N using Sieve of Eratosthenes
        for (int i = 2; i*i <= N; i++) {
            // if i is prime, then mark multiples of i as nonprime
            // suffices to consider mutiples i, i+1, ..., N/i
            if (isPrime[i]) {
                for (int j = i; i*j <= N; j++) {
                    isPrime[i*j] = false;
                }
            }
        }
				// count primes
        int nofPrimes = 0;
				ArrayList<Integer> primes = new ArrayList<Integer>();
        for (int i = 2; i <= N; i++) {
            if (isPrime[i]) {
							primes.add(i);
							nofPrimes++;
						}
        }
				nofPrimes = primes.size();
				int[] primelist = new int[nofPrimes];
			  for (int i=0; i < primelist.length; i++) {
			      primelist[i] = primes.get(i).intValue();
			  }
				System.out.println("nofPrimes: "+nofPrimes);
				Scanner sc = new Scanner(System.in);
				int p,q,cnt,N1;
				int T = sc.nextInt();
				for (int c=1;c<=T;c++){
					N1 = sc.nextInt();
					cnt = 0;
					int offset = 0;
					while(primelist[offset] < N1) {
						//System.out.println(primelist[offset]);
						offset++;
					}
					//System.out.println("off: "+offset);
					if(offset >= nofPrimes) {
						System.out.println(cnt);
						continue;
					}
					p = offset;
					q = 0;
					while(p>0){
						if(q>p) {
							q = 0;
							p--;
							continue;
						}
						
						if(2 * primelist[q] >= N1){
							//System.out.print("p: "+p+"("+primelist[p]+") q: "+q+"("+primelist[q]+")");
							//System.out.println("== use?");
							q = 0;
							p--;
							continue;
						}
						if(N1 == (primelist[p] + (2 * primelist[q])) ) {
							//System.out.print("p: "+p+"("+primelist[p]+") q: "+q+"("+primelist[q]+")");
							cnt++;
							//System.out.println("== bingo");
						}
						//System.out.println();
						q++;
					}
					System.out.println(cnt);
				}
    }
}