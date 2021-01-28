#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) // requires a cast in the funtion call for a pointer not of char* type.
{
	int i; // <-- if this is size_t, for some reason it results in (nil)0x00 being spammed from gcc on my VM. I'm not sure why this is breaking my code if a marker could explain I'd be grateful.
	//to be read as a char, one byte at a time.
	for ( i = len-1; i >= 0; i-- )
	{
		printf( "%p 0x%.2x \n", *(&start + i), *(start + i) ); 
		//printf( "%")
	}

	printf( "\n ");
	return;
}


void show_bits(int num) 
{
	int i;
	// (b): because the CSIL machine and my VM are Little Endian, 
	//last bit accounts for MSB and first is LSB -- therefore to print byte correctly needs to be 
	//i-- from the last bit.
	for( i = (sizeof(num) * 8) -1; i >= 0; i-- ) //8 * because sizeof( ) returns size of data type in BYTES -- need size in BITS
	{
		printf( "%i", (num >> i) & 1); //bit shift right
	}

	printf("\n");

}


void show_int( int x ) {
	printf("\nival = %d\n", x); 
    show_bytes((byte_pointer) &x, sizeof(int)); 
}

void show_float( float x ) {
    printf("fval = %f\n", x); 	
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer( void *x ) {
	printf("pval = %p\n", x); 
    show_bytes((byte_pointer) &x, sizeof(void *));
}


int  mask_LSbits(int n ) // n number of bits for mask (Default n = 1)
{
 	unsigned int c =  0;
 	unsigned int mask;
 	unsigned int w = 64; //because 64-bit machine

 	if( n <= 0 ) return c; //special case n = 0, returns a mask of all 0's.

	if( n >= w ) return ~c; // ~c (not) c flips all bits in c, 
					//logical negation of c's bits. returns -1 to represent overflow
				// Accepted Case: 0 < n < w, Special Cases: n >= w & n <= 0
	else
	{
 		mask = (1 << n)-1; //actual masking being created with one operation, since every << n is 
 						//a shift of 2^n, so I need to subtract by one to account.	
 		return mask; 
 	}
} 

int main() {
    int ival = 12345; 
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);

 /*Add your test cases here in order
   to test your new functions. */

    int n_ival = -12345;
    int m_val = 64;

    printf( "Testing for modified show_bytes( ) function... \n" );
    show_bytes( (char*)pval, sizeof( int ) );
    printf( "Testing for show_bits( ) function on n = +/-%d ... \n", ival);
    show_bits( ival );
    show_bits( n_ival );
    printf( "Testing for mask_LSbits( ) function...\n" );
  	printf( "Masking (set to 1) with n = %d returns %d ( 0x%.8x ) ...", 
  		m_val, mask_LSbits( m_val ), mask_LSbits( m_val ) );




    return 0;

}