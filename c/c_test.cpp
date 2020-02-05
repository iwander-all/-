#define E 206000//
#define alpha 0.90//
#include <stdio.h>
int main()
{
   double length[5]={0,490,380,270,160}, a[5], Y[5], J[5],L[5]={0},length1;
   double c=0,S=0;
   int k, i, b, h;
   a[1]=0; b=60; h=7;
   length1=581.5;
   for (k=0;k<4;k++)
   {
       a[k+1]=length1-length[k+1];
	    printf("a[%d]=%lf\n",k+2,a[k+1]);
	   printf("a[%d]^3=%lf\n",k+2,a[k+1]*a[k+1]*a[k+1]);
       for (i=0;i<k+1;i++)//对转动惯量进行求和
	   {
          J[i]=b*h*h*h/12;
          L[k]=L[k]+J[i]; 
          J[i+1]=b*h*h*h/12;
          L[k+1]=L[k]+J[i+1];
		  printf("J[%d]=%lf\n",k,J[i]);
        }
        Y[k]=1/L[k];
        Y[k+1]=1/L[k+1];
		printf("L[%d]=%lf\n",k+2,L[k+1]);
		printf("Y[%d]=%lf\n",k+1,Y[k]);
		printf("Y[%d]=%lf\n",k+2,Y[k+1]);
		printf("L[%d]=%lf\n",k+1,L[k]);
		
        L[k]=0; L[k+1]=0;
		printf("Y[%d]-Y[%d]=%lf\n",k+1,k+2,Y[k]-Y[k+1]);
		printf("a[%d]^3(Y[%d]-Y[%d])=%lf\n",k+2,k+1,k+2,(Y[k]-Y[k+1])*a[k+1]*a[k+1]*a[k+1]);
        S=S+a[k+1]*a[k+1]*a[k+1]*(Y[k]-Y[k+1]);
		printf("S=%lf\n",S);
		printf("\n");
   }
   S=S+length1*length1*length1*Y[4];printf("S=%lf\n",S);
   c=6*alpha*E/S;
   printf("c=%lf\n",c);
   return 0;
}
