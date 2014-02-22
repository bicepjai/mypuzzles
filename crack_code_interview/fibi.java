
public class fibi{
	public static int fib(int n, int a1, int a2){
		if (n<=1) return a1;
		else return fib(n-1, a2,a1+a2);
	}
	
	public static void main(String[] args) {
		System.out.println(fib(9,1,1));
	}
}

