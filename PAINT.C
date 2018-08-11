/*
Go to Options->Linker->Libraries and make sure 'Graphics Library' option is checked.
Find the initgraph() function call in main() and change/verify the location of the 'BGI' directory to yours.
*/

#include<graphics.h>
#include<dos.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
union REGS in,out;
void textDisplay();
void mainLayout();
void colorPallete();
void drawingMenu();
void start();
void initMouse();
void showPointer();
void hidePointer();
void detectClick(int*,int*,int*);
void main(){	int gd=DETECT,gm,x,y,x1,y1,click,temp1,temp2,status=6,color=0,triangle[8];	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");		/*Check this location with your BGI directory location*/	mainLayout();	initMouse();	showPointer();	setcolor(color);	setviewport(0,0,566,435,1);
	while(!kbhit()){		detectClick(&x,&y,&click);		if(click==1){			if(x>=50&&x<=560&&y>=440&&y<=465){				for(x1=50,color=0;x1<=560,color<=15;x1+=32,color++){					if(x>=x1&&x<=x1+30)						setcolor(color);				}			}						if(x>=570&&x<=633&&y>=50&&y<=435){				if(y>=50&&y<=75)					status=1;				if(y>=95&&y<=120)					status=2;				if(y>140&&y<=165)					status=3;				if(y>=185&&y<=210)					status=4;				if(y>=230&&y<=255)					status=5;				if(y>=275&&y<=300)					status=6;				if(y>=320&&y<=345)					status=7;				if(y>=365&&y<=390)					status=9;				if(y>=410&&y<=435)					status=8;			}						temp1=x;			temp2=y;			if(status==6){				hidePointer();				while(click==1){					line(temp1,temp2,x,y);					temp1=x;					temp2=y;					detectClick(&x,&y,&click);				}				showPointer();			}else if(status==9){				setfillstyle(1,15);				while(click==1){					bar(temp1-5,temp2-5,x+5,y+5);					temp1=x;					temp2=y;					detectClick(&x,&y,&click);				}			}						while(click==1)				detectClick(&x,&y,&click);						hidePointer();						if(status==1){				line(temp1,temp2,x,y);			}else if(status==2){				circle(temp1,temp2,sqrt(abs(abs(x-temp1)*abs(x-temp1)+abs(y-temp2)*abs(y-temp2))));			}else if(status==3){				rectangle(temp1,temp2,x,y);			}else if(status==4){				triangle[0]=temp1;				triangle[1]=temp2;				triangle[2]=x+sqrt(abs((abs(temp1-x)*abs(temp1-x)+abs(temp2-y)*abs(temp2-y))/3));				triangle[3]=y;				triangle[4]=abs(x-sqrt(abs((abs(temp1-x)*abs(temp1-x)+abs(temp2-y)*abs(temp2-y))/3)));				triangle[5]=y;				triangle[6]=temp1;				triangle[7]=temp2;				drawpoly(4,triangle);			}else if(status==5){				ellipse(temp1,temp2,0,360,abs(x-temp1),abs(y-temp2));			}else if(status==7){				setfillstyle(1,getcolor());				floodfill(x,y,getcolor());			}else if(status==8){				clearviewport();				status=6;				color=getcolor();				setcolor(15);				setfillstyle(1,15);				rectangle(0,0,566,435);				floodfill(getmaxx()/2,getmaxy()/2,15);				setcolor(color);				setfillstyle(1,color);			}			showPointer();		}	}		closegraph();
}
void colorPallete(){	int x1,x2,color;		for(x1=50,x2=80,color=0;x1<=530,x2<=560,color<=15;x1+=32,x2+=32,color++){		rectangle(x1,440,x2,465);		setfillstyle(SOLID_FILL,color);		floodfill(x1+10,450,WHITE);	}}
void drawingMenu(){	int y1,y2;	int triangle[]={600,190,590,203,610,203,600,190};	int pen[]={608,282,592,294,589,295,590,292,606,280,608,282};	int fill[]={598,324,598,327,595,327,595,340,607,340,607,327,604,327,604,324,598,324};		setcolor(14);		for(y1=50,y2=75;y1<=410,y2<=435;y1+=45,y2+=45){		rectangle(570,y1,633,y2);	}		setlinestyle(0,0,2);	setcolor(9);	line(592,57,608,69);	circle(600,107,8);	rectangle(587,145,614,160);	drawpoly(4,triangle);	ellipse(600,242,0,360,10,6);	setfillstyle(1,9);	fillpoly(6,pen);	setcolor(6);	setfillstyle(1,6);	fillpoly(9,fill);	setfillstyle(1,15);	bar(587,370,614,385);	setcolor(RED);	setlinestyle(0,0,3);	line(593,417,609,430);	line(609,417,593,430);	setlinestyle(0,0,0);	setcolor(15);	setfillstyle(1,15);	rectangle(0,0,566,435);	floodfill(getmaxx()/2,getmaxy()/2,15);	setcolor(15);
}
void textDisplay(){	setcolor(10);	outtextxy(585,78,"Line");	outtextxy(580,123,"Circle");	outtextxy(568,168,"Rectangle");	outtextxy(571,213,"Triangle");	outtextxy(575,258,"Ellipse");	outtextxy(589,303,"Pen");	outtextxy(588,348,"Fill");	outtextxy(582,393,"Erase");	outtextxy(583,440,"Clear");	setcolor(15);
}
void mainLayout(){	start();	colorPallete();	drawingMenu();	textDisplay();
}
void start(){	int color=0;	while(!kbhit()){		setbkcolor(color);		color++;		settextstyle(1,0,2);		outtextxy(getmaxx()/2-30,getmaxy()/2,"PAINT");		settextstyle(0,0,0);		outtextxy(getmaxx()/2-50,getmaxy()/2+40,"Press any key!");		if(color>14)			color=0;		delay(500);	}		setbkcolor(BLACK);	cleardevice();	getch();
}
void initMouse(){	in.x.ax=0;	int86(51,&in,&out);		if(out.x.ax==0){		exit(0);	}
}
void showPointer(){	in.x.ax=1;	int86(51,&in,&out);
}
void hidePointer(){	in.x.ax=2;	int86(51,&in,&out);
}
void detectClick(int* x,int* y,int* click){	in.x.ax=3;		int86(51,&in,&out);		*x=out.x.cx;	*y=out.x.dx;	*click=out.x.bx;
}