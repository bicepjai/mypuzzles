import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.*;

// PollardRho
class prob4 {
    private final static BigInteger ZERO = new BigInteger("0");
    private final static BigInteger ONE  = new BigInteger("1");
    private final static BigInteger TWO  = new BigInteger("2");
    private final static SecureRandom random = new SecureRandom();
		private final static List<BigInteger> factors = new ArrayList<BigInteger>();

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

    public static void getFactors(BigInteger N) {
        if (N.compareTo(ONE) == 0) return;
        if (N.isProbablePrime(20)) { 
					factors.add(N); 
					/*System.out.println(factors);*/ 
					return; 
				}
        BigInteger divisor = rho(N);
        getFactors(divisor);
        getFactors(N.divide(divisor));
    }

		public static List<BigInteger> getPFactors(BigInteger N) {
				factors.clear();
				getFactors(N);
				return factors;
		}
		
		public static int getBILength(BigInteger N) {
				return N.toString().length();
		}
		
		public static BigInteger formPalindrome(int i) {
				String no1S = Integer.toString(i);
				String no2S = new StringBuffer(Integer.toString(i)).reverse().toString();
				String noS = no1S + no2S;
				BigInteger noB = new BigInteger(noS);
				return noB;
		}
		
    public static void main(String[] args) {
	      List<BigInteger> factors_1 = new ArrayList<BigInteger>();
				List<BigInteger> factors_2 = new ArrayList<BigInteger>();
				List<BigInteger> factors_3 = new ArrayList<BigInteger>();
	
				for(int i=999; i>=100; i--){
						BigInteger N = formPalindrome(i);
						getPFactors(N);
						System.out.println(N+": "+factors);
						factors_1.clear();
						factors_2.clear();
						factors_3.clear();
						for (BigInteger factor1 : factors){
								if(getBILength(factor1) == 3){
										BigInteger factor2 = N.divide(factor1);
										if( getBILength(factor2) == 3){
												System.out.println(N+": "+factors+"=> "+factor1+" and "+factor2);
										}
								}
						}
				}
    }
}
