#include <iostream>
#include <winbgim.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <cstdlib>
using namespace std;
#define 	MINX 		20
#define 	MINY 		20
#define 	MAXX 		420
#define 	MAXY 		220
#define 	BACKGROUND	15
struct Point {
	int x,y,x0,y0;
};

int level; // di nhanh hay di cham 
bool endGame; // Luu trang thai game
int snakeLength; // Do dai ran
Point snake[100]; // Ran
Point direction; // Huong di
Point food; // Do an
const int DIRECTION = 10; // Khoang cach 1 lan di
char* score_str = new char[20];// chuyen score sang string

void showTextBackground(int x,int y,string st,int color){    //ham ve nen
	char *str=new char[st.size()+1];
    for(int i=0; i<st.size(); i++){
      str[i]=st[i];
      str[st.size()]='\0';
  }
	int bks = getbkcolor();
	setbkcolor(color);
	outtextxy(x,y,str);
	delay(200);
	setbkcolor(bks);
}
void showText(int x,int y,string st){    //ham ve chu
	char *str=new char[st.size()+1];
    for(int i=0; i<st.size(); i++){
      str[i]=st[i];
      str[st.size()]='\0';
  }
	int c = getcolor();
	int color = 15;
	setcolor(color);
	outtextxy(x+3,y,str);
	setcolor(c);
	delay(50);
}
bool checkPoint (){     //kiem tra food co trung snake khong
	for (int i = 0;i < snakeLength;i++){
		if (food.x == snake[i].x && food.y == snake[i].y)
		return false;
	}
	return true;
}
void initGame(){         //ve nen game
	setbkcolor (15);
	cleardevice ();
	setwindowtitle ("SNAKE_GAMEPLAY");
	endGame = false;
	setfillstyle (1,0); 
//ve khung gameplay
	bar (MINX,MINY,MAXX,MINY+5); 
	bar (MAXX,MINY,MAXX-5,MAXY);
	bar (MAXX,MAXY,MINX,MAXY-5);
	bar (MINX,MINY,MINX+5,MAXY); 
//ve cac huong dan
    setcolor (0);
    int bki = getbkcolor();
    setfillstyle (SOLID_FILL,0);
int a[] = {15,350,30,350,30,345,50,355,30,365,30,360,15,360,15,350};
    fillpoly (8,a); 
    settextstyle (4,0,3); 
	outtextxy (70,340,"Right");
int b[] = {15,410,30,400,30,405,45,405,45,415,30,415,30,420,15,410};
    fillpoly (8,b);
	outtextxy (70,400,"Left");
int c[] = {235,370,235,355,230,355,240,340,250,355,245,355,245,370,235,370};
	fillpoly (8,c);
	outtextxy (265,340,"Up");
int d[] = {235,400,235,415,230,415,240,430,250,415,245,415,245,400,235,400};
	fillpoly (8,d);
	outtextxy (265,400,"Down");
bar (50,450,170,480);
        setcolor (15);
	settextstyle(1,0,1);
	setbkcolor(0);
	outtextxy(60,455,"SPACE");
	setbkcolor(bki);
        setcolor(0);
	settextstyle (4,0,3);
	outtextxy(200,450,"Pause/Resum");
bar (50,500,170,530);
        setcolor (15);
    settextstyle(1,0,1);
	setbkcolor(0);
	outtextxy(80,505,"ESC");
	setbkcolor(bki);
	    setcolor(0);
    settextstyle (4,0,3);
	outtextxy(200,500,"End Game");
//tao snake
	snake[0].x = 60;snake[0].y = 50;
	snake[1].x = 50;snake[1].y = 50;
	snake[2].x = 40;snake[2].y = 50;
	snakeLength = 3;
	setfillstyle (1,BACKGROUND);
bar (25,25,415,215);
	direction.x = 10;direction.y = 0;
	setcolor (2);
	srand ( time(NULL));
//tao food
    do{
        food.x = (rand() % 39 + 3)*10;
    	food.y = (rand() % 19 + 3)*10;
	}while (checkPoint() == false);
}
void drawPoint (int x,int y,int r){     //ve diem tao snake vaa food
	circle (x,y,r);
	floodfill (x,y,getcolor());
}
void drawSnake (){  //ve snake
	setfillstyle (1,10);
	int count = 0;
	for (int i = 0;count < snakeLength;i++){
			drawPoint(snake[i].x,snake[i].y,5);
			count++;
		}
	//xoa diem khi snake di
	int xs = getcolor();
	setfillstyle (1,BACKGROUND);
	drawPoint(snake[snakeLength-1].x0,snake[snakeLength-1].y0,5);
	setcolor (BACKGROUND);
	circle (snake[snakeLength-1].x0,snake[snakeLength-1].y0,5);
	setcolor(xs);
	setfillstyle (1,5);
}
void drawFood (){   //ve food
	int xf = getcolor();
		setcolor(12);
		setfillstyle (SOLID_FILL, 12);
		drawPoint(food.x, food.y,5);
	setcolor(xf);
	setfillstyle (1,BACKGROUND);
}
void drawGame (){ //ve game
	drawSnake();
	drawFood();
	int xg = getcolor ();
	setcolor (2);
	sprintf(score_str,"%d",snakeLength*level*10-level*30);    //show score
    settextstyle(4,0,3); 
    outtextxy(450,20,"SCORE:");
    setcolor(12);
    outtextxy(600,20,score_str);
	setcolor (xg);
}
void modern(){   //che do co tuong     
	for (int i = 0;i < snakeLength;i++){
		if (i == 0){
			snake[0].x0 = snake[0].x;snake[0].y0 = snake[0].y;
			snake[0].x += direction.x;
			snake[0].y += direction.y;
		}
		else {
			snake[i].x0 = snake[i].x;snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0;snake[i].y = snake[i-1].y0;
		}
		if (snake[0].x < MINX+5 || snake[0].y < MINY+5 || snake[0].x > MAXX-5 || snake[0].y > MAXY - 5 ) //cham tuong
			endGame = true;
		if (i != 0 && snake[0].x == snake[i].x && snake[0].y == snake[i].y)	 endGame = true; //can than
	}
	if (snake[0].x == food.x && snake[0].y == food.y){
		snake[snakeLength].x = snake[snakeLength-1].x0;snake[snakeLength].y = snake[snakeLength-1].y0;
	    snakeLength++;
	    
		//tao food moi khi ran an
		srand ( time(NULL));
		do{
        	food.x = (rand() % 39 + 3)*10;
    		food.y = (rand() % 19 + 3)*10;
		}while (checkPoint() == false);
	}
}
void classic(){   //che do xuyen tuong   
    for (int i = 0; i < snakeLength; i++) {
        if (i == 0) {
            snake[0].x0 = snake[0].x;snake[0].y0 = snake[0].y;
			snake[0].x += direction.x;
			snake[0].y += direction.y;
        }else{
            snake[i].x0 = snake[i].x;snake[i].y0 = snake[i].y;
			snake[i].x = snake[i-1].x0;snake[i].y = snake[i-1].y0;
        }
        //xuyen qua ben doi dien
        if (snake[i].x >= MAXX) snake[i].x = MINX + 10; 
        if (snake[i].x <= MINX) snake[i].x = MAXX - 10;
        if (snake[i].y >= MAXY) snake[i].y = MINY + 10;
        if (snake[i].y <= MINY) snake[i].y = MAXY - 10;
         
        if (i != 0 && (snake[0].x == snake[i].x && snake[0].y == snake[i].y)) endGame = true; //can than
    }
    if (snake[0].x == food.x && snake[0].y == food.y){
		snake[snakeLength].x = snake[snakeLength-1].x0;snake[snakeLength].y = snake[snakeLength-1].y0;
		snakeLength++;
		
		//tao food moi khi ran an
		srand ( time(NULL));
        do{
        	food.x = (rand() % 39 + 3)*10;
    		food.y = (rand() % 19 + 3)*10;
		}while (checkPoint() == false);
	}
}
void changeDirecton (int k){  //dieu khien 
	switch(k){
                case 80: //len 
                    if (direction.y != -DIRECTION) {
            			direction.y = DIRECTION; direction.x = 0;
        			}
                    break;
                case 72: //xuong 
                	if (direction.y != DIRECTION) {
            			direction.y = -DIRECTION; direction.x = 0;
        			}
                   break;
                case 77: //phai 
                    if (direction.x != -DIRECTION) {
            			direction.x = DIRECTION; direction.y = 0;
        			}
                    break;
                case 75: //trai 
                    if (direction.x != DIRECTION) {
            			direction.x = -DIRECTION; direction.y = 0;
        			}
                    break;
                case 27: //thoat game
                	endGame = true;
					break;
    }
}
void mainLoop (void (*xxx)()){  //tam dung game
	int x = getcolor();
	if (!kbhit()){
		xxx();
	}
	else{
		char ch;
        ch = getch();
		if (ch == -32) ch = getch();
		if ( ch == 32){
			setcolor(0);
			outtextxy (100,100,"Game Pause");
			setcolor(x);
			ch = getch();
			while (ch != 32){
				ch = getch();
				delay(0);
			}
			setcolor (BACKGROUND);
			outtextxy (100,100,"Game Pause");
			setcolor (x);
			delay(1000);
		}
        changeDirecton(ch);
        mainLoop (xxx);
    }
}
void run (){    //chay game
	initwindow (800,600); //kich thuoc man hinh do hoa (x,y)
	
	x1: //nhãn--menu
	int bk = getbkcolor();
	cleardevice();
	setbkcolor(0);
	cleardevice(); 
	clearmouseclick(WM_LBUTTONDOWN);
	while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 200 || mousey() > 465 || mousey() < 190 || mousex() > 580 ){
		settextstyle(1,0,6); 
		setcolor (10);
		outtextxy(120,70,"GAME MENU"); 
		settextstyle(10,0,5);
		showText(300,200,"NEW GAME");
		showText(300,340,"QUIT GAME");
	
	}
	clearmouseclick(WM_LBUTTONDOWN);
	if (mousey() <= 255){
		showTextBackground(220,200,"NEW GAME",15);
		x2: //nhãn--chon che do
		setbkcolor(0);
		cleardevice();
		int nameFunction; //che do
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 290 || mousex() > 520 || mousey() < 240 || mousey() > 400){
			settextstyle(1,0,6);setcolor(10);
			outtextxy (140,150,"GAME TYPE");
			setcolor(15);settextstyle(1,0,4);
			showTextBackground(270,250,"CLASSIC",0);
			showTextBackground (270,350,"MODERN",0);
		}
		if (ismouseclick(WM_LBUTTONDOWN) && mousex() >= 240 && mousex() <= 500 && mousey() >= 240 && mousey() <= 400){
			if(mousey() <= 300) nameFunction = 1; //classic
			else nameFunction = 2; //morden
		}
		setbkcolor(0);
		cleardevice();
		setcolor(4);settextstyle(4,0,3);
		outtextxy(10,310,"YOUR CHOICE :");
		settextstyle (4,0,6);
		setcolor (10);
		outtextxy (150,200,"LEVEL 1 - 5");
		setcolor(4);settextstyle(4,0,3);
		outtextxy(10,310,"YOUR CHOICE :");
		int xx = 330;
		char str1[2];
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN) || mousex() < 300 || mousex() > 790 || mousey() < 280 || mousey() > 350) 
		for(int i = 1;i <= 5;i++){
			sprintf(str1,"%d",i);
			settextstyle(4,0,4);
			showTextBackground(xx,300,str1,0);
			xx+= 100;
		}
		if (ismouseclick(WM_LBUTTONDOWN) && mousex() >= 300 && mousex() <= 790 && mousey() >= 280 && mousey() <= 350){
			if(mousex() <= 390) level = 1;
			else if(mousex() <= 490) level = 2;
			else if(mousex() <= 590) level = 3;
			else if(mousex() <= 690) level = 4;
			else level = 5;
		}
		initGame();
		while (!endGame){
			//change delay folow level (thay doi toc do chay cua ran)
		delay (250 - (level-1)*40);
	    (nameFunction == 1) ? mainLoop(classic):mainLoop(modern);
		drawGame();
	}
		settextstyle (1,0,4);
		setcolor (0);
		outtextxy (100,110,"GAME OVER!");
		setcolor (8);
		settextstyle (1,0,2);
		outtextxy (100,160,"Your Score : ");
		setcolor(12);
		outtextxy (300,160,score_str);
		setcolor(10);settextstyle(4,0,5);
		outtextxy (100,200,"Play Again ?");
		settextstyle(4,0,3);
		setcolor(1);
		clearmouseclick(WM_LBUTTONDOWN);
		while (!ismouseclick(WM_LBUTTONDOWN)){
			showTextBackground(150,270,"YES",12);
			showTextBackground(300,270,"NO",7);
		}
		if(ismouseclick(WM_LBUTTONDOWN)){
			if (mousex() >= 140 && mousex() <= 230 && mousey() >= 260 && mousey() <= 310){
				showTextBackground(150,270,"YES",7);
				delay(100);
				goto x2; //nhay den nhãn x2
			}
			else if(mousex() >= 290 && mousex() <= 360 && mousey() >= 260 && mousey() <= 310){
				showTextBackground(300,270,"NO",12);
				delay(100);
				goto x1; //nhay den nhãn x1
			}
        	}
    	}
	    else if(mousey() <= 395){
			showTextBackground (220,340,"QUIT GAME",15);
			exit(0);
		}
}
int main (){
	run();
	delete score_str; //giai phong bo nho con tro
	getch();
	closegraph (); //ket thuc che do do hoa
    return 0;
}
