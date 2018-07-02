#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<conio.h>
int c, bgcolor;
int sign(float);
void creategraph();
void drawxy();
void plotpoints_br(int x[],int y[],int n);
void bresenham(int x1,int y1, int x2, int y2);
void plotpoints_cir(int x[],int y[],int xc,int yc,int n);
void circledraw(int xc,int yc,int r);
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
	for(i=0;i<479;i++)
	{
		putpixel(320,i,15);
		delay(5);
	}
}
void plotpoints_br(int x[],int y[],int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		putpixel(320+x[i],240-y[i],c);
		delay(5);
	}
}
void bresenham(int x1,int y1, int x2, int y2)
{
	int delx,dely,s1,s2,interchange,temp,xx,yy,i,e;
	int x[700],y[700];
	delx=abs(x2-x1);
	dely=abs(y2-y1);
	s1=sign(x2-x1);
	s2=sign(y2-y1);
	xx=x1;
	yy=y1;
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
	plotpoints_br(x,y,delx+1);
}
void plotpoints_cir(int x[],int y[],int xc,int yc,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		putpixel(320+x[i]+xc,240-y[i]-yc,c);
		delay(5);
	}
}
void circledraw(int xc,int yc,int r)
{
	int x[1200],y[1200];
	int n=0;
	int xk=0;
	int yk=r;
	int i,d;
	double pk=0.0;
	do
	{
		x[n]=xk;
		y[n]=yk;
		d=(xk+1)*(xk+1)+(yk-1)*(yk-1)-r*r;
		if (d<0)
		{
			pk=(xk+1)*(xk+1)+(yk-.5)*(yk-.5)-r*r;
			if(pk<0)
				xk=xk+1;
			else
			{
				xk=xk+1;
				yk=yk-1;
			}
		}
		else if(d>0)
		{
			pk=(xk+.5)*(xk+.5)+(yk-1)*(yk-1)-r*r;
			if(pk<=0)
			{
				xk=xk+1;
				yk=yk-1;
			}
			else
				yk=yk-1;
		}
		else
		{
			xk=xk+1;
			yk=yk-1;
		}
		n++;
	}while(yk>=0);
	n--;
	for(i=n+1;i<2*n;i++)
	{
		x[i]=x[i-n-1];
		y[i]=-y[i-n-1];
	}
	/*for(i=2*n+1;i<4*n;i++)
	{
		x[i]=-x[i-2*n];
		y[i]=y[i-2*n];
	}*/
	n=n*2;
	plotpoints_cir(x,y,xc,yc,n);
 }
 int sign(float x)
 {
	 if(x>0)
		 return 1;
	 else if(x<0)
		 return -1;
	 else
		 return 0;
 }
 void main()
 {
	int x1,y1,r;
	printf("enter centre and radius of first circle ");
	scanf( "%d %d %d",&x1,&y1,&r);
	printf("enter color and bg ");
	scanf("%d %d",&c,&bgcolor);
	creategraph();
	drawxy();
	circledraw(x1,y1,r);
	bresenham(x1,y1+r,x1,y1-r);
	getch();
	closegraph();
}