import java.util.*;
import java.lang.*;
import java.math.*;

public class Main {
	
	public static boolean isPrime(long N){
		int primeTest = 5;
		Random randomGenerator = new Random();
		for(int i=0; i<primeTest; i++){
			long a = randomGenerator.nextLong() % N;
			if(a != 0 && Math.pow(a,N-1) % N != 1) return false;
		}
		return true;
	}
	
	public static List<Long> primeFactors(long numbers) {
		long n = numbers; 
		List<Long> factors = new ArrayList<Long>();
		for (long i = 2; i <= n / i ; i++) { // i*i <= n
			while (n % i == 0) {
				factors.add(i);
				n /= i;
			}
		}
		if (n > 1) {
			factors.add(n);
		}
		return factors;
	}
	
	public static List<Integer> findPrimes(int N)
	{
		List<Integer> primes = new ArrayList<Integer>();
		int sqrt = (int)Math.sqrt((double)N);
		boolean[] isPrime = new boolean[N+1];
		int x,y,n,s,k;
		for ( x = 1; x <= sqrt; x++)
			for ( y = 1; y <= sqrt; y++)
			{
				n = 4 * x * x + y * y;
				if (n <= N && (n % 12 == 1 || n % 12 == 5))
					isPrime[n] ^= true;

				n = 3 * x * x + y * y;
				if (n <= N && n % 12 == 7)
					isPrime[n] ^= true;

				n = 3 * x * x - y * y;
				if (x > y && n <= N && n % 12 == 11)
					isPrime[n] ^= true;
			}

		for ( n = 5; n <= sqrt; n++)
			if (isPrime[n])
			{
				s = n * n;
				for ( k = s; k <= N; k += s)
					isPrime[k] = false;
			}
		if(N >= 2)	primes.add(2);
		if(N >= 3)	primes.add(3);
		for (n = 5; n <= N; n+=2)
			if (isPrime[n])
				primes.add(n);
		return primes;
	}
	
	public static int getMultiplicity(int N, int p) {
		int n = N, m=0;
		while (n/p != 0) {
			n /= p;
			m += n;
		}
		return m;
	}	
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		sc.nextLine();
		for (int i=0;i<n;i++){
			int frm = sc.nextInt();
			int to = sc.nextInt();
			sc.nextLine();			
			System.out.println("frm: "+frm+" to: "+to);
			findPrimes(to);
		}		
	}
}