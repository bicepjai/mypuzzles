public class c11 {
	private static boolean unique(String str) {
		int i,j;
		int len = str.length();
		
		boolean[] charsat = new boolean[256];
		
		for(i=0;i<len;i++){
				j = str.charAt(i);
				if (charsat[j])
					return false;
				else
					charsat[j] = true;
		}
		return true;
	}
	
	public static boolean isUniqueChars2(String str) {
		boolean[] char_set = new boolean[256];
		for (int i = 0; i < str.length(); i++) {
			int val = str.charAt(i);
			if (char_set[val]) return false;
			char_set[val] = true;
		}
		return true;
	}
	
	public static void main(String[] args) {
		System.out.println(c11.unique(args[0]));
		System.out.println(c11.isUniqueChars2(args[0]));
	}
	
}