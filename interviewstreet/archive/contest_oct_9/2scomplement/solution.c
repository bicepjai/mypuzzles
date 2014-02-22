#include <stdio.h>

/* Count the ON bits in n using an iterative algorithm */
long bitcount(long n) {
	long c = 0;
	while ( n != 0 ) { c += ( n & 1L ); n >>= 1; }
	return c;
}

long count1sposnos(long n, int pwr2) {
	if(n==0 || n==1 || n==2 || n==3) pwr2 = 0;
	if (n == 0) return 0;
	else if (n == 1 || n == 2) return 1;
	else if (n == 3) return 2;
	else if (n%2 == 1) {
		return (n/(2^pwr2) + 2*count1sposnos(n/2,pwr2++) + bitcount(n/2));
	}
	else {
		return (n/(2^pwr2) + 2*count1sposnos(n/2,pwr2++));
	}
}

long count1snegnos(long n) {
	if (n==0)
		return 0;
	long N = (-1*n); 
	if (N-1 == 0) return 32;
	else return (N*32) - count1sposnos(N,0);
}

int main()
{
	long T, A, B, i, j, bits;
	scanf ("%ld",&T);
	for(i=0;i<T;i++) {
		scanf ("%ld %ld",&A,&B);
		bits = 0;
	
		if(B==0)
			bits = bits + count1sposnos(B,0);
		else if(B>0)
			bits = bits + count1sposnos(B+1,0);
		else
			bits = bits + count1snegnos(B);
				
		if(A==0)
			bits = bits + count1sposnos(A,0);
		else if(A>0)
			bits = bits + count1sposnos(A+1,0);
		else
			bits = bits + count1snegnos(A);

		if (i==T-1)
			printf("%ld",bits);
		else
			printf("%ld", bits);
		
		bits = 0;
		for(j=A;j<B;j++) {
			if(j<0){
				bits = bits + 32 - bitcount((-1*j)-1);
			} else {
				bits = bits + bitcount(j);
			}
		}
		printf("(%ld)\n",bits);
			
	}
	return 0;
}

// int main()
// {
// 	// unsigned long	twos;
// 	long T, A, B, i, j, bits;
// 	// int k=0;
// 	int *rec = 0;
// 	
// 	scanf ("%ld",&T);
// 	for(i=0;i<T;i++) {
// 		scanf ("%ld %ld",&A,&B);
// 		bits = 0;
// 				
// 		// brute force
// 		for(j=A;j<B;j++) {
// 			nor_var++;
// 			if(j<0){
// 				bits = bits + 32 - bitcount((-1*j)-1);
// 				// printf("%d ",32-bitcount((-1*j)-1));
// 			} else {
// 				bits = bits + bitcount(j);
// 				// printf("%d ",bitcount(j));
// 			}
// 		}
// 		printf("B=%ld: %ld (%d)\n",B, bits, nor_var);
// 		
// 		if (i==T-1)
// 			printf("%d: %d\n",B, bits);
// 		else
// 			printf("%d: %d\n",B, bits);
// 	}
// 	return 0;
// }

// /* Count the ON bits in n using an iterative algorithm */
// long count1sposnos(long n) {
// 	static int pwr2 = 0;
// 	if (n == 0) return 0;
// 	else if (n == 2) return 1;
// 	else return (n/(2^pwr2++) + 2*count1sposnos(n/2));
// }

// int main()
// {
// 	unsigned long	twos;
// 	int T, A, B, i, j, bits;
// 	
// 	scanf ("%d",&T);
// 	for(i=0;i<T;i++) {
// 		scanf ("%d %d",&A,&B);
// 		// A = -100; B = 100;
// 		bits = 0;
// 		for(j=A;j<=B;j++) {
// 			if(j>=0){
// 				bits = bits + bitcount(j);
// 				// printf("%d %d; ",j,bitcount(j));
// 			} else {
// 				twos = ~(-1*j);
// 				twos = twos & 0xffffffff;
// 				twos = twos + 1;
// 				bits = bits + bitcount(twos);
// 				// printf("%d %d; ",j,bitcount(twos));
// 			}			
// 		}
// 		if (i==T-1)
// 			printf("%d",bits);
// 		else
// 			printf("%d\n",bits);
// 	}
// 	return 0;
// }
// 
// /* Count the ON bits in n using an iterative algorithm */
// int bitcount(long n) {
// 	int tot = 0;
// 	unsigned int i;
// 	for (i = 1; i > 0; i = i<<1)
// 		if (n & i)
// 			++tot;
// 	return tot;
// }

// static int bits_len_array[2147483648];
// int main()
// {
// 	unsigned long	twos;
// 	int T, A, B, i, j, bits;
// 	
// 	scanf ("%d",&T);
// 	for(i=0;i<T;i++) {
// 		scanf ("%d %d",&A,&B);
// 		bits = 0;
// 		for(j=A;j<=B;j++) {
// 			if(j<0){
// 				bits = bits + 32 - bitcount((-1*j)-1);
// 				// printf("%d %d\n",j,bitcount((-1*j)-1));
// 			} else {
// 				bits = bits + bitcount(j);
// 				// printf("%d %d; ",j,bitcount(j));
// 			}
// 		}
// 		if (i==T-1)
// 			printf("%d",bits);
// 		else
// 			printf("%d\n",bits);
// 	}
// 	return 0;
// }
// 
// /* Count the ON bits in n using an iterative algorithm */
// int bitcount(long n) {
// 	int tot = 0;
// 	unsigned int i;
// 	if(bits_len_array[n] != 0){
// 		return bits_len_array[n];
// 	} else {
// 		printf("calculated for %ld\n",n);
// 		for (i = 1; i > 0; i = i<<1)
// 			if (n & i)
// 				++tot;
// 		bits_len_array[n]=tot;
// 		return tot;
// 	}
// }