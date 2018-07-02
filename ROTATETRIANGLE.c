#include<stdio.h>
#include<graphics.h>
#include<math.h>
int bgcolor,c;
int sign(float x);
void creategraph();
void drawxy();
void plotpoints(int x[],int y[],int n);
void multiply(double a[3][3],double b[3][3],double c[3][3]);
void bresenham(int x1,int y1,int x2,int y2);
void rotate(int x1,int y1,int x2,int y2,int x3,int y3,int xr,int yr,float th);
void creategraph()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C://turboc3/BGI");
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
	int delx,dely,s1,s2,temp,interchange,e,xx,yy,i;
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
				xx+=s1;
			else
				yy+=s2;
			e-=2*delx;
		}
		if(interchange==1)
			yy+=s2;
		else
			xx+=s1;
		e+=2*dely;
	}
	plotpoints(x,y,delx+1);
}
void multiply(double a[3][3],double b[3][3],double c[3][3])
{
	int i,j,k;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			c[i][j]=0;
			for(k=0;k<3;k++)
				c[i][j]+=a[i][k]*b[k][j];
		}
}
void rotate(int x1,int y1,int x2,int y2,int x3,int y3,int xr,int yr,float th)
{
	double a[3][3],b[3][3],c[3][3],d[3][3];
	double t1[3][3],t2[3][3],t;
	int i,j;
	d[0][0]=x1;
	d[0][1]=x2;
	d[0][2]=x3;
	d[1][0]=y1;
	d[1][1]=y2;
	d[1][2]=y3;
	for(i=0;i<3;i++)
		d[2][i]=1;
	c[0][0]=1;
	c[0][1]=0;
	c[0][2]=-xr;
	c[1][0]=0;
	c[1][1]=1;
	c[1][2]=-yr;
	c[2][0]=0;
	c[2][1]=0;
	c[2][2]=1;
	t=th*3.1415926/180.0;
	b[0][0]=cos(t);
	b[0][1]=-sin(t);
	b[0][2]=0;
	b[1][0]=sin(t);
	b[1][1]=cos(t);
	b[1][2]=0;
	b[2][0]=0;
	b[2][1]=0;
	b[2][2]=1;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			a[i][j]=c[i][j];
	a[0][2]=-a[0][2];
	a[1][2]=-a[0][2];
	multiply(c,d,t1);
	multiply(b,t1,t2);
	multiply(a,t2,t1);
	bresenham(t1[0][0],t1[1][0],t1[0][1],t1[1][1]);
	bresenham(t1[0][1],t1[1][1],t1[0][2],t1[1][2]);
	bresenham(t1[0][2],t1[1][2],t1[0][0],t1[1][0]);
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
void main()
{
	int x1,y1,x2,y2,x3,y3,xr,yr;
	float th;
	char a[100];
	clrscr();
	printf("x1 y1 x2 y2 x3 y3 xr yr th: ");
	scanf("%d %d %d %d %d %d %d %d %f",&x1,&y1,&x2,&y2,&x3,&y3,&xr,&yr,&th);
	printf("Background Color, color : ");
	scanf("%d %d",&bgcolor,&c);
	creategraph();
	drawxy();
	bresenham(x1,y1,x2,y2);
	bresenham(x2,y2,x3,y3);
	bresenham(x3,y3,x1,y1);
	rotate(x1,y1,x2,y2,x3,y3,xr,yr,th);
	sprintf(a,"A(%d,%d)",x1,y1);
	outtextxy(322+x1,238-y1,a);
	getch();
	closegraph();
}