#include<stdio.h>
#include<graphics.h>
#include<math.h>
int bgcolor,c;
void creategraph();
void drawxy();
void plotpoints(int x[],int y[],int xc,int yc,int n);
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
void plotpoints(int x[],int y[],int xc,int yc,int n)
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
	int xk,yk,n,i;
	int d;
	double pk;
	xk=0;
	yk=r;
	n=0;
	do
	{
		x[n]=xk;
		y[n]=yk;
		d=(xk+1)*(xk+1)+(yk-1)*(yk-1)-r*r;
		if(d<0)
		{
			pk=(xk+1)*(xk+1)+(yk-.5)*(yk-.5)-r*r;
			if(pk<=0)
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
	} while(yk>=0);
	n--;
	for(i=n+1;i<=2*n;i++)
	{
		x[i]=x[i-n-1];
		y[i]=-y[i-n-1];
	}
	for(i=2*n+1;i<4*n;i++)
	{
		x[i]=-x[i-2*n];
		y[i]=y[i-2*n];
	}
	n=n*4;
	plotpoints(x,y,xc,yc,n);
}
void main()
{
	int xc,yc,r;
	clrscr();
	printf("xc yc r: ");
	scanf("%d %d %d",&xc,&yc,&r);
	printf("bgcolor color: ");
	scanf("%d %d",&bgcolor,&c);
	creategraph();
	drawxy();
	circledraw(xc,yc,r);
	getch();
	closegraph();
}