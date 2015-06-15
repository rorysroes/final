#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int FFT_radix_2(int *X ,int *x ,int w ,int N,int P);
int BaseP(int *x, int N, int a, int P);

int main()
{
	int *y, *x, *X, *Y, *Z, *z, a , b, i;
	clock_t t1,t2;
    int N = 32, n = 1365, w = 10, W = 141, P = 1409; 
	printf("Input a , b : ");
	scanf("%d %d", &a, &b);
	//printf("%d x %d = %d\n", a, b, a*b); 
	                
	x = (int * ) malloc(N*sizeof(int));
	y = (int * ) malloc(N*sizeof(int));
	z = (int * ) malloc(N*sizeof(int));
    X = (int * ) malloc(N*sizeof(int));
    Y = (int * ) malloc(N*sizeof(int));
    Z = (int * ) malloc(N*sizeof(int));

	BaseP(x, N, a, 10);
	BaseP(y, N, b, 10);
	
    for(i=0;i<N;++i) 
    printf("%d ",x[i]); 
	printf("\n");	

	t1 = clock();
	FFT_radix_2(X ,x ,w ,N ,P);	
	t2 = clock();
	printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
    for(i=0;i<N;++i) printf("%d ",X[i]);
    printf("\n");
	system("pause");
	
	for(i=0;i<N;++i) 
	printf("%d ",y[i]);
	printf("\n");
		
	t1 = clock();
	FFT_radix_2(Y,y,w,N,P);	
	t2 = clock();
	printf("%f secs\n", 1.0*(t2-t1)/CLOCKS_PER_SEC);	
    for(i=0;i<N;++i) printf("%d ",Y[i]);
    printf("\n");
	system("pause");

	for(i=0;i<N;++i) Z[i] =(((X[i] * Y[i]) % P) * n ) % P;
	//for(i=0;i<N;++i) printf("Z[%d]=%d\n",i,Z[i]);
	
	FFT_radix_2(z ,Z , W ,N ,P );	
    for(i=0;i<N;++i) printf("%d ",z[i]);
    printf("\n");
	system("pause");
 
	free(x);
	free(y);
	free(z);
	free(X);
	free(Y);
	free(Z);
	
    return 0;
}

int FFT_radix_2(int *X ,int *x ,int w ,int N,int P)
{ 
	if(N==1)
	{
        X[0] = x[0]; 
	    return 0; 	
	}
	int k, n,i;
	int *even, *odd, wk;
    int *even_FT, *odd_FT;

	even = (int *) malloc(N*sizeof(int));
	odd = even + N/2; //(double *) malloc(N/2*sizeof(double));
	even_FT = (int *) malloc(N*sizeof(int));
	odd_FT = even_FT + N/2;//(double *) malloc(N/2*sizeof(double));
	 
	for(n=0;n<N/2;++n)
	{
		even[n] = x[2*n];
		odd[n] = x[2*n+1];
	} 
	
	FFT_radix_2(even_FT ,even , w * w  % P,N/2 ,P);
	FFT_radix_2(odd_FT ,odd , w * w  % P ,N/2 ,P);

	wk=1;
	
    if(N==32){
		for(k=0;k<N/2;++k)
	        {
				X[k] = (even_FT[k] + (wk * odd_FT[k]))  % P;
				//printf("wk=%d\n",wk);
				wk =( wk * (w * (w * (w * (w * (w * ( w *( w * ( w * w % P) * w % P) * w % P) * w % P)* w % P)* w % P)* w % P)* w % P) ) % P;
				//printf("wk=%d\n",wk);
				X[k+N/2] = (even_FT[k] + (wk * odd_FT[k])) % P; 
				
                if(k==14){
				    wk = (w * (w * (w * (w * (w * (w * (w * w * w % P)* w % P)* w % P) * w % P)* w % P)* w % P) * w) % P;					
				}else if(k==13){
				    wk = w * (w * (w * (w * (w * (w * w * w * w % P )* w % P) * w % P)* w % P)* w % P)* w % P;				
				}else if(k==12){
				    wk = w * (w * (w * (w * (w * (w * w * w % P) * w % P) * w % P)* w % P)* w % P)* w % P;				
				}else if(k==11){
				    wk = w * (w * (w * (w * (w * (w * w * w % P)* w % P) * w % P)* w % P)* w % P) % P;				
				}else if(k==10){
				    wk = w * (w * (w * (w * (w * w * w % P) * w % P)* w % P)* w % P)* w % P;					
				}else if(k==9){
				    wk = w * (w * (w * (w * w * w * w % P)* w % P)* w % P) * w % P;				
				}else if(k==8){
				    wk = w * (w * (w * (w * w * w % P) * w % P) * w % P) * w % P;				
				}else if(k==7){
				    wk = w * (w * (w * w * w * w % P)* w % P)* w % P;				
				}else if(k==6){
				    wk = w * (w * (w * w * w % P ) * w % P) * w % P;				
				}else if(k==5){
				    wk = w * (w * w * w * w % P)* w % P;				
				}else if(k==4){
			        wk = w * (w * w * w % P) * w % P;
				}else if(k==3){
				    wk = w * w * w * w % P;
			    }else if(k==2) {
				    wk = w * w * w % P;
				}else if(k==1) {
				    wk = w * w % P;
			    }else{
			    	wk = w % P;	
				}
			}
	}	
	else if(N==16){
		for(k=0;k<N/2;++k)
	        {
				X[k] = (even_FT[k] + (wk * odd_FT[k]))  % P;
				//printf("wk=%d\n",wk);
				wk = (wk * (w * (w * (w * w * w * w % P)* w % P)* w % P) ) % P;
				//printf("wk=%d\n",wk);
				X[k+N/2] = (even_FT[k] + (wk * odd_FT[k])) % P; 
				
				if(k==6){
				    wk = w * (w * (w * w * w % P)* w % P)* w % P;				
				}else if(k==5){
				    wk = w * (w * w * w * w % P)* w % P;				
				}else if(k==4){
			        wk = w * (w * w * w % P)* w % P;
				}else if(k==3){
				    wk = w * w * w * w % P;
			    }else if(k==2) {
				    wk = w * w * w % P;
				}else if(k==1) {
				    wk = w * w % P;
			    }else{
			    	wk = w % P;	
				}
			}
	}else if(N==8){
			for(k=0;k<N/2;++k)
			{
				X[k] = (even_FT[k] + (wk * odd_FT[k]))  % P;
				//printf("wk=%d\n",wk);
				wk = (wk * (w * w * w * w % P) )% P;
				//printf("wk=%d\n",wk);
				X[k+N/2] = (even_FT[k] + (wk * odd_FT[k])) % P; 
				
				if(k==2){
				    wk = w * w * w % P;
			    }else if(k==1) {
				    wk = w * w % P;
			    }else{
			    	wk = w % P;	
				}
		    }
	}else if(N==4){
		for(k=0;k<N/2;++k)
			{
				X[k] = (even_FT[k] + (wk * odd_FT[k]))  % P;
				//printf("wk=%d\n",wk);
				wk = wk * w * w % P;
				//printf("wk=%d\n",wk);
				X[k+N/2] = (even_FT[k] + (wk * odd_FT[k])) % P; 
				wk = w  % P; 
		    }
    }else{
		for(k=0;k<N/2;++k)
			{
				X[k] = (even_FT[k] + (wk * odd_FT[k]))  % P;
				//printf("wk=%d\n",wk);
				wk = wk * w % P;
				//printf("wk=%d\n",wk);
				X[k+N/2] = (even_FT[k] + (wk * odd_FT[k])) % P; 
		    }    	
	}
	//printf("N=%d\n",N);
	//for(i=0;i<N/2;++i) printf("X[%d]=%d\n",i,X[i]);
	//for(i=0;i<N/2;++i) printf("X[%d]=%d\n",i+N/2,X[i+N/2]);
    //printf("\n");
    
    
	free(even);
	free(even_FT);
	return 0;
}

int BaseP(int *x, int N, int a, int P)
{
	int i;
	for(i=0;i<N;i++)
	{
		x[i] = a % P;
		a -= x[i];
		a /= P;
	}
	return 0;
} 
