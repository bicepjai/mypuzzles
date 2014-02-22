/*
https://www.hackerrank.com/challenges/insertionsort1
*/
	import java.util.*;
	import java.lang.*;
	import java.math.*;
	import java.io.*;

public class insertionSort1 {
       
			static void insertionSort(int[] ar) {
				int i,j,x;
				i = ar.length;
				for(j=i-1;j>0;j--){
					if(ar[j-1] > ar[j]){
						x = ar[j];
						ar[j] = ar[j-1];
						printArray(ar);
						ar[j-1] = x;
					} else {
						printArray(ar);
						break;
					}
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
