/*WAP to draw cosine surve*/
#include<stdio.h>
#include<graphics.h>
int c,bgcolor;
void draw_xy();
float cosine(float x);
void cosine_curve(int theta_1,int theta_2);
void main()
{
 int theta_1,theta_2;
 clrscr();
 printf("\n Enter theta_1 in degree (-360 to 0) :");
 scanf("%d",&theta_1);
 printf("\n Enter theta_2 in degree (0 to 360): ");
 scanf("%d",&theta_2);
 printf(" Enter the background color code (1-14) = ");
 scanf("%d",&bgcolor);
 printf(" Enter color of the line (1-14) = ");
 scanf("%d",&c);
 /*draw_xy();*/
 cosine_curve(theta_1,theta_2);
 getch();
 closegraph();
 }
 /* float sine(float x) : Function to calculate sine(x) */
 float cosine(float x)
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
  /* void cosine_curve(int theta_1, int theta_2): Function to generate and plot y=sin(x)
  for x=theta_1 to x=theta_2 */
   void cosine_curve(int theta_1,int theta_2)
   {
    int i,count;
    int x[2000],y[2000];
    float y1;
    count =0;
	for(i=theta_1;i<=theta_2;i++)
	 {
	  y1=cosine((float)i);
	 x[count]=i/2;
	 y[count]=(int)100*y1;
	 count++;
		printf("cos(%d) = %7.4f \n",i,y1);
			if((count%20)==0)
			{
			printf("\n Press any key to continue --->");
			getch();
			clrscr();
			}
	 }
	 /* To plot y=sin(x)*/
	 draw_xy(); /*To draw a and y axis*/
	      for(i=0;i<count;i++)
	      putpixel(320+x[i],240-y[i],c);
	 }
	/* To draw_xy() : Function to draw x-axis and y-axis */
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