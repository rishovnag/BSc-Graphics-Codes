/*sine_curve.c: Write a program to plot sin(x) for x=-360 degree to x=+360 degree*/
#include<stdio.h>
#include<graphics.h>
int c,bgcolor;
void draw_xy();
float sine(float x);
void sine_curve(int theta_1,int theta_2);
void main()
{
int theta_1,theta_2;
clrscr();
printf("\nEnter theta_1 in degrees(-360 to 0):");
scanf("%d",&theta_1);
printf("\nEnter theta_2 in degrees(0 to 360):");
scanf("%d",&theta_2);
printf("\nEnter background color code(1-14):");
scanf("%d",&bgcolor);
printf("\nEnter color code of circles(1-14):");
scanf("%d",&c);
/* draw_xy();*/
sine_curve(theta_1,theta_2);
getch();
closegraph();
}
/*void sine_curve(int theta_1,int theta_2) : function to calculate sin(x)*/
float sine(float x)
{
float csin,psin,eps,xrad,fact,px;
int i,sf,n;
xrad=x*3.141593/180;
csin=xrad;
psin=1;
eps=csin-psin;
	if(eps<0)
	eps=-eps;
n=3;
sf=-1;
	while(eps > 1e-07)
	{
	psin=csin;
	fact=1;
	px=1;
		for(i=1;i<=n;i++)
		{
		fact=fact*i;
		px=px*xrad;
		}
	csin=csin+sf*px/fact;
	eps=csin-psin;
		if(eps<0)
		eps=-eps;
	n=n+2;
	sf=-sf;
	}
return csin;
}

/* void sine_curve(int theta_1, int theta_2): function to generate and plot
y=sin(x) for x=theta_1 to x=theta_2 */

void sine_curve(int theta_1, int theta_2)
{
int i,count;
int x[2000],y[2000];
float y1;
count=0;
	for(i=theta_1;i<=theta_2;i++)
	{
		if(i<0)
		y1=-sine(-(float)i);
		else
		y1=sine((float)i);
	x[count]=i/2;
	y[count]=(int)100*y1;
	count++;
	printf("sin(%d)=%7.4f\n",i,y1);
		if((count%20)==0)
		{
		printf("\nPress any key to continue--->");
		getch();
		clrscr();
		}
	}
	getch();
 /*to plot y=sin(x)*/
 draw_xy(); /*to draw x and y axis*/
	for(i=0;i<count;i++)
	putpixel(320+x[i],240-y[i],c);
 }

/* void draw_xy() : Function to display x-axis, y-axis */
void draw_xy()
{
int i,c,c1;
int gd=DETECT,gm;
initgraph(&gd,&gm,"C:\\turboc3\\BGI");
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
