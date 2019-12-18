/*23.09.2019*/
//EVALUATION OF K2, Kz, Kmz Ka, Kma- gradient
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <conio.h>
#include <omp.h>
double ka0,kma0,kz0,kmz0,k20;
double s_a[30000], s_z[30000], s_p[30000], ds[30000];
double a0=0.10147399,z0=0.12196783,p0=0.0,c0,c1,c2;


#define MAX_THREADS 8
main()
{
int n,i,i1,i2,i3,i4,i5,i6,iijj,ipp;
double  max,h;

double  p;


double  r,r1,r2,r8;

double alfa1_a,alfa2_a,beta1_a, beta2_a,gamma_a,alfa1_z,beta1_z,alfa2_z,beta2_z,gamma_z,alfa1_p,alfa2_p,beta1_p,beta2_p,gamma_p;
double min1,min2,kk21,kka1,kkma1,kkz1,kkmz1;

double cat0,h1;


int i10,j,l,l1,k,k1,n1,nb,nb1,ip,i_count,i_count1,j1,ii;
double  tt[20],ttt[20],s[10000];
char  buf[800000],c[20];

FILE *stream_t;
FILE *stream_a;
FILE *stream_z;
FILE *stream_p;
stream_a = fopen("data_A.dat", "r");
stream_z = fopen("data_Z.dat", "r");
stream_p = fopen("data_P.dat", "r");
stream_t = fopen("time.dat", "r");

n=200;
//getch();

   max=100000000000.;
   c[0]=48;
   c[1]=49;
   c[2]=50;
   c[3]=51;
   c[4]=52;
   c[5]=53;
   c[6]=54;
   c[7]=55;
   c[8]=56;
   c[9]=57;

   tt[0]=1.;
   tt[1]=10.;
   tt[2]=100.;
   tt[3]=1000.;
   tt[4]=10000.;

   ttt[0]=0.1;
   ttt[1]=0.01;
   ttt[2]=0.001;
   ttt[3]=0.0001;
   ttt[4]=0.00001;
   ttt[5]=0.000001;
   ttt[6]=0.0000001;
   ttt[7]=0.00000001;
   ttt[8]=0.000000001;
   ttt[9]=0.0000000001;
   ttt[10]=0.00000000001;
   ttt[11]=0.000000000001;
   ttt[12]=0.0000000000001;
   ttt[13]=0.00000000000001;
   ttt[14]=0.000000000000001;
   ttt[15]=0.0000000000000001;
   ttt[16]=0.00000000000000001;
   ttt[17]=0.000000000000000001;
   ttt[18]=0.0000000000000000001;
   ttt[19]=0.00000000000000000001;


//********* DATUM _A************
//1._____ Reading of array_____
nb=100000;
fread(buf,nb,1,stream_a);

//2._______ Decoding of array ______

i2=0;
i1=0;
mn2:
i_count1=0;
mn:
ii=buf[i1];if(ii==44) {j1=i_count1;}
ii=buf[i1];if(ii==10) {i1=i1+1;i_count1=i_count1+1;goto mn1;}

i1=i1+1;
i_count1=i_count1+1;
goto mn;

mn1:
//1.				//SAMPLE
i3=buf[i1-i_count1+j1];
//printf("\n %4d %d %d %d %d",i1,i2,i3,i1-i_count1+j1,i_count1);

r2=1.;
r=0.;
for(i=0;i<j1;i++)
{
i3=buf[i1-i_count1+j1-i-1];
//printf("\n %4d %d",i,i3);
//getch();
if(i3==48){r1=0.;r=r+r1*tt[i];}
if(i3==49){r1=1.;r=r+r1*tt[i];}
if(i3==50){r1=2.;r=r+r1*tt[i];}
if(i3==51){r1=3.;r=r+r1*tt[i];}
if(i3==52){r1=4.;r=r+r1*tt[i];}
if(i3==53){r1=5.;r=r+r1*tt[i];}
if(i3==54){r1=6.;r=r+r1*tt[i];}
if(i3==55){r1=7.;r=r+r1*tt[i];}
if(i3==56){r1=8.;r=r+r1*tt[i];}
if(i3==57){r1=9.;r=r+r1*tt[i];}
if(i3==45){r2=-1.;}
}

for(i=0;i<i_count1-j1-2;i++)
{
i3=buf[i1-i_count1+j1+i+1];
if(i3==48){r1=0.;}
if(i3==49){r1=1.;}
if(i3==50){r1=2.;}
if(i3==51){r1=3.;}
if(i3==52){r1=4.;}
if(i3==53){r1=5.;}
if(i3==54){r1=6.;}
if(i3==55){r1=7.;}
if(i3==56){r1=8.;}
if(i3==57){r1=9.;}
r=r+r1*ttt[i];
}

s_a[i2]=r2*r;
//printf("\n %4d %20.18f",i2,s_a[i2]);
//getch();

i2=i2+1;


if(i2<n) {goto mn2;}		// NEW Sample

//_______END of  Decoding of array ______





//********* TIME ************
//1._____ Reading of array_____
nb=100000;
fread(buf,nb,1,stream_t);

//2._______ Decoding of array ______

i2=0;
i1=0;
d_mn2:
i_count1=0;
d_mn:
ii=buf[i1];if(ii==44) {j1=i_count1;}
ii=buf[i1];if(ii==10) {i1=i1+1;i_count1=i_count1+1;goto d_mn1;}

i1=i1+1;
i_count1=i_count1+1;
goto d_mn;

d_mn1:
//1.				//SAMPLE
i3=buf[i1-i_count1+j1];
//printf("\n %4d %d %d %d %d",i1,i2,i3,i1-i_count1+j1,i_count1);

r2=1.;
r=0.;
for(i=0;i<j1;i++)
{
i3=buf[i1-i_count1+j1-i-1];
//printf("\n %4d %d",i,i3);
//getch();
if(i3==48){r1=0.;r=r+r1*tt[i];}
if(i3==49){r1=1.;r=r+r1*tt[i];}
if(i3==50){r1=2.;r=r+r1*tt[i];}
if(i3==51){r1=3.;r=r+r1*tt[i];}
if(i3==52){r1=4.;r=r+r1*tt[i];}
if(i3==53){r1=5.;r=r+r1*tt[i];}
if(i3==54){r1=6.;r=r+r1*tt[i];}
if(i3==55){r1=7.;r=r+r1*tt[i];}
if(i3==56){r1=8.;r=r+r1*tt[i];}
if(i3==57){r1=9.;r=r+r1*tt[i];}
if(i3==45){r2=-1.;}
}

for(i=0;i<i_count1-j1-2;i++)
{
i3=buf[i1-i_count1+j1+i+1];
if(i3==48){r1=0.;}
if(i3==49){r1=1.;}
if(i3==50){r1=2.;}
if(i3==51){r1=3.;}
if(i3==52){r1=4.;}
if(i3==53){r1=5.;}
if(i3==54){r1=6.;}
if(i3==55){r1=7.;}
if(i3==56){r1=8.;}
if(i3==57){r1=9.;}
r=r+r1*ttt[i];
}

ds[i2]=r2*r;
//printf("\n %4d %f",i2,ds[i2]);
//getch();

i2=i2+1;


if(i2<n) {goto d_mn2;}		// NEW Sample

//_______END of  Decoding of array ______



//********* DATUM_P ************
//1._____ Reading of array_____
nb=100000;
fread(buf,nb,1,stream_p);

//2._______ Decoding of array ______

i2=0;
i1=0;
p_mn2:
i_count1=0;
p_mn:
ii=buf[i1];if(ii==44) {j1=i_count1;}
ii=buf[i1];if(ii==10) {i1=i1+1;i_count1=i_count1+1;goto p_mn1;}

i1=i1+1;
i_count1=i_count1+1;
goto p_mn;

p_mn1:
//1.				//SAMPLE
i3=buf[i1-i_count1+j1];
//printf("\n %4d %d %d %d %d",i1,i2,i3,i1-i_count1+j1,i_count1);

r2=1.;
r=0.;
for(i=0;i<j1;i++)
{
i3=buf[i1-i_count1+j1-i-1];
//printf("\n %4d %d",i,i3);
//getch();
if(i3==48){r1=0.;r=r+r1*tt[i];}
if(i3==49){r1=1.;r=r+r1*tt[i];}
if(i3==50){r1=2.;r=r+r1*tt[i];}
if(i3==51){r1=3.;r=r+r1*tt[i];}
if(i3==52){r1=4.;r=r+r1*tt[i];}
if(i3==53){r1=5.;r=r+r1*tt[i];}
if(i3==54){r1=6.;r=r+r1*tt[i];}
if(i3==55){r1=7.;r=r+r1*tt[i];}
if(i3==56){r1=8.;r=r+r1*tt[i];}
if(i3==57){r1=9.;r=r+r1*tt[i];}
if(i3==45){r2=-1.;}
}

for(i=0;i<i_count1-j1-2;i++)
{
i3=buf[i1-i_count1+j1+i+1];
if(i3==48){r1=0.;}
if(i3==49){r1=1.;}
if(i3==50){r1=2.;}
if(i3==51){r1=3.;}
if(i3==52){r1=4.;}
if(i3==53){r1=5.;}
if(i3==54){r1=6.;}
if(i3==55){r1=7.;}
if(i3==56){r1=8.;}
if(i3==57){r1=9.;}
r=r+r1*ttt[i];
}

s_p[i2]=r2*r;
//printf("\n %4d %20.18f",i2,s[i2]);
//getch();

i2=i2+1;


if(i2<n) {goto p_mn2;}		// NEW Sample

//_______END of  Decoding of array ______





//********* DATUM_Z ************
//1._____ Reading of array_____
nb=100000;
fread(buf,nb,1,stream_z);

//2._______ Decoding of array ______

i2=0;
i1=0;
z_mn2:
i_count1=0;
z_mn:
ii=buf[i1];if(ii==44) {j1=i_count1;}
ii=buf[i1];if(ii==10) {i1=i1+1;i_count1=i_count1+1;goto z_mn1;}

i1=i1+1;
i_count1=i_count1+1;
goto z_mn;

z_mn1:
//1.				//SAMPLE
i3=buf[i1-i_count1+j1];
//printf("\n %4d %d %d %d %d",i1,i2,i3,i1-i_count1+j1,i_count1);

r2=1.;
r=0.;
for(i=0;i<j1;i++)
{
i3=buf[i1-i_count1+j1-i-1];
//printf("\n %4d %d",i,i3);
//getch();
if(i3==48){r1=0.;r=r+r1*tt[i];}
if(i3==49){r1=1.;r=r+r1*tt[i];}
if(i3==50){r1=2.;r=r+r1*tt[i];}
if(i3==51){r1=3.;r=r+r1*tt[i];}
if(i3==52){r1=4.;r=r+r1*tt[i];}
if(i3==53){r1=5.;r=r+r1*tt[i];}
if(i3==54){r1=6.;r=r+r1*tt[i];}
if(i3==55){r1=7.;r=r+r1*tt[i];}
if(i3==56){r1=8.;r=r+r1*tt[i];}
if(i3==57){r1=9.;r=r+r1*tt[i];}
if(i3==45){r2=-1.;}
}

for(i=0;i<i_count1-j1-2;i++)
{
i3=buf[i1-i_count1+j1+i+1];
if(i3==48){r1=0.;}
if(i3==49){r1=1.;}
if(i3==50){r1=2.;}
if(i3==51){r1=3.;}
if(i3==52){r1=4.;}
if(i3==53){r1=5.;}
if(i3==54){r1=6.;}
if(i3==55){r1=7.;}
if(i3==56){r1=8.;}
if(i3==57){r1=9.;}
r=r+r1*ttt[i];
}

s_z[i2]=r2*r;
//printf("\n %4d %f",i2,s_z[i2]);
//getch();

i2=i2+1;


if(i2<n) {goto z_mn2;}		// NEW Sample

//_______END of  Decoding of array ______



p=0.;
//getch();
//1. __________________Initialization_____________________

c0=a0-z0;
c2=z0;
//c1=-0.915*a0;
c1=-0.9*a0;


ipp=10;
h1=5.0/ipp;
max=10000.;
min1=10000.;
min2=10000.;

omp_set_num_threads(1);
#pragma omp parallel for private(i,i2,i3,i4,i5) firstprivate(min1,min2)
for (i1=0; i1<ipp+2;i1++)
{
	double ka=h1*i1;
  	for (i2=0; i2<ipp+2;i2++)
	{
		double kma=h1*i2;
		for (i3=0; i3<ipp+2;i3++)
		{
			double kz=h1*i3;
        	for (i4=0; i4<ipp+2;i4++)
			{
				double kmz=h1*i4;

				for (i5=0; i5<ipp+2;i5++)
				{
					double k2=h1*i5;
					int i7=1;
					double r7=ds[i7];
//printf("\n  r7= %20.18f i4= %d i5= %d",r7,i4,i5);
//getch();

//2._________________ Runge_Kutta Procedure _________________
					h=0.01;
					double a1=a0;
					double z1=z0;
					double p1=p0;

					double sum=0.;

					for(i=0;i<200000;i++)
					{
						int r8=(int)(i*h);

						double k11=h*(-ka*(p1+a1+c1)*a1+kma*(-a1+z1+c0));
						double k12=h*(-kz*(-a1+z1+c0)*z1+kmz*(-p1-z1+c2));
						double k13=h*(k2*(-p1-z1+c2));

						double k21=h*(-ka*((p1+0.5*k13)+(a1+0.5*k11)+c1)*(a1+0.5*k11)+kma*(-(a1+0.5*k11)+(z1+0.5*k12)+c0));
						double k22=h*(-kz*(-(a1+0.5*k11)+(z1+0.5*k12)+c0)*(z1+0.5*k12)+kmz*(-(p1+0.5*k13)-(z1+0.5*k12)+c2));
						double k23=h*(k2*(-(p1+0.5*k13)-(z1+0.5*k12)+c2));

						double k31=h*(-ka*((p1+0.5*k23)+(a1+0.5*k21)+c1)*(a1+0.5*k21)+kma*(-(a1+0.5*k21)+(z1+0.5*k22)+c0));
						double k32=h*(-kz*(-(a1+0.5*k21)+(z1+0.5*k22)+c0)*(z1+0.5*k22)+kmz*(-(p1+0.5*k23)-(z1+0.5*k22)+c2));
						double k33=h*(k2*(-(p1+0.5*k23)-(z1+0.5*k22)+c2));

						double k41=h*(-ka*((p1+k33)+(a1+k31)+c1)*(a1+k31)+kma*(-(a1+k31)+(z1+k32)+c0));
						double k42=h*(-kz*(-(a1+k31)+(z1+k32)+c0)*(z1+k32)+kmz*(-(p1+k33)-(z1+k32)+c2));
						double k43=h*(k2*(-(p1+k33)-(z1+k32)+c2));

						//#pragma omp critical
						a1=a1+1./6.*(k11+2.*k21+2.*k31+k41);
						z1=z1+1./6.*(k12+2.*k22+2.*k32+k42);
						p1=p1+1./6.*(k13+2.*k23+2.*k33+k43);

//printf("\n  %d r7= %20.18f r7= %f",i,r8,r7);
//getch();

						if(r8==r7)
						{
							//   printf("\n__ i7= %d r7= %f",i7,r7);
							//	getch();
							sum=sum+(s_a[i7]-a1)*(s_a[i7]-a1)+(s_z[i7]-z1)*(s_z[i7]-z1)+(s_p[i7]-p1)*(s_p[i7]-p1);
							//   sum=sum+(s_a[i7]-a1)*(s_a[i7]-a1)+(s_z[i7]-z1)*(s_z[i7]-z1)+(s_p[i7]-p1)*(s_p[i7]-p1);
							//   printf("\n__ sum= %f",sum);
							i7=i7+1;
							r7=ds[i7];
						}//if

					}//i

					if (min1>sum)
					{
					min2=min1;kka1=ka0;kkma1=kma0;kkz1=kz0;kkmz1=kmz0;kk21=k20;
					min1=sum;ka0=ka;kma0=kma;kz0=kz;kmz0=kmz;k20=k2;
					}

				}//i5

			}//i4
			printf("\n__ min2= %f",min2);
			//printf("\n i1= %4d i2= %4d i3= %4d i4= %4d i5= %4d",i1,i2,i3,i4,i5);
			printf("\n__ ka= %f kma= %f kz= %f kmz= %f k2= %f",kka1,kkma1,kkz1,kkmz1,kk21);
			printf("\n__ min1= %f",min1);
			printf("\n__ ka= %f kma= %f kz= %f kmz= %f k2= %f",ka0,kma0,kz0,kmz0,k20);
			printf("\n i1= %4d i2= %4d i3= %4d i4= %4d i5= %4d",i1,i2,i3,i4,i5);
			printf("\n________________________________________________________________");

		}//i3
   }//i2
}//i1


printf("\n___ END___");
//getch();
//getch();
//getch();

fclose(stream_t);
fclose(stream_a);
fclose(stream_p);
fclose(stream_z);

}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
