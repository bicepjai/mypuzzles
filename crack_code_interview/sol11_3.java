import java.util.*;
import java.io.*;

public class sol11_3 {
		
	public static void findOpenNumber() throws FileNotFoundException {
		int bitsize = 1048576; // 2^20 bits (2^17 bytes)
		int blockNum = 4096; // 2^12
		byte[] bitfield = new byte[bitsize/8];
		int[] blocks = new int[blockNum];
		
		int starting = -1;
		Scanner in = new Scanner(System.in);

		while (in.hasNextInt()) {
			int n = in.nextInt();
			blocks[n / (bitfield.length * 8)]++;
		}
		System.out.println(Arrays.toString(blocks));
	
	 	for (int i = 0; i < blocks.length; i++) {
	 		if (blocks[i] < bitfield.length * 8){
	 		    //if value < 2^20, then at least 1 number is missing in
					//that section.
					starting = i * bitfield.length * 8;
				break;
			}
		}
		System.out.println("starting=> "+ starting);
		
		in = new Scanner(new FileReader("in11_3.txt"));
	 	while (in.hasNextInt()) {
	 		int n = in.nextInt();
			   	//If the number is inside the block that’s missing numbers,
			 		//we record it
				if( n >= starting && n < starting + bitfield.length * 8){
					bitfield [(n-starting) / 8] |= 1 << ((n - starting) % 8);
				}
				/*if( n < bitfield.length * 8){
					bitfield [(n) / 8] |= 1 << ((n) % 8);
				}*/
		}
		
		for (int i = 0 ; i < bitfield.length; i++) {
			for (int j = 0; j < 8; j++) {
			// 	Retrieves the individual bits of each byte. When 0 bit
			//		is found, finds the corresponding value.
				if ((bitfield[i] & (1 << j)) == 0) {
					System.out.println(i * 8 + j + starting);
					//System.out.println(i * 8 + j);
				}
			}
		}
		System.out.println("over");
		return;
	}
		
	public static void main(String[] args) {
		try{
			findOpenNumber();
		} catch(Exception e){}
	}
	
}