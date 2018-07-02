#include<stdio.h>
#include<graphics.h>
#include<math.h>
int bgcolor,c;
int sign(float x);
void creategraph()
{
		int gd=DETECT,gm;
		initgraph(&gd,&gm,"C://turboC3/BGI");
}
void drawxy()
{
		int i;
		setbkcolor(bgcolor);
		for(i=0;i<=639;i++)
		{
			putpixel(i,240,15);
			delay(5);
		}
		for(i=0;i<=479;i++)
		{
			putpixel(320,i,15);
			delay(5);
		}
		outtextxy(620,245,"+X");
		outtextxy(10,245,"-X");
		outtextxy(330,20,"+Y");
		outtextxy(330,460,"-Y");
		outtextxy(330,245,"O");
}
void plotpoints(int x[],int y[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		putpixel(320+x[i],240-y[i],c);
		delay(5);
	}
}
void bresenham(int x1,int y1,int x2,int y2)
{
	int x[700],y[700];
	int delx,dely,xx,yy,s1,s2,temp,interchange,e,i;
	delx=abs(x2-x1);
	dely=abs(y2-y1);
	s1=sign(x2-x1);
	s2=sign(y2-y1);
	if(dely>delx)
	{
		temp=dely;
		dely=delx;
		delx=temp;

		interchange=1;
	}
	else
		interchange=0;
	e=2*dely-delx;
	xx=x1;
	yy=y1;
	for(i=0;i<=delx;i++)
	{
		x[i]=xx;
		y[i]=yy;
		while(e>=0)
		{
			if(interchange==1)
				xx=xx+s1;
			else
				yy=yy+s2;
			e=e-2*delx;
		}
		if(interchange==1)
			yy=yy+s2;
		else
			xx=xx+s1;
		e=e+2*dely;
	}
	plotpoints(x,y,delx+1);
}
int sign(float x)
{
	if(x<0)
		return -1;
	else if(x>0)
		return 1;
	else
		return 0;
}
void multiply(double a[3][3],double b[3][3],double c[3][3])
{
	int i,j,k;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			c[i][j]=0;
			for(k=0;k<3;k++)
				c[i][j]=c[i][j]+a[i][k]*b[k][j];
		}
	}
}
void transformation(int x1,int y1, int x2, int y2, int x3, int y3,int nm, int dm,int cc)
{
	double a[3][3],b[3][3],c[3][3],d[3][3],e[3][3],f[3][3];
	double t1[3][3],t2[3][3];
	double sine,cosine;
	int i;
	sine=nm/sqrt(nm*nm+dm*dm);
	cosine=dm/sqrt(nm*nm+dm*dm);
	f[0][0]=x1;
	f[0][1]=x2;
	f[0][2]=x3;
	f[1][0]=y1;
	f[1][1]=y2;
	f[1][2]=y3;
	for(i=0;i<3;i++)
		f[2][i]=1;
	e[0][0]=1;
	e[0][1]=0;
	e[0][2]=0;
	e[1][0]=0;
	e[1][1]=1;
	e[1][2]=-cc;
	e[2][0]=0;
	e[2][1]=0;
	e[2][2]=1;
	d[0][0]=cosine;
	d[0][1]=sine;
	d[0][2]=0;
	d[1][0]=-sine;
	d[1][1]=cosine;
	d[1][2]=0;
	d[2][0]=0;
	d[2][1]=0;
	d[2][2]=1;
	c[0][0]=1;
	c[0][1]=0;
	c[0][2]=0;
	c[1][0]=0;
	c[1][1]=-1;
	c[1][2]=0;
	c[2][0]=0;
	c[2][1]=0;
	c[2][2]=1;
	b[0][0]=cosine;
	b[0][1]=-sine;
	b[0][2]=0;
	b[1][0]=sine;
	b[1][1]=cosine;
	b[1][2]=0;
	b[2][0]=0;
	b[2][1]=0;
	b[2][2]=1;
	a[0][0]=1;
	a[0][1]=0;
	a[0][2]=0;
	a[1][0]=0;
	a[1][1]=1;
	a[1][2]=cc;
	a[2][0]=0;
	a[2][1]=0;
	a[2][2]=1;
	multiply(e,f,t1);
	multiply(d,t1,t2);
	multiply(c,t2,t1);
	multiply(b,t1,t2);
	multiply(a,t2,t1);
	bresenham(t1[0][0],t1[1][0],t1[0][1],t1[1][1]);
	bresenham(t1[0][1],t1[1][1],t1[0][2],t1[1][2]);
	bresenham(t1[0][2],t1[1][2],t1[0][0],t1[1][0]);
}
void drawline(int nm,int dm,int cc)
{
	int i,y=0;
	for(i=-320;i<320;i++)
	{
		y=(nm/dm)*i+cc;
		putpixel(320+i,240-y,c);
	}
}
void main()
{
	int x1,y1,x2,y2,x3,y3,nm,dm,cc;
	printf("\nEnter background colour code");
	scanf("%d",&bgcolor);
	printf("\nEnter line colour code");
	scanf("%d",&c);
	printf("\nEnter x1 of Triangle");
	scanf("%d",&x1);
	printf("\nEnter y1 of Triangle");
	scanf("%d",&y1);
	printf("\nEnter x2 of Triangle");
	scanf("%d",&x2);
	printf("\nEnter y2 of Triangle");
	scanf("%d",&y2);
	printf("\nEnter x3 of Triangle");
	scanf("%d",&x3);
	printf("\nEnter y3 of Triangle");
	scanf("%d",&y3);
	printf("Enter numerator of slope of line");
	scanf("%d",&nm);
	printf("Enter denominator of slope of line");
	scanf("%d",&dm);
	printf("Enter y intercept of line");
	scanf("%d",&cc);
	creategraph();
	drawxy();
	bresenham(x1,y1,x2,y2);
	bresenham(x1,y1,x3,y3);
	bresenham(x3,y3,x2,y2);
	drawline(nm,dm,cc);
	transformation(x1,y1,x2,y2,x3,y3,nm,dm,cc);
	getch();
	closegraph();
}
