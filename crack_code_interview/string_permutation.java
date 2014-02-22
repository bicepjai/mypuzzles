public class string_permutation {
	private static void permute(String string) {
		permute(string,0);
	}
	
	private static void permute(String str, int n) {
		int n = str.length();
		if (n == 0) System.out.println(prefix);
		else {
			for (int i = 0; i < n; i++)
				//permute(prefix + str.charAt(i), str.substring(0, i) + str.substring(i+1, n));
				permute(str.substring(0, i),str.substring(i+1, n));
		}
	}
	
	public static void main(String[] args) {
		//string_permutation strp = new string_permutation();
		string_permutation.permute("abcd");
	}
	
}