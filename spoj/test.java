import java.util.*;

public class test {
	
    public static void main(String[] args) {
			try{
				Scanner sc = new Scanner(System.in);
						
				int n = sc.nextInt();
				sc.nextLine();
				while(n != 42){	
					System.out.println(n);
					n = sc.nextInt();
					sc.nextLine();
				}
			}catch(Exception e){
				return;
			}
    }
}