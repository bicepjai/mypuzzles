/*
https://www.hackerrank.com/challenges/insertionsort1
*/
	import java.util.*;
	import java.lang.*;
	import java.math.*;
	import java.io.*;

public class insertionSort2 {
	static void insertionSort(int[] ar) {
		int i,j,x;
		boolean exchange;
		for(i=0;i<ar.length;i++){
			for(j=i;j>0;j--){
				if(ar[j-1] > ar[j]){
					exchange = true;
					x = ar[j];
					ar[j] = ar[j-1];
					ar[j-1] = x;
				} else {
					break;
				}
			}
			if(i>0)	printArray(ar);
		}              
	}

	static void printArray(int[] ar) {
		for(int n: ar){
			System.out.print(n+" ");
		}
		System.out.println("");
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int[] ar = new int[n];
		for(int i=0;i<n;i++){
			ar[i]=in.nextInt(); 
		}
		insertionSort(ar);
	}    
}
