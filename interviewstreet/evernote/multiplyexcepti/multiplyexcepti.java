import java.util.*;
import java.lang.*;
import java.math.*;

public class multiplyexcepti {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int N = sc.nextInt(); 
		sc.nextLine();
		
		BigInteger product = BigInteger.ONE;
		int i,j,n;
		int [] ints = new int[N];
		boolean zeroPresence = false;
		boolean printZero = false;
		for (i=0;i<N;i++){
			n = sc.nextInt();
			if(i<N-1)sc.nextLine();
			
			ints[i] = n;
			
			if (n==0) {
				zeroPresence = true;
			} else {
				product = product.multiply(BigInteger.valueOf(n));
			}
		}
		if(!zeroPresence){
			for (i=0;i<N;i++){
				System.out.println(product.divide(BigInteger.valueOf(ints[i])));
			}
		}else {
			for (i=0;i<N;i++){
				printZero = false;
				for (j=0;j<N;j++){
					if(j!=i && ints[j]==0) {
						printZero = true;
						break;
					}
				}
				if(printZero)
					System.out.println(0);
				else
					System.out.println(product);
			}			
		}
					
	}
}