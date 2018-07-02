/*y=sin(x) x=-360 to 360*/
#include<stdio.h>
#include<graphics.h>
int c,bgcolor;
void draw_xy();
float cos(float x);
float sine(float x);
void tan_curve(int theta_1,int theta_2);
void main()
{
int theta_1,theta_2;
clrscr();
printf("\nEnter theta_1 in degerees(-360 to 0):");
scanf("%d",&theta_1);
printf("\nEnter theta_2 in degerees(-360 to 0):");
scanf("%d",&theta_2);
printf("Enter background color code=");
scanf("%d",&bgcolor);
printf("\nEnter color code of lines(1-14):");
scanf("%d",&c);
/*draw_xy();*/
tan_curve(theta_1,theta_2);
getch();
closegraph();
}
float cos(float x)
{
float ccos,pcos,eps,xrad,fact,px;
int i,sf,n;
xrad=x*3.141593/180;
ccos=1;
pcos=0;
eps=ccos-pcos;
	if(eps<0)
	eps=-eps;
n=2;
sf=-1;
	while(eps > 1e-07)
	{
	pcos=ccos;
	fact=1;
	px=1;
		for(i=1;i<=n;i++)
		{
		fact=fact*i;
		px=px*xrad;
		}
	ccos=ccos+sf*px/fact;
	eps=ccos-pcos;
		if(eps<0)
		eps=-eps;
	n=n+2;
	sf=-sf;
	}
return ccos;
}
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
void tan_curve(int theta_1,int theta_2)
{
int i,count;
int x[2000],y[2000];
float y1,y2,y3,y4;
count=0;
	for(i=theta_1;i<theta_2;i++)
	{
	y1=sine((float)i);
	y2=cos((float)i);
	y3=y1/y2;
	x[count]=i/2;
		if(y3<0)
		y4=-y3;
		else
		y4=y3;
		if(y4>50)
		{
			if(y3<0)
			y[count]=-200;
			else
			y[count]=200;
		}
		else
		y[count]=(int)(y3*100);
	printf("tan(%d)=%7.4f\n",i,y1);
	count++;
		if((count%20)==0)
		{
		printf("\nPress any key to continue--->");
		getch();
		clrscr();
		}
	}
	getch();
	draw_xy();
		for(i=0;i<count;i++)
		putpixel(320+x[i],240-y[i],c);
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
outtextxy(350,25,"y=tan(x)");
}

