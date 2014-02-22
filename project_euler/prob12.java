import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.*;
    

class pollard_rho {
    private final static BigInteger ZERO = new BigInteger("0");
    private final static BigInteger ONE  = new BigInteger("1");
    private final static BigInteger TWO  = new BigInteger("2");
    private final static SecureRandom random = new SecureRandom();
	public static Map<BigInteger,Integer> primes = new HashMap<BigInteger,Integer>();
	
    public static BigInteger rho(BigInteger N) {
        BigInteger divisor;
        BigInteger c  = new BigInteger(N.bitLength(), random);
        BigInteger x  = new BigInteger(N.bitLength(), random);
        BigInteger xx = x;

        // check divisibility by 2
        if (N.mod(TWO).compareTo(ZERO) == 0) return TWO;

        do {
            x  =  x.multiply(x).mod(N).add(c).mod(N);
            xx = xx.multiply(xx).mod(N).add(c).mod(N);
            xx = xx.multiply(xx).mod(N).add(c).mod(N);
            divisor = x.subtract(xx).gcd(N);
        } while((divisor.compareTo(ONE)) == 0);

        return divisor;
    }

    public static void factor(BigInteger N) {
        if (N.compareTo(ONE) == 0) return;
        if (N.isProbablePrime(20)) { 
			//System.out.println(N); 
			if(primes.containsKey(N)){
				Integer s = primes.get(N);
				primes.put(N,s+1);
			}else
				primes.put(N,1);
			return;
		}
        BigInteger divisor = rho(N);
        factor(divisor);
        factor(N.divide(divisor));
    }

/*
A faster method is to factorize N, and use the divisor function(http://en.wikipedia.org/wiki/Divisor_function)
to compute the amount of divisors.
If the factorization of N is:
p1^e1 . p2^e2 . p3^e3
Where  are the prime factors and  are their exponents, then the total amount of divisors of N is:
e1 + 1 . e2 + 1 . e3 + 1
*/ 
    public static void main(String[] args) {
		int n = 3, tri = 1, p = 1;
		while(p<=500){
			p = 1;
			tri = n*(n+1)/2;
			if (tri%2 != 0 || tri%3 != 0){
			}else{
				factor(BigInteger.valueOf(tri));
				for (Map.Entry<BigInteger, Integer> entry : primes.entrySet())
					p = p*(entry.getValue() + 1);
				primes.clear();
			}
			n++;
		}
		System.out.println(tri +" "+ p);
    }
}
