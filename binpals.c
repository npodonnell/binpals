// binpals.c
// by Noel P O'Donnell, 2014
// Finds all binary palindromes in range [a,b]

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

unsigned int reverse(register unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));

}

int main() {
	
	int np=0,nba=0,nbb=0,nbah=0,nbbh=0,i;
    unsigned x,a,b,ah,bh,ahr,bhr,am,bm;

    
    scanf("%d,%d",&a,&b);
	
    
    // compute # of bits in a
    x=a;
    while(x>0){
		x>>=1;
		nba++;
	}
	
	
	// compute # of bits in b
    x=b;
    while(x>0){
		x>>=1;
		nbb++;
	}
	
	// compute # of bits in (h)igher sections
	nbah=(nba>>1)+(nba%2);
	nbbh=(nbb>>1)+(nbb%2);
	
	if (nbah<1) nbah=1;
	if (nbbh<1) nbbh=1;	
	
	// generate the (h)igher sections
	ah=a>>(nba-nbah);
	bh=b>>(nbb-nbbh);
	
	// generate reversals of these then shift them to the right
	ahr=reverse(ah) >> (32-nbah);
	bhr=reverse(bh) >> (32-nbbh);
	
	// generate mirrors
	am=ahr | (ah<<(nbah-(nba%2)));
	bm=bhr | (bh<<(nbbh-(nbb%2)));
	
	//printf("nba=%d nbb=%d\n",nba,nbb);
	//printf("nbah=%d nbbh=%d\n",nbah,nbbh);
	//printf("ah=%u bh=%u\n",ah,bh);
	//printf("ahr=%u bhr=%u\n",ahr,bhr);
	//printf("am=%u bm=%u\n",am,bm);
	
	if (nba==nbb)
	{
		// a and b have the same bitness
				
		if (nba==0)
			goto done; // [0..0]
			
		if (nba==1){
			np++;
			goto done; // [1..1]
		}
		
		if (nba==2){ 
			if (b==3)
				np=1; // [X..3]
				
			goto done;
		}
		
		// something higher
		np=(bh-ah)+1;
		if (am<a)np--;
		if (bm>b)np--;
		
		goto done;
	}
	
	// b has a higher bitness to a
	for(i=nba; i<=nbb; i++)
	{
		//printf("Counting %d-bit numbers...\n",i);
		
		switch (i){
		
			case 0: continue;
			case 1: np++; continue;
			case 2:
			
				if (a<=3 && b>=3)
					np++;
					
					continue;
			
			default:
			
				if (i>nba && i<nbb){
					np+= ((1 << ((i>>1)-1)) * (1+(i%2))); // just to confuse people
					continue;
				}
				
				if (i==nba){				
					np+= (1<<nbah)-ah; // palindromes after a with same bitness as a
										
					if (am<a)np--; // a exceeds it's mirror				
					continue;
				}
				
				if (i==nbb){
					np+= bh-((1<<(nbbh-1))-1); // palindromes before b with same bitness as b
					
					if (bm>b)np--; // b's mirror exceeds b			
					continue;
				}					
		}
			
	}

done:
	printf("%d",np);
    return 0;
}


