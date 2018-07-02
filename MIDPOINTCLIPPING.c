/*circle_c.c: Write a program to implement
mid point subdivision clipping algorithm on a */
#include<stdio.h>
#include<graphics.h>
#include<math.h>
int c,bgcolor;
int xL,xR,yB,yT;
void draw_xy();
void draw_window();/*to draw clipping window*/
void line_draw(int x1,int y1,int x2,int y2);
int bresenham(int x1,int y1,int x2,int y2,int x[],int y[]);
int sign(int x);
void plot_line(int x[],int y[],int n);
void mid_point(int x1,int y1,int x2,int y2);
int bit_code(int x,int y);
int bit_and(int x1,int y1,int x2,int y2);
void main()
{
int x1,y1,x2,y2;
clrscr();
printf("\nEnter x co-ordinate of point P1:");
scanf("%d",&x1);
printf("\nEnter y co-ordinate of point P1:");
scanf("%d",&y1);
printf("\nEnter x co-ordinate of point P2:");
scanf("%d",&x2);
printf("\nEnter y co-ordinate of point P2:");
scanf("%d",&y2);
printf("\nEnter xL of viewing window:");
scanf("%d",&xL);
printf("\nEnter xR of viewing window:");
scanf("%d",&xR);
printf("\nEnter yB of viewing window:");
scanf("%d",&yB);
printf("\nEnter yT of viewing window:");
scanf("%d",&yT);
printf("Enter background color code=");
scanf("%d",&bgcolor);
printf("\nEnter color code of lines(1-14):");
scanf("%d",&c);
draw_xy();
draw_window();
mid_point(x1,y1,x2,y2);
getch();
closegraph();
}
int bit_code(int x,int y)
{
int bc;
bc=0;
	if(x<xL || x>xR || y<yB || y>yT)
	bc=1;
return bc;
}
int bit_and(int x1,int y1,int x2,int y2)
{
int bit_p1[5],bit_p2[5];
int i,flag;
/*to set bit codes to 0 to all array elements*/
	for(i=1;i<5;i++)
	{
	bit_p1[i]=0;
	bit_p2[i]=0;
	}
/*to calculate bit of point p1*/
	if(x1<xL)
	bit_p1[1]=1;
	if(x1>xR)
	bit_p1[2]=1;
	if(y1<yB)
	bit_p1[3]=1;
	if(y1>yT)
	bit_p1[4]=1;
/*to calculate bit of point p2*/
	if(x2<xL)
	bit_p2[1]=1;
	if(x2>xR)
	bit_p2[2]=1;
	if(y2<yB)
	bit_p2[3]=1;
	if(y2>yT)
	bit_p2[4]=1;
/*to calculate bit_wise & operation of two bit codes*/
	flag=0;
	for(i=1;i<5;i++)
	{
	flag=bit_p1[i] & bit_p2[i];
		if(flag==1)
		break;
	}
return flag;
}
void draw_window()
{
int i,c1;
/*to draw line from (xL,yB) to (xR,yB)*/
c1=15;
	for(i=xL;i<=xR;i++)
	{
	putpixel(320+i,240-yB,c1);
	delay(5);
	}
/*to draw line from (xR,yB) to (xR,yT)*/
	for(i=yB;i<=yT;i++)
	{
	putpixel(320+xR,240-i,c1);
	delay(5);
	}
/*to draw line from (xR,yT) to (xL,yT)*/
	for(i=xR;i>=xL;i--)
	{
	putpixel(320+i,240-yT,c1);
	delay(5);
	}
/*to draw line from (xL,yT) to (xL,yB)*/
	for(i=yT;i>=yB;i--)
	{
	putpixel(320+xL,240-i,c1);
	delay(5);
	}
outtextxy(322+xL,242-yB,"A");
outtextxy(322+xR,242-yB,"B");
outtextxy(322+xR,242-yT,"C");
outtextxy(322+xL,242-yT,"D");
}
void mid_point(int x1,int y1,int x2,int y2)
{
int xm,ym;
int xx1,yy1,xx2,yy2;
int p1x,p1y,p2x,p2y;
int b1,b2;
char a[80];
b1=bit_code(x1,y1);
b2=bit_code(x2,y2);
	if(b1==0 || b2==0)
	{
	outtextxy(200,80,"Clipping not possible");
	getch();
	return;
	}
b1=bit_and(x1,y1,x2,y2);
	if(b1!=0)
	{
	outtextxy(200,80,"Clipping not possible");
	getch();
	return;
	}
xm=floor((x1+x2)/2);
ym=floor((y1+y2)/2);
b1=bit_code(xm,ym);
	if(b1!=0)
	{
	outtextxy(200,80,"Clipping not possible");
	getch();
	return;
	}
/*mid point subdivision algo starts*/
/* choose p1 and pm*/
xx1=x1;
yy1=y1;
xx2=xm;
yy2=ym;
p1x=0;
p1y=0;
	do
	{
	xm=floor((xx1+xx2)/2);
	ym=floor((yy1+yy2)/2);
	b1=bit_code(xm,ym);
		if(b1==0)
		{
		xx2=xm;
		yy2=ym;
		}
		else
		{
		xx1=xm;
		yy2=ym;
		}
		if(xm==xL || xm==xR)
		{
		p1x=xm;
		p1y=ym;
		break;
		}
		if(ym==yB || ym==yT)
		{
		p1x=xm;
		p1y=ym;
		break;
		}
	}while(1);
/* choose pm and p2*/
xx1=xm;
yy1=ym;
xx2=x2;
yy2=y2;
p2x=0;
p2y=0;
	do
	{
	xm=floor((xx1+xx2)/2);
	ym=floor((yy1+yy2)/2);
	b1=bit_code(xm,ym);
		if(b1==0)
		{
		xx1=xm;
		yy1=ym;
		}
		else
		{
		xx2=xm;
		yy2=ym;
		}
		if(xm==xL || xm==xR)
		{
		p2x=xm;
		p2y=ym;
		break;
		}
		if(ym==yB || ym==yT)
		{
		p2x=xm;
		p2y=ym;
		break;
		}
	}while(1);
/*to draw line from (x1,y1) to (p1x,p1y)*/
	line_draw(x1,y1,p1x,p1y);
/*to draw line from (p1x,p1y) to (p2x,p2y)*/
	line_draw(p1x,p1y,p2x,p2y);
/*to draw line from (p2x,p2y) to (x2,y2)*/
	line_draw(p2x,p2y,x2,y2);
	outtextxy(322+x1,242-y1,"P1");
	outtextxy(322+x2,242-y2,"P2");
	sprintf(a,"(%d,%d)",p1x,p1y);
	outtextxy(322+p1x,242-p1y,a);
	sprintf(a,"(%d,%d)",p2x,p2y);
	outtextxy(322+p2x,242-p2y,a);
 }

/* void draw_xy() : Function to display x-axis, y-axis */
void draw_xy()
{
int i,c,c1;
int gd=DETECT,gm;
initgraph(&gd,&gm,"C://turboc3//BGI");
c=15;
/* To draw x-axis */
	for(i=0;i<=639;i++)
	{
	putpixel(i,240,c);
	delay(2);
	}
/* To draw y-axis */
	for(i=0;i<=479;i++)
	{
	putpixel(320,i,c);
	delay(2);
	}
setbkcolor(bgcolor);
outtextxy(620,245,"+X");
outtextxy(10,245,"-X");
outtextxy(330,20,"+Y");
outtextxy(330,460,"-Y");
outtextxy(330,245,"O");
}

/* void plot_xy(int x[],int y[],int xc,int yc,int n): Function to draw circle*/
void plot_xy(int x[],int y[],int xc,int yc,int n)
{
int i;
char a[80];
	for(i=1;i<=n;i++)
	{
	putpixel(x[i]+320+xc,240-y[i]-yc,c);
	delay(10);
	}
sprintf(a,"C(%d,%d)",xc,yc);
outtextxy(xc+320,240-yc,a);
}

	/*void line_draw(int x1,int y1,int x2,int y2) : Function to draw
	aline from (x1,y1) to (x2,y2)*/
	void line_draw(int x1,int y1,int x2,int y2)
	{
	int x[700],y[700];
	int n;
	n=bresenham(x1,y1,x2,y2,x,y);
	plot_line(x,y,n);
	}


       //int bresenham(int x1,int y1,int x2,int y2,int x[],int y[]):
       //Function to generate all points using Generalized Bresenham algorithm

	int bresenham(int x1,int y1,int x2,int y2,int x[],int y[])
	{
	int delx,dely,s1,s2;
	int interchange,temp;
	int xx,yy;
	int e,i;
	delx=abs(x2-x1);
	dely=abs(y2-y1);
	s1=sign(x2-x1);
	s2=sign(y2-y1);
	/*To Calculate value of interchange*/
		if(dely>delx)
		{temp=dely;
		dely=delx;
		delx=temp;
		interchange=1;
		}
		else
		interchange=0;
	xx=x1;
	yy=y1;
	e=2*dely-delx;
	//To generate all points
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
	return delx;
	}

	void plot_line(int x[],int y[],int n)
	{
	int i;
	for(i=0;i<=n;i++)
	{
	putpixel(320+x[i],240-y[i],c);
	delay(10);
	}
	}

	//int sign(int x) : Function to return sign of x
	int sign(int x)
	{
		if(x>0)
		return 1;
		else if(x==0)
		return 0;
		else
		return -1;
	}
