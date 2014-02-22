import java.util.*;
import java.lang.*;
import java.math.*;

public class b {
	
	
	/** A ridiculously large number  */
	protected static final int MAX_DIGITS = 255;

	/** Check if a number is palindromic. */
	public static boolean isPalindrome(BigInteger num) {
		String digits = num.toString();
		int numDigits = digits.length();
		if (numDigits >= MAX_DIGITS) {
			throw new IllegalStateException("too big");
		}
		// Consider any single digit to be as palindromic as can be
		if (numDigits == 1)
			return true;
		for (int i=0; i<numDigits/2; i++) {
			if (digits.charAt(i) != digits.charAt(numDigits - i - 1))
				return false;
		}
		return true;
	}
	
	public static BigInteger bigIntSqRootFloor(BigInteger x)
	        throws IllegalArgumentException {
	    if (x.compareTo(BigInteger.ZERO) < 0) {
	        throw new IllegalArgumentException("Negative argument.");
	    }
	    // square roots of 0 and 1 are trivial and
	    // y == 0 will cause a divide-by-zero exception
	    if (x == BigInteger.ZERO || x == BigInteger.ONE) {
	        return x;
	    } // end if
	    BigInteger two = BigInteger.valueOf(2L);
	    BigInteger y;
	    // starting with y = x / 2 avoids magnitude issues with x squared
	    for (y = x.divide(two);
	            y.compareTo(x.divide(y)) > 0;
	            y = ((x.divide(y)).add(y)).divide(two));
	    return y;
	} // end bigIntSqRootFloor

	public static BigInteger bigIntSqRootCeil(BigInteger x)
	        throws IllegalArgumentException {
	    if (x.compareTo(BigInteger.ZERO) < 0) {
	        throw new IllegalArgumentException("Negative argument.");
	    }
	    // square roots of 0 and 1 are trivial and
	    // y == 0 will cause a divide-by-zero exception
	    if (x == BigInteger.ZERO || x == BigInteger.ONE) {
	        return x;
	    } // end if
	    BigInteger two = BigInteger.valueOf(2L);
	    BigInteger y;
	    // starting with y = x / 2 avoids magnitude issues with x squared
	    for (y = x.divide(two);
	            y.compareTo(x.divide(y)) > 0;
	            y = ((x.divide(y)).add(y)).divide(two));
	    if (x.compareTo(y.multiply(y)) == 0) {
	        return y;
	    } else {
	        return y.add(BigInteger.ONE);
	    }
	} // end bigIntSqRootCeil
	
	static boolean PerfectSquare(BigInteger n)	{
	    
			long ln = n.longValue();
			long h = ln & 0xF; // last hexidecimal "digit"
			
	    if (h > 9)
	        return false; // return immediately in 6 cases out of 16.

	    // Take advantage of Boolean short-circuit evaluation
	    if ( h != 2 && h != 3 && h != 5 && h != 6 && h != 7 && h != 8 )	{
	        // take square root if you must
	        //int t = (int) floor( sqrt((double) n) + 0.5 );
					BigInteger t = bigIntSqRootFloor(n);
	        return t.multiply(t).equals(n);
	    }
	    return false;
	}
	
	static void getInput() {
		Scanner sc = new Scanner(System.in);
		int N = sc.nextInt();
		int count = 0;
		for (int c=1;c<=N;c++){
			BigInteger A = sc.nextBigInteger();
			BigInteger B = sc.nextBigInteger();
			System.out.println("==>"+A.toString());
			System.out.println("==>"+B.toString());
			count = 0;
			for (BigInteger i = A; i.compareTo(B) <= 0; i = i.add(BigInteger.ONE)) {
				if(PerfectSquare(i) && isPalindrome(i)) count++;
				//System.out.println(i.toString());
			}
				System.out.println(count);
		}
	}
	
	public static void main(String[] args) {
		getInput();
	}
}