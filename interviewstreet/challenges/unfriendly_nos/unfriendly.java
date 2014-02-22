import java.util.*;
import java.lang.*;

public class unfriendly {
	
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

	public static List<Long> allFactors(long N) {
		long i = 1; 
		List<Long> factors = new ArrayList<Long>();
		while (i <= n/i) {
			if(n%i == 0){
				factors.add(i);
				if(i != n/i)
				factors.add(n/i);
			}
			i++;
		}
		return factors;
	}
		
	public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		long k = sc.nextLong();
					
		int i, answer = 0;
		sc.nextLine();
		long[] unfriendlynos = new long[n];
		for(i=0;i<n;i++)
			unfriendlynos[i] = sc.nextLong();
		
		//System.out.println(allFactors(k));			
		//System.out.println(Arrays.toString(unfriendlynos));			
		for (long factor : allFactors(k)) {
			boolean notaFactor = true;
			for (long unfriend : unfriendlynos) {
				if(unfriend % factor == 0) {
					notaFactor = false;
					break;
				}
			}
			if (notaFactor) answer++;
		}
		System.out.println(answer);			
	 }
}