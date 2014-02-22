public class c13 { 
public static void removeDuplicates(char[] str) {
	if (str == null) return;
	int len = str.length;
	if (len < 2) return;
	boolean[] hit = new boolean[256];
	for (int i = 0; i < 256; ++i) {
		hit[i] = false;
	}
	hit[str[0]] = true;
	int tail = 1;
	for (int i = 1; i < len; ++i) {
		if (!hit[str[i]]) {
			str[tail] = str[i];
			++tail;
			hit[str[i]] = true;
		}
	}
	System.out.println(tail);
	while(tail < len) {
		str[tail] = 0;
		tail++;
	}
 }

	public static void main(String[] args) {
		char[] str = (args[0]).toCharArray();
		c13.removeDuplicates(str);
		System.out.println(str);
	}
}