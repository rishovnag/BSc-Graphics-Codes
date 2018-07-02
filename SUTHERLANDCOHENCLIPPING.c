/*circle_c.c: Write a program to implement
sutherland cohen clipping algorithm on a */
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
void sutherland(int x1,int y1,int x2,int y2);
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
sutherland(x1,y1,x2,y2);
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
void sutherland(int x1,int y1,int x2,int y2)
{

int xx1,yy1,xx2,yy2;
int px1,py1,px2,py2,px3,py3,px4,py4;
int ppx1,ppy1,ppx2,ppy2;
int flag1,flag2,flag3,flag4;
float m; /*m= slope of the intersecting line*/
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
/*sutherland-cohen algorithm starts*/
m=(float)(y2-y1)/(x2-x1);
	flag1=flag2=flag3=flag4=1;
	/*case-1: to find intersection at x=xL*/
	yy1=m*(xL-x1)+y1;
		if(yy1<yB || yy1>yT)
		{
		px1=xL;
		py1=yy1;
		flag1=0;
		}
		else
		{
		px1=xL;
		py1=yy1;
		}
	  /*case-2: to find intersection at x=xR*/
	yy1=m*(xR-x1)+y1;
		if(yy1<yB || yy1>yT)
		{
		px2=xR;
		py2=yy1;
		flag2=0;
		}
		else
		{
		px2=xR;
		py2=yy1;
		}
	 /*case-3: to find intersection at y=yB*/
	xx1=x1+1.0/m*(yB-y1);
		if(xx1<xL || xx1>xR)
		{
		px3=xx1;
		py3=yB;
		flag3=0;
		}
		else
		{
		px3=xx1;
		py3=yB;
		}
	  /*case-4: to find intersection at y=yT*/
	xx1=x1+1.0/m*(yT-y1);
		if(xx1<xL || xx1>xR)
		{
		px4=xx1;
		py4=yT;
		flag4=0;
		}
		else
		{
		px4=xx1;
		py4=yT;
		}

	 /* to test whether the intersecting points are valid or not */
		if(flag1==0 && flag2==0 && flag3==0 && flag4==0)
		{
		outtextxy(250,30,"**no valid intersection point.**");
		getch();
		return;
		}
		if(flag1==1 && flag2==1)
		{
		ppx1=px1;
		ppy1=py1;
		ppx2=px2;
		ppy2=py2;
		}
		else if(flag1==1 && flag3==1)
		{
		ppx1=px1;
		ppy1=py1;
		ppx2=px3;
		ppy2=py3;
		}
		else if(flag1==1 && flag4==1)
		{
		ppx1=px1;
		ppy1=py1;
		ppx2=px4;
		ppy2=py4;
		}
		else if(flag2==1 && flag3==1)
		{
		ppx1=px2;
		ppy1=py2;
		ppx2=px3;
		ppy2=py3;
		}
		else if(flag2==1 && flag4==1)
		{
		ppx1=px2;
		ppy1=py2;
		ppx2=px4;
		ppy2=py4;
		}
		else if(flag3==1 && flag4==1)
		{
		ppx1=px3;
		ppy1=py3;
		ppx2=px4;
		ppy2=py4;
		}
   /* to draw line from (x1,y1) to (ppx1,ppy1) */
       line_draw(x1,y1,ppx1,ppy1);
   /* to draw line from (ppx1,ppy1) to (ppx2,ppy2) */
       line_draw(ppx1,ppy1,ppx2,ppy2);
   /*to draw line from (ppx2,ppy2) to (x2,y2) */
	line_draw(ppx2,ppy2,x2,y2);
	outtextxy(322+x1,242-y1,"P1");
	outtextxy(322+x2,242-y2,"P2");
	sprintf(a,"(%d,%d)",ppx1,ppy1);
	outtextxy(322+ppx1,242-ppy1,a);
	sprintf(a,"(%d,%d)",ppx2,ppy2);
	outtextxy(322+ppx2,242-ppy2,a);
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
