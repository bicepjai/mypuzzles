/*
http://www.codeeval.com/open_challenges/10/
*/

	import java.util.*;
	import java.lang.*;
	import java.math.*;
	import java.io.*;

	public class m2last {
		
		public static void main(String[] args) {
			/*
			Scanner sc = new Scanner(System.in);
			while (sc.hasNextLine()) {
				String line = sc.nextLine();
				String[] lineArray = line.split(" ");
				int arraySize = lineArray.length;
				int m = Integer.parseInt(lineArray[arraySize-1]);
				//System.out.println(Arrays.toString(lineArray));
				//System.out.println(m);
				if (arraySize-1 >= m){
					System.out.println(lineArray[arraySize-m-1]);
				}
			}*/
	    try {
	        File file = new File(args[0]);
	        BufferedReader in = new BufferedReader(new FileReader(file));
	        String line;
	        while ((line = in.readLine()) != null) {
						String[] lineArray = line.split(" ");
						int arraySize = lineArray.length;
						int m = Integer.parseInt(lineArray[arraySize-1]);
						if (arraySize-1 >= m){
							System.out.println(lineArray[arraySize-m-1]);
						} 
	        }
	    } catch (IOException e) {
	        System.out.println("File Read Error: " + e.getMessage());
	    }
		}
	}