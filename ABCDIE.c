#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <Windows.h>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
HANDLE wHnd;
HANDLE rHnd;
struct enemystruct {char name [20]; int hp; int atk; int armor;};
struct enemystruct e [26] = {
{"Alpha", 100,60, 10},
{"Beta", 300, 110, 40},
{"Gamma", 300,110,40},
{"Delta", 300,110,40},
{"Epsilon", 300, 110, 40},
{"Zeta", 300, 110, 40},
{"Theta", 320, 110,40},
{"Iota", 150,65, 10},
{"Kappa", 350, 115, 40},
{"Lambda", 350,115,40},
{"Mu", 350,115,40},
{"Nu", 350, 115, 40},
{"Xi", 350, 115, 40},
{"Omicron", 370, 115,40},
{"Rho", 180,70, 10},
{"Sigma", 380, 120, 40},
{"Tau", 380,120,40},
{"Upsilon", 380,120,40},
{"Phi", 380, 120, 40},
{"Chi", 380, 120, 40},
{"Omega", 400, 120,40},
{"Physics Teacher", 410,130,40},//21
{"Geography Teacher", 410,130,40},//22
{"History Teacher", 410, 130, 40},//23
{"Maths Teacher", 410, 130, 40},//24
{"Greek Master", 410, 130,40}};//25
struct weaponstruct {char name [15]; int dmg;};
struct weaponstruct w [4] = {
{"Pencil", 50},
{"Pen", 60},
{"Steel pen", 70},
{"Indelible Pen", 80}};
void cMod();
void pressenter ();
void load();
void gotoxy(int, int);
void battle (int m,int ehp,int eatk,int earmor,int pot,int hp,int* newhp,int* newpot,int maxhp,int atk,int armor,int lvl);
void callmap1(int lvl,int* nhp,int* newlvl);
void callmap2(int lvl,int* nhp,int* newlvl);
void callmap3(int lvl,int* nhp,int* newlvl);
void callmap4(int pot,int left,int right,int next,int hp,int atk,int* newlvl,int* newx,int* newy,int* newxA,int* newyA,int* npot,int* newright,int* newleft,int* nhp,int* newatk,int* newnext);
void callmap4a(int lvl,int x,int xA,int y,int yA,int pot,int right,int left,int next,int h,int atk,int* newlvl,int* npot,int* newright,int* newleft,int* nhp,int* newatk,int* newnext);
void map(int lvl);
void lastmap(int lvl);
int quiz(int m,int pot,int hp,int atk,int armor,int lvl);
void type(char *s);
void intro();
void intro2();
void intro3();
void intro4();
void outro();
void castle();
void start();
void chest(int lvl);
void HTP(int hp,int lvl);
void letter();
char choose (char cho,int m,int pot,int hp,int atk,int armor,int lvl);
void gameover();
void hideCursor();
int main(){	

	cMod();
	
	do{
		
	    int lvl=0;
	    system("cls");
   		load();
		start();
		load();
		intro();
		map(lvl);
			lvl=1;
			chest(lvl);
			system("COLOR 0D");
			load();
			intro2();
			map(lvl);
				lvl=2;
				chest(lvl);
				system("COLOR 0B");
				load();
				intro3();
				map(lvl);
					lvl=3;
					system("COLOR 0C");
					chest(lvl);
					load();
					intro4();
					castle();
					lastmap(lvl);
					load();
					system("COLOR 0E");
					outro();
					system("cls");
					gotoxy(15,14);
				 	type("THANKS FOR PLAYING");
				 	sleep(5);
					// image for THE END - THANKS FOR PLAYING
					//CREDITS
	}while(1==1);
	system("PAUSE");
	
	return 0;
}	

void cMod(){
	hideCursor();
	system("COLOR 0A");
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTitle("FattyJr's Big Adventure");
    SMALL_RECT windowSize = {0, 0, 85, 30};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}

void hideCursor(){
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void callmap4(int pot,int left,int right,int next,int hp,int atk,int* newlvl,int* newx,int* newy,int* newxA,int* newyA,int* npot,int* newright,int* newleft,int* nhp,int* newatk,int* newnext){			system("cls");
	system("COLOR 0C");
	system("cls");
	char c,a,p;
	int maxhp=120, armor=60,bonus,button,lvl=3,ehp,eatk,earmor,newhp,newpot;
	int i=0,j=0,m,q=0,t,step;
	int cho=0;
	int x = 18,y = 26,xA=25,yA=18,lastx=18 ,lasty=26;
	boolean filesOpened = TRUE;
	boolean exit = FALSE;
	char map1[26][52];
	maxhp+=(maxhp*0.1-2);armor+=(armor*0.1-1);
	printf("LVL:%d \t HP:%d\t Weapon:%s \t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
	FILE *fp = NULL;
	fp=fopen("BIN/MAP_4.TXT","r");
	if (fp==NULL) {	
		perror("file not found");
		filesOpened = FALSE;
	}else{
		for(i=0;i<26;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(fp);
				map1[i][j]=a;
			}
		}
		fclose(fp);
		map1[21][18]='.';
		map1[16][23]='.';
		map1[14][33]='.';
		map1[11][20]='.';
		map1[ 5][25]='.';
	}		
	if(filesOpened){
		if(next>0){
			map1[16][19]=' ';
			map1[17][19]='?';
		}
		if(next>1){
			map1[16][31]=' ';
			map1[17][31]='?';
		}
		if(next>2){
			map1[9][26]=' ';
			map1[10][26]='?';
		}
		if(next>3){
			map1[7][19]=' ';
			map1[8][19]='?';
		}
			
		for(i=0;i<26;++i){	
			for(j=0;j<52;++j){	
				printf("%c",map1[i][j]);
			}
		}
		i=0,j=0,step=0;
		
		while(next!=5 && !exit){	
			q,i,j,step;
			int flag;
			if(q==1){		
				if (flag!=0){
					step=0;
					flag=0;
				}	
				if(step==0){
					gotoxy(lastx, lasty);
					printf(" ");
					gotoxy(x,y);
			   		printf("@");
				}else{
					gotoxy(lastx, lasty);
					printf("%c",176);
					gotoxy(x,y);
				    printf("@");
				}
			    if((step==22)&&(map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]=='_')){
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i){
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
							map1[xA-1][yA]=' ';
						}
					}
					q=0;
					step=0;
					flag=1;
					gotoxy(x,y);
	    			printf("@");
				}else 
				if((map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]!=' ')){	
					gotoxy(x,y);
			   		printf("@");
					sleep(1);
					q=0;
					button=0;
					*newlvl=lvl;
					*newx=x;
					*newy=y;
					*newxA=xA;
					*newyA=yA;
				 	*npot=pot;
				 	*newright=right;
				 	*newleft=left;
				 	*nhp=hp;
				 	*newatk=atk;
				 	*newnext=next;
					return;
				}
			}
			else if(q==2){		
				if (flag!=0){
					step=0;
					flag=0;
				}	
				if(step==0){
					gotoxy(lastx, lasty);
					printf(" ");
					gotoxy(x,y);
			   		printf("@");
				}else{
					if (step==38){
						gotoxy(lastx, lasty);
						printf("%c",176);
						gotoxy(x,y);
					    printf("@");
					    q=0;
					    step=0;
					}
					gotoxy(lastx, lasty);
					printf("%c",176);
					gotoxy(x,y);
				    printf("@");
				}
			    if((step==37)&&(map1[xA][yA+1]=='|')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]!=' ')){
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i){
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
							map1[xA][yA+1]=' ';
						}
					}
					flag=0;
					gotoxy(x,y);
	    			printf("@");
				}
				else
			    if((map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]!=' ')){	
					gotoxy(x,y);
			   		printf("@");
					sleep(1);
					q=0;
					button=0;
					*newlvl=lvl;
					*newx=x;
					*newy=y;
					*newxA=xA;
					*newyA=yA;
				 	*npot=pot;
				 	*newright=right;
				 	*newleft=left;
				 	*nhp=hp;
				 	*newatk=atk;
				 	*newnext=next;
					return;
				}
			}
			else if(q==3){		
				if (flag!=0){
					step=0;
					flag=0;
				}	
				if(step==0){
					gotoxy(lastx, lasty);
					printf(" ");
					gotoxy(x,y);
			   		printf("@");
				}else{
					if (step==40){
						gotoxy(lastx, lasty);
						printf("%c",176);
						gotoxy(x,y);
					    printf("@");
					    q=0;
					    step=0;
					}
					gotoxy(lastx, lasty);
					printf("%c",176);
					gotoxy(x,y);
				    printf("@");
				}
			    if((step==39)&&(map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]=='_')){
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i){
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
							map1[xA-1][yA]=' ';
						}
					}
					flag=0;
					gotoxy(x,y);
	    			printf("@");
				}
				else
			    if((map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]!=' ')){	
					gotoxy(x,y);
			   		printf("@");
					sleep(1);
					q=0;
					button=0;
					*newlvl=lvl;
					*newx=x;
					*newy=y;
					*newxA=xA;
					*newyA=yA;
				 	*npot=pot;
				 	*newright=right;
				 	*newleft=left;
				 	*nhp=hp;
				 	*newatk=atk;
				 	*newnext=next;
					return;
				}
			}
			else if(q==4){		
				if (flag!=0){
					step=0;
					flag=0;
				}	
				if(step==0){
					gotoxy(lastx, lasty);
					printf(" ");
					gotoxy(x,y);
			   		printf("@");
				}
				else{
					if (step==34){
						gotoxy(lastx, lasty);
						printf("%c",176);
						gotoxy(x,y);
					    printf("@");
					    q=0;
					    step=0;
					}
					gotoxy(lastx, lasty);
					printf("%c",176);
					gotoxy(x,y);
				    printf("@");
				}
			    if((step==33)&&(map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]=='_')){
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i){
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
							map1[xA-1][yA]=' ';
						}
					}
					flag=0;
					gotoxy(x,y);
	    			printf("@");
				}
				else
			    if((map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]!=' ')){	
					gotoxy(x,y);
			   		printf("@");
					sleep(1);
					q=0;
					button=0;
					*newlvl=lvl;
					*newx=x;
					*newy=y;
					*newxA=xA;
					*newyA=yA;
				 	*npot=pot;
				 	*newright=right;
				 	*newleft=left;
				 	*nhp=hp;
				 	*newatk=atk;
				 	*newnext=next;
					return;
				}
			}
			else if(q==5){		
				if (flag!=0){
					step=0;
					flag=0;
				}	
				if(step==0){
					gotoxy(lastx, lasty);
					printf(" ");
					gotoxy(x,y);
			   		printf("@");
				}
				else
				if (step==38){
					gotoxy(lastx, lasty);
					printf("%c",176);
					gotoxy(x,y);
				    printf("@");
				    q=0;
				    step=0;
				    button=0;
				}
				else{
					gotoxy(lastx, lasty);
					printf("%c",176);
					gotoxy(x,y);
				    printf("@");
				}
			    if((step==37)&&(map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]=='_')){
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i){
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
							map1[xA-1][yA]=' ';
						}
					}
					flag=0;
					gotoxy(x,y);
	    			printf("@");
				}
				else
			    if((map1[xA][yA+1]!=' ')&&(map1[xA][yA-1]!=' ')&&(map1[xA+1][yA]!=' ')&&(map1[xA-1][yA]!=' ')&&(q==5)){	
					gotoxy(x,y);
			   		printf("@");
					sleep(1);
					q=0;
					button=0;
					*newlvl=lvl;
					*newx=x;
					*newy=y;
					*newxA=xA;
					*newyA=yA;
				 	*npot=pot;
				 	*newright=right;
				 	*newleft=left;
				 	*nhp=hp;
				 	*newatk=atk;
				 	*newnext=next;
					return;
				}
			}
			else{
				gotoxy(lastx, lasty);
				printf(" ");
				gotoxy(x,y);
		    	printf("@");
			}
			c=getch();
			lastx = x; lasty = y;
			switch(c){	
				case ' ': 
					HTP(hp,lvl);
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i){	
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
						}
					}
					xA=lasty-1;
					yA=lastx;
					break;
				case 'w':
				case 'W':
					if (map1[xA-1][yA]==' '){
						xA--;
						y--;
						if(q>0){
							map1[xA+1][yA]=176;
							step++;
						}
					}else{
						if(map1[xA-1][yA]=='\"'){
							*newlvl=lvl;
							*newx=x;
							*newy=y;
							*newxA=xA;
							*newyA=yA;
						 	*npot=pot;
						 	*newright=right;
						 	*newleft=left;
						 	*nhp=hp;
						 	*newatk=atk;
						 	*newnext=next;
							return;
						}	
						if(map1[xA-1][yA]=='O'){
							gotoxy(55,10);
							type("You are late for the EXAM");
							sleep(1);
							gotoxy(55,11);
							type("Hope you studied more than");
							gotoxy(55,12);
							type("the A");
							sleep(1);
							gotoxy(60,12);
							type("B");
							sleep(1);
							gotoxy(61,12);
							type("C");
							sleep(1);
							gotoxy(62,12);
							type("D");
							sleep(1);
							gotoxy(63,12);
							type("E");
							sleep(1);
							gotoxy(63,12);
							type("IE");
							sleep(2);
							m=25;
							cho=quiz (m,pot,hp,atk,armor,lvl);
							if(cho==1){	
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								gotoxy(60,15);
								sleep(1);
								type("!UNBELIEVABLE!");
								gotoxy(57,16);
								type("!YOU PASSED THE EXAM!");
								sleep(2);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									xA--;
									y--;
									next=5;
									lvl=4;
									*newlvl=lvl;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<26;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[0][25]='@';
										}
									}
									sleep(2);
									system("cls");
								}
							}else{
								gotoxy(55,15);
								type("MOU AHA HA HA HA HA HA HA");
								gotoxy(60,16);
								type("YOU KNEW YOUR FATE");
								sleep(2);
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
							}
						}
						if(map1[xA-1][yA]=='.'){
							xA--;
							y--;
							if (button==2){
								button=3;
								q=3;
							}
							else
							if (button==4){
								button=5;
								q=5;
							}
							else{
								button=1;
								q=1;
							}
							gotoxy(52,10);
							printf("You stepped on a button that makes "); 
							gotoxy(52,11);
							printf("the ground cracking behind you!");
							gotoxy(52,12);
							printf(" >Press how to play for HINTS<");
						}
					}
					break;
				case 's':
				case 'S':
					if(map1[xA+1][yA]==' '){
						xA++;
						y++;
						if(q>0)	{
							map1[xA-1][yA]=176;
							step++;
						}
					}else{
						if(map1[xA+1][yA]=='\"'){
							*newlvl=lvl;
							*newx=x;
							*newy=y;
							*newxA=xA;
							*newyA=yA;
						 	*npot=pot;
						 	*newright=right;
						 	*newleft=left;
						 	*nhp=hp;
						 	*newatk=atk;
						 	*newnext=next;
							return;
						}
						if(map1[xA+1][yA]=='.'){
							xA++;
							y++;
							button=4;
							q=4;
							gotoxy(52,10);
							printf("You stepped on a button that makes "); 
							gotoxy(52,11);
							printf("the ground cracking behind you!");
							gotoxy(52,12);
							printf(" >Press how to play for HINTS<");
						}
					}
					break;
				case 'a':
				case 'A':
					if (map1[xA][yA-1]==' '){
						yA--;
						x--;
						if(q>0){
							map1[xA][yA+1]=176;
							step++;
						}
					}else{
						if(map1[xA][yA-1]=='\"'){
							*newlvl=lvl;
							*newx=x;
							*newy=y;
							*newxA=xA;
							*newyA=yA;
						 	*npot=pot;
						 	*newright=right;
						 	*newleft=left;
						 	*nhp=hp;
						 	*newatk=atk;
						 	*newnext=next;
							return;
						}	
						if (map1[xA][yA-1]=='?'){
							m=23;
							cho=quiz (m,pot,hp,atk,armor,lvl);
							if(cho==1){	
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								gotoxy(60,15);
								printf("!RIGHT ANSWER!");
								sleep(2);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									yA--;
									x--;
									next=3;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<26;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[9][26]=' ';
											map1[10][26]='?';
										}
									}
								}
								
							}else{
								gotoxy(60,15);
								printf("!WRONG ANSWER!");
								sleep(2);
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}
					}
					break;
				case 'd':
				case 'D':
					if (map1[xA][yA+1]==' '){	
						yA++;
						x++;
						if(q>0){
							map1[xA][yA-1]=176;
							step++;
						}	
					}else{
						if((map1[xA][yA+1]=='?')&&(next==3)){
							m=24;
							cho=quiz (m,pot,hp,atk,armor,lvl);
							if(cho==1){	
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								gotoxy(60,15);
								printf("!RIGHT ANSWER!");
								sleep(2);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									yA++;
									x++;
									next=4;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<26;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[7][19]=' ';
											map1[8][19]='?';
										}
									}
								}
							}else{
								gotoxy(60,15);
								printf("!WRONG ANSWER!");
								sleep(2);
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}
						if((map1[xA][yA+1]=='?')&&(next==1)){
							m=22;
							cho=quiz (m,pot,hp,atk,armor,lvl);
							if(cho==1){	
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								gotoxy(60,15);
								printf("!RIGHT ANSWER!");
								sleep(2);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									yA++;
									x++;
									next=2;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<26;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[16][31]=' ';
											map1[17][31]='?';
										}
									}
								}
							}else{
								gotoxy(60,15);
								printf("!WRONG ANSWER!");
								sleep(2);
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}
						if((map1[xA][yA+1]=='?')&&(next==0)){	
							m=21;
							cho=quiz (m,pot,hp,atk,armor,lvl);
							if(cho==1){	
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								gotoxy(60,15);
								printf("!RIGHT ANSWER!");
								sleep(2);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									yA++;
									x++;
									next=1;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<26;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[16][19]=' ';
											map1[17][19]='?';
										}
									}
								}
								
							}
							else{
								gotoxy(60,15);
								printf("!WRONG ANSWER!");
								sleep(2);
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}
						if(map1[xA][yA+1]=='.') {
							yA++;
							x++;
							q=2;
							button=2;
							gotoxy(52,10);
							printf("You stepped on a button that makes "); 
							gotoxy(52,11);
							printf("the ground cracking behind you!");
							gotoxy(52,12);
							printf(" >Press how to play for HINTS<");
						}
					}
					break;
			}
		}
	}
}
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
void callmap4a(int lvl,int x,int xA,int y,int yA,int pot,int right,int left,int next,int hp,int atk,int* newlvl,int* npot,int* newright,int* newleft,int* nhp,int* newatk,int* newnext){
	system("COLOR 0C");
	int i=0,j=0,br=0;
	boolean filesOpened = TRUE;
	boolean exit = FALSE;
	while(j!=1){		
		for(i=1;i<200;++i){
			system("cls");
			system("cls");
			gotoxy(18,10);
			printf ("! ! ! YOU ARE FALLINGGGGGGGGG ! ! !");
		}
		j=1;
	}
	system("cls");
	char c,a,p,cho;
	int  armor=60;
	armor+=(armor*0.1-1);
	int m,q,t;
	int lastx ,lasty;
	char map1[26][52];
	FILE *fp = NULL;
	fp=fopen("BIN/MAP4_A.TXT","r");
	if (fp==NULL){	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<26;++i){	
			for(j=0;j<52;++j)
			{	
				int a= fgetc(fp);
				map1[i][j]=a;
			}
		}
		fclose(fp);
	}
	if(filesOpened){
		
		
		if(map1[xA][yA+1]!=' ' && map1[xA][yA-1]!=' ' && map1[xA+1][yA]!=' ' && map1[xA-1][yA]!=' '){
			xA=13;
			yA=25;
			y=14;
			x=25;
		}
		
		if(left==1) map1[8][9]=' ';
		if(right==1) map1[10][41]=' ';
		printf("LVL:%d \t HP:%d\t Weapon:%s \t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
		for(i=0;i<26;++i){	
			for(j=0;j<52;++j){	
				printf("%c",map1[i][j]);
			}
		}
		while(!exit){	
			gotoxy(lastx, lasty);
			printf(" ");
			gotoxy(x,y);
			printf("@");
			c=getch();
			lastx = x; lasty = y;
			switch(c){	
				case ' ': 
					HTP(hp,lvl);
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<26;++i)	{	
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
						}
					}
					xA=lasty-1;
					yA=lastx;
					break;
				case 'w':
				case 'W':
					if (map1[xA-1][yA]==' '){
						xA--;
						y--;
					}else{
						if(map1[xA-1][yA]=='!'){
							xA--;
							y--;
							pot++;
							right=1;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<26;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[10][41]=' ';
								}
							}
						}
					}
					break;
				case 's':
				case 'S':
					if(map1[xA+1][yA]==' '){
						xA++;
						y++;
					}else{
						if(map1[xA+1][yA]=='_'){
							xA++;
							y++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<26;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[25][18]='@';
								}
							}
							sleep(1);
							*newlvl=lvl;
						 	*npot=pot;
						 	*newright=right;
						 	*newleft=left;
						 	*nhp=hp;
						 	*newatk=atk;
						 	*newnext=next;
							exit = TRUE;
						}
					}
					break;
				case 'a':
				case 'A':
					if (map1[xA][yA-1]==' '){
						yA--;
						x--;
					}else{
						if(map1[xA][yA-1]=='!'){
							yA--;
							x--;
							pot++;
							left=1;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<26;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[8][9]=' ';
								}
							}
						}
					}
					break;
				case 'd':
				case 'D':
					if (map1[xA][yA+1]==' '){	
						yA++;
						x++;
					}
					break;
			}
		}
	}
}
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
void callmap3(int lvl,int* nhp,int* newlvl){
	system("COLOR 0B");
	system("cls");
	char c,a,p,cho;
    char S=145,F=148,W=151;
	int maxhp=110,hp=110,atk=w [lvl].dmg, armor=55, pot=0,newhp,newpot,bonus,ehp,eatk,earmor;
	int i,j,m,next=0,q=1;
	int x = 1,y = 12,xA=11,yA=1,lastx = 1 ,lasty= 5,tele;
	boolean exit = FALSE;
	boolean filesOpened = TRUE;
	char map1[22][52];
	maxhp+=(maxhp*0.1-1);hp+=(hp*0.1-1);armor+=(armor*0.1);
	srand(time(0));
	bonus=(rand()%5);
	atk+=bonus;
	printf("LVL:%d \t HP:%d\t Weapon:%s \t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
	FILE *fp = NULL;
	fp=fopen("BIN/MAP_3.TXT","r");
	if (fp==NULL) {	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
				for(j=0;j<52;++j){	
					int a= fgetc(fp);
					map1[i][j]=a;
				}
			}
			fclose(fp);
			map1[9][15]=S;
		map1[9][25]=F;
		map1[11][48]=W;
		map1[11][0]='@';
	}
	if(filesOpened){
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				printf("%c",map1[i][j]);
			}
		}
		while (q!=0){	
			c=getch();
			if ((c=='d')||(c=='D')){
				system("cls");
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
				for(i=0;i<22;++i){	
					for(j=0;j<52;++j){	
						printf("%c",map1[i][j]);
						map1[11][0]=221;
					}
				}
				q=0;
			}
		}
		while(!exit){
			gotoxy(lastx, lasty);
			printf(" ");
			gotoxy(x,y);
		    printf("@");
			c=getch();
			lastx = x; lasty = y;
			switch(c){	
				case ' ': 
					HTP(hp,lvl);
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<22;++i){	
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
						}
					}
					xA=lasty-1;
					yA=lastx;
					break;
				case 'w':
				case 'W':
					if (map1[xA-1][yA]==' '){
						xA--;
						y--;
					}else{
					 	if(map1[xA-1][yA]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								yA=49;
								x=49;
							}
							if (tele==2){
								xA=19;
								y=20;
							}
							else{
								xA=19;
								yA=49;
								y=20;
								x=49;
							}
						}
						if (map1[xA-1][yA]=='Y'){
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=17;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==3){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[3][41]=197;
											}
										}
									}
									
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i)	{	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
						if (map1[xA-1][yA]=='X'){
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=19;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==5){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										gotoxy(13,11);
										printf("- THE DOOR LEADING TO THE BOSS IS NOW OPEN- ");
										sleep(2);
										map1[11][39]=' ';
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[17][25]=197;
											}
										}
									}
									
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
				case 's':
				case 'S':
					if(map1[xA+1][yA]==' '){
						xA++;
						y++;
					}else{
						if((map1[xA+1][yA])=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								xA=1;
								y=2;
							}
							else
							if (tele==2){
								yA=1;
								x=1; 
							}
							else{
								xA=1;
								yA=1;
								y=2;
								x=1; 
							}
						}
						if (map1[xA+1][yA]=='!'){
							xA++;
							y++;
							pot++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[17][31]=' ';
								}
							}
						}	
					}
					break;
				case 'a':
				case 'A':
					if (map1[xA][yA-1]==' '){
						yA--;
						x--;
					}else{
						if(map1[xA][yA-1]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								xA=1;
								y=2;
							}
							if (tele==2){
								yA=49;
								x=49;
							}
							else{
								xA=1;
								yA=49;
								y=2;
								x=49;
							}
						}
						if (map1[xA][yA-1]=='P'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=14;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								next++;
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
										map1[3][9]=197;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i)	{	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
						if (map1[xA][yA-1]==S){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=15;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==1){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[9][15]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
						if (map1[xA][yA-1]=='T'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=16;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==2){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[9][35]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
				case 'd':
				case 'D':
					if (map1[xA][yA+1]==' '){
						yA++;
						x++;
						if (next==7){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[11][48]=197;
									map1[11][50]='@';
									exit = TRUE;
									*nhp=hp;
									*newlvl=lvl;
								}
							}
							sleep(1);
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							gotoxy(10,10);
							printf("MaxHp(UP) Atk(UP)+(lucky bonus) Armor(UP)\n");
							gotoxy(10,25);
							printf("Press any key to continue . . .");
							getch();
							system("cls");
						}
					}else{
						if(map1[xA][yA+1]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								yA=1;
								x=1; 
							}
							if (tele==2){
								xA=19;
								y=20;
							}
							else{
								xA=19;
								yA=1;
								y=20;
								x=1;
							}
						}
						if (map1[xA][yA+1]=='!'){
							yA++;
							x++;
							pot++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[19][17]=' ';
								}
							}
						}
						if (map1[xA][yA+1]==W){	
							yA=yA+2;
							x=x+2;
							m=20;
							ehp=e [m].hp;
							eatk=e [m].atk;
							earmor=e [m].armor;
							if(next==6){
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								system("cls");
								letter(lvl);
								sleep(2);
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								printf("\n\n\n\n\n\n\n\t - YOU REMEMBERED THE LETTER OF THE SEQUENCE -\t\n\n\n\n\n\n\n\n\n\n ");
								printf("\t - IT'S THE GREEK LETTER '%c' OF COURSE!- \t ",150);
								sleep(4);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									next++;
									lvl=3;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<22;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[11][48]=197;
										}
									}
								}
							}
							else{
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}
						if (map1[xA][yA+1]==F){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=18;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==4){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[9][25]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i)	{	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
			}
		}
	}
}
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
void callmap2(int lvl,int* nhp,int* newlvl){   			
	system("COLOR 0D");
	system("cls");
	char c,a,p,cho;
    char KS=141,L=138,T=221;
	int maxhp=100,hp=100,atk=w [lvl].dmg, armor=50, pot=0,newhp,newpot,bonus,ehp,eatk,earmor;
	int i,j,m,next=0,q=1;
	boolean filesOpened = TRUE;
	boolean exit = FALSE;
	int x = 1,y = 12,xA=11,yA=1,lastx = 1,lasty = 10,tele;
	char map1[22][52];
	maxhp+=(maxhp*0.1);hp+=(hp*0.1);armor+=(armor*0.1);
	srand(time(0));
	bonus=(rand()%5);
	atk+=bonus;
	printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
	FILE *fp = NULL;
	fp=fopen("BIN/MAP_2.TXT","r");
	if (fp==NULL){	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(fp);
				map1[i][j]=a;
			}
		}
		fclose(fp);
		map1[17][46]=KS;
		map1[3][9]=L;
		map1[11][0]='@';
		
	}
	if(filesOpened){
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				printf("%c",map1[i][j]);
			}
		}
		while (q!=0){	
			c=getch();
			if ((c=='d')||(c=='D')){
				system("cls");
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
				for(i=0;i<22;++i)	{	
					for(j=0;j<52;++j){	
						printf("%c",map1[i][j]);
						map1[11][0]=221;
					}
				}
				q=0;
				break;
			}
		}
		while(!exit){
			gotoxy(lastx, lasty);
			printf(" ");
			gotoxy(x,y);
		    printf("@");
			c=getch();
			lastx = x; lasty = y;
			switch(c){	
				case ' ': 
					HTP(hp,lvl);
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<22;++i){	
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
						}
					}
					xA=lasty-1;
					yA=lastx;
					break;
				case 'w':
				case 'W':
					if (map1[xA-1][yA]==' '){
						xA--;
						y--;
					}else{
						if(map1[xA-1][yA]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								yA=49;
								x=49;
							}
							if (tele==2){
								xA=19;
								y=20;
							}
							else{
								xA=19;
								yA=49;
								y=20;
								x=49;
							}
						}
					}
					break;
				case 's':
				case 'S':
					if(map1[xA+1][yA]==' '){
						xA++;
						y++;
					}else{
						if((map1[xA+1][yA])=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								xA=1;
								y=2;
							}
							if (tele==2){
								yA=1;
								x=1; 
							}
							else{
								xA=1;
								yA=1;
								y=2;
								x=1; 
							}
						}	
					}
					break;
				case 'a':
				case 'A':
					if (map1[xA][yA-1]==' '){
						yA--;
						x--;
					}else{
						if(map1[xA][yA-1]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								xA=1;
								y=2;
							}
							if (tele==2){
								yA=49;
								x=49;
							}
							else{
								xA=1;
								yA=49;
								y=2;
								x=49;
							}
						}
						if (map1[xA][yA-1]=='!'){
							yA--;
							x--;
							pot++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[9][9]=' ';
								}
							}
						}
						if (map1[xA][yA-1]==L){
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=9;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==2){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[3][9]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
						if (map1[xA][yA-1]==KS){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=12;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==5){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										gotoxy(13,11);
										printf("- THE DOOR LEADING TO THE BOSS IS NOW OPEN- ");
										sleep(2);
										map1[11][39]=' ';
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[17][46]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
				case 'd':
				case 'D':
					if (map1[xA][yA+1]==' '){	
						yA++;
						x++;
						if (next==7) {	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[11][48]=197;
									map1[11][50]='@';
									exit = TRUE;
									*nhp=hp;
									*newlvl=lvl;
								}
							}
							sleep(1);
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							gotoxy(10,10);
							printf("MaxHp(UP) Atk(UP)+(lucky bonus) Armor(UP)\n");
							gotoxy(10,25);
							printf("Press any key to continue . . .");
							getch();
							system("cls");
						}
					}else{
						if(map1[xA][yA+1]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								yA=1;
								x=1; 
							}
							if (tele==2){
								xA=19;
								y=20;
							}
							else{
								xA=19;
								yA=1;
								y=20;
								x=1;
							}
						}
						if (map1[xA][yA+1]=='!'){
							yA++;
							x++;
							pot++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[17][25]=' ';
								}
							}
						}
						if (map1[xA][yA+1]=='O'){	
							yA=yA+2;
							x=x+2;
							m=13;
							ehp=e [m].hp;
							eatk=e [m].atk;
							earmor=e [m].armor;
							if(next==6){
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								system("cls");
								letter(lvl);
								sleep(2);
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								printf("\n\n\n\n\n\n\n\t - YOU REMEMBERED THE LETTER OF THE SEQUENCE -\t\n\n\n\n\n\n\n\n\n\n ");
								printf("\t - IT'S THE GREEK LETTER '%c' OF COURSE!- \t ",143);
								sleep(4);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									next++;
									lvl=2;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<22;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[11][48]=197;
										}
									}
								}
							}
							else{
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}			
						if (map1[xA][yA+1]=='I'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=7;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								next++;
								printf("%d",next);
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
										map1[17][9]=197;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}					
						if (map1[xA][yA+1]=='K'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=8;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==1){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[11][9]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}					
						if (map1[xA][yA+1]=='M'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=10;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==3){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[3][46]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}			
						if (map1[xA][yA+1]=='N'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=11;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==4){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[9][46]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i)	{	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
			}
		}
	}
}
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
//---------------------------------------------////---------------------------------------------////---------------------------------------------//
void callmap1(int lvl,int* nhp,int* newlvl){   			
	system("COLOR 0A");
	system("cls");
	char c,a,p,cho;
    char C=130, D=131, G=135,T=222;
	int maxhp=100,hp=100,atk=w[lvl].dmg, armor=50, pot=0,newhp,newpot,ehp,eatk,earmor;
	int i,j,m,next=0,q=1;
	int x = 21,y = 20,xA=19,yA=21,lastx = 21 ,lasty = 20,tele;
	boolean filesOpened = TRUE;
	boolean exit = FALSE;
	char map1[22][52];
	printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w[lvl].name,atk,armor,pot);
	FILE *fp = NULL;
	fp=fopen("BIN/MAP_1.TXT","r");
	if (fp==NULL){	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(fp);
				map1[i][j]=a;
				
			}
		}
		fclose(fp);
		map1[3][46]=C;//gamma
		map1[17][46]=D;//delta
		map1[11][48]=G;//theta
		map1[20][21]='@';
		
	}
	if(filesOpened){
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				printf("%c",map1[i][j]);
			}
		}	
		while (q!=0){	
			c=getch();
			if (c=='w'||c=='W'){
				system("cls");
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w[lvl].name,atk,armor,pot);
				map1[20][21]=223;
				for(i=0;i<22;++i){	
					for(j=0;j<52;++j){	
						printf("%c",map1[i][j]);
					}
				}
				q=0;
			}
		}	
		
		while(!exit){
			
			gotoxy(lastx, lasty);
			printf(" ");
			gotoxy(x,y);
		    printf("@");
			c=getch();
			lastx = x; lasty = y;
			switch(c){	
				case ' ':
				 	HTP(hp,lvl);
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					for(i=0;i<22;++i){	
						for(j=0;j<52;++j){	
							printf("%c",map1[i][j]);
						}
					}
					xA=lasty-1;
					yA=lastx;
					break;
				case 'w':
				case 'W':
					if (map1[xA-1][yA]==' '){
						xA--;
						y--;
					}else{
					 	if(map1[xA-1][yA]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								yA=49;
								x=49;
							}
							if (tele==2){
								xA=19;
								y=20;
							}
							else{
								xA=19;
								yA=49;
								y=20;
								x=49;
							}
						}
						if (map1[xA-1][yA]=='B'){
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=1;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==1){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i)	{	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[18][9]=197;
											}
										}
									}
									
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
				case 's':
				case 'S':
					if(map1[xA+1][yA]==' '){
							xA++;
							y++;
					}else{
						if((map1[xA+1][yA])=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								xA=1;
								y=2;
							}
							else
							if (tele==2){
								yA=1;
								x=1; 
							}
							else{
								xA=1;
								yA=1;
								y=2;
								x=1; 
							}
						}	
						if (map1[xA+1][yA]=='!'){
							xA++;
							y++;
							pot++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[3][17]=' ';
								}
							}
						}
					}
					break;
				case 'a':
				case 'A':
					if (map1[xA][yA-1]==' '){
						yA--;
						x--;
					}else{
						if(map1[xA][yA-1]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								xA=1;
								y=2;
							}
							else
							if (tele==2){
								yA=49;
								x=49;
							}
							else{
								xA=1;
								yA=49;
								y=2;
								x=49;
							}
						}
						if (map1[xA][yA-1]=='!'){	
							yA--;
							x--;
							pot++;
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[13][27]=' ';
								}
							}
						}
						if (map1[xA][yA-1]=='A'){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=0;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								next++;
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
										map1[3][9]=197;
										
									}
								}
							}
							else{
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
							
						}
						if (map1[xA][yA-1]==D){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){
								m=3;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==3){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[17][46]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
				case 'd':
				case 'D':
					if (map1[xA][yA+1]==' '){	
						yA++;
						x++;
						if (next==7){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							for(i=0;i<22;++i){	
								for(j=0;j<52;++j){	
									printf("%c",map1[i][j]);
									map1[11][48]=197;
									map1[11][50]='@';
									exit = TRUE;
									*nhp=hp;
									*newlvl=lvl;
								}
							}
							sleep(1);
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							gotoxy(10,10);
							printf("MaxHp(UP) Atk(UP)+(lucky bonus) Armor(UP)\n");
							gotoxy(10,25);
							printf("Press any key to continue . . .");
							getch();
							system("cls");
						}
					}else{
						if(map1[xA][yA+1]=='*'){	
							srand(time(0));
							tele=(rand()%3)+1;
							if (tele==1){
								yA=1;
								x=1; 
							}
							else
							if (tele==2){
								xA=19;
								y=20;
							}
							else{
								xA=19;
								yA=1;
								y=20;
								x=1;
							}
						}
						if (map1[xA][yA+1]==G){	
							yA=yA+2;
							x=x+2;
							m=6;
							ehp=e [m].hp;
							eatk=e [m].atk;
							earmor=e [m].armor;
							next=6;
							if(next==6){
								ehp=e [m].hp-200;
								eatk=e [m].atk-50;
								earmor=e [m].armor-30;
								system("cls");
								letter(lvl);
								sleep(2);
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								printf("\n\n\n\n\n\n\n\t - YOU REMEMBERED THE LETTER OF THE SEQUENCE -\t\n\n\n\n\n\n\n\n\n\n ");
								printf("\t - IT'S THE GREEK LETTER 'H' OF COURSE!- \t ");
								sleep(4);
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								pot=newpot;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}else{
									next++;
									lvl++;
									system("cls");
									printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
									for(i=0;i<22;++i){	
										for(j=0;j<52;++j){	
											printf("%c",map1[i][j]);
											map1[11][48]=197;
										}
									}
								}
							}
							else{
								battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
								hp=newhp;
								if(hp==0){
									*nhp=hp;
									system("cls");
									exit = TRUE;
								}
							}
						}
						if (map1[xA][yA+1]==C){	
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=2;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==2){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[3][46]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
						if (map1[xA][yA+1]=='E'){
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=4;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==4){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i){	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[9][3]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
						if (map1[xA][yA+1]=='Z'){
							system("cls");
							printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
							cho=choose (cho,m,pot,hp,atk,armor,lvl);
							if((cho=='y')||(cho=='Y')){	
								m=5;
								ehp=e [m].hp;
								eatk=e [m].atk;
								earmor=e [m].armor;
								if(next==5){
									ehp=e [m].hp-200;
									eatk=e [m].atk-50;
									earmor=e [m].armor-30;
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									pot=newpot;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}else{
										next++;
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										gotoxy(13,11);
										printf("- THE DOOR LEADING TO THE BOSS IS NOW OPEN- ");
										sleep(2);
										map1[11][40]=' ';
										system("cls");
										printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
										for(i=0;i<22;++i)	{	
											for(j=0;j<52;++j){	
												printf("%c",map1[i][j]);
												map1[9][49]=197;
											}
										}
									}
								}
								else{
									battle(m,ehp,eatk,earmor,pot,hp,&newhp,&newpot,maxhp,atk,armor,lvl);
									hp=newhp;
									if(hp==0){
										*nhp=hp;
										system("cls");
										exit = TRUE;
									}
								}
							}
							else{	
								system("cls");
								printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor:%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
								for(i=0;i<22;++i){	
									for(j=0;j<52;++j){	
										printf("%c",map1[i][j]);
									}
								}
							}
						}
					}
					break;
			}
		}
	}
}
///////////////
void map(int lvl){
	int nhp,hp,newlvl;
	if(lvl==0){
		do{
			callmap1(lvl,&nhp,&newlvl);
			hp=nhp;
			lvl=newlvl;
			if(hp<=0) {
				gameover();
				lvl=0;
			}
		}while(lvl==0);
	}else if(lvl==1){
		do{
			callmap2(lvl,&nhp,&newlvl);
			hp=nhp;
			lvl=newlvl;
			if(hp<=0) {
				gameover();
				lvl=1;
			}
		}while(lvl==1);
	}else if(lvl==2){
		do{
			callmap3(lvl,&nhp,&newlvl);
			hp=nhp;
			lvl=newlvl;
			if(hp<=0){
				gameover();
				lvl=2;
			}
		}while(lvl==2);
	}
}
//////////////
void lastmap(int lvl){
	int pot=0,left=0,right=0,next=0,hp=120,bonus,atk,newx,newy,newyA,newxA,x,y,xA,yA,newlvl,npot,newright,newleft,nhp,newatk,newnext;
	atk=w [lvl].dmg;
	hp+=(hp*0.1-2);
	srand(time(0));
	bonus=(rand()%5);
	atk+=bonus;
	do{
 		callmap4(pot,left,right,next,hp,atk,&newlvl,&newx,&newy,&newxA,&newyA,&npot,&newright,&newleft,&nhp,&newatk,&newnext);
 		lvl=newlvl;
	 	x=newx;
	 	y=newy;
	 	xA=newxA;
	 	yA=newyA;
	 	pot=npot;
	 	right=newright;
	 	left=newleft;
	 	hp=nhp;
	 	atk=newatk;
	 	next=newnext;
		if ((lvl!=4)&&(hp>0)){
			callmap4a(lvl,x,xA,y,yA,pot,right,left,next,hp,atk,&newlvl,&npot,&newright,&newleft,&nhp,&newatk,&newnext);
		 	lvl=newlvl;
		 	pot=npot;
		 	right=newright;
		 	left=newleft;
		 	hp=nhp;
		 	atk=newatk;
		 	next=newnext;
	 	}
	 	else
	 	if(hp<=0) {
			 gameover();
			 lvl=3;
			 pot=0,left=0,right=0,next=0,hp=120,bonus,atk,newx,newy,newyA,newxA,x,y,xA,yA,newlvl,npot,newright,newleft,nhp,newatk,newnext;
			 atk=w [lvl].dmg;
			 hp+=(hp*0.1-2);
		  	 srand(time(0));
			 bonus=(rand()%5);
			 atk+=bonus;
		}
 	}while(lvl==3);
}
//////////////
void intro(){	
	type("\nYou are playing as Fataoul's kid!\n");
	sleep(1);
	type("\nFataoul's kid,FattyJr is in first grade of primary school!\n");
	type("\nHe is learning the greek Alphabet but seems too hard for him . . .\n");
	sleep(1);
	type("\nOne day,FJ was home stuDying for the next day's exam ,revising\n");
	type("\nthe greek alphaBet.He was studying hard,he was trying hard and harder\n");
	type("\nin order to memorize the letters.But . . . he keeps on forgetting . . .\n");
	sleep(1);
	type("\nWhich letter comes next??? . . . In which order??? . . . \n");
	sleep(1);
	type("\n. . . Which ? ? ? . . . What ? ? ? . . .\n");
	sleep(1);
	type("\nFJ fell asleep holding his Pencil,with all these thoughts twisting and swirling\n");
	type("\nin his mind.\n");
	sleep(1);
	type("\n\n");
	type("\nNOW I WONDER . . . IS GREEK ALPHABET HARDER THAN SOLVING A MAZE? . . .\n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
}
//////////////
void intro2(){
	type("\nYou successfully passed the first 8 letters of greek alphabet!\n");
	type("\nDespite the fact you couldn't remember a letter,\n");
	type("\nyou 'draw' it fighting the other letters in the right order !\n");
	sleep(1);
	type("\nNow your knowledge is better and you feel mentally stronger . . . \n");
	type("\nIt's time to use the Pen to engrave the letters and learn them faster!\n");
	type("\nJust hope you're lucky and get a strong one . . .\n");
	sleep(1);
	type("\n\n");
	type("\nBE SURE  . . . YOU ARE NOT THE ONLY ONE WHO GOT STRONGER . . .\n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
}
/////////////
void intro3(){
	type("\nYou successfully passed the next 8 letters of greek alphabet!\n");
	type("\nYou are doing well as you start to remember more and more in\n");
	type("\nyour journey to learn all the letters.\n");
	sleep(1);
	type("\nEverything starts to pop out of your mind while fighting and \n");
	type("\nfighting your way through knowledge . . .\n");
	type("\nGrab your Steel Pen and keep up the hard work . . .\n");
	sleep(1);
	type("\n\n");
	type("\nLET'S HOPE LETTERS WILL BE YOUR ONLY PROBLEM . . .\n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
}
/////////////
void intro4(){
	type("\nYou've learned all of the 24 letters of the greek alphabet!\n");
	type("\nYou feel wiser after this hard 'battle'!\n");
	type("\nYou have proved to yourself that you can succeed if you \n");
	type("\natleast try! Rriiinnng . . . Rriiiinnng . . . \n");
	sleep(1);
	type("\nSomething seems wrong . . .\n");
	type("\nRriiinnng . . . Rriiinnng . . .\n");
	sleep(1);
	type("\nWhy do I feel kind of dozy? . . .\n");
	type("\nRriiinnng . . . Rriiinnng . . .\n");
	type("\n\n");
	type("\nWHAT IS THIS SOUND ANYWAYS ? ? ? \n");
	sleep(2);
	system("cls");
	int i,j,x;
	boolean filesOpened = TRUE;
	char start1[32][52];
	char start2[32][52];
	FILE *cp1 = NULL;
	cp1=fopen("BIN/CLOCK.TXT","r");
	if (cp1==NULL) {	
		perror("ERROR");
		filesOpened = FALSE;
		sleep(1);
	}else{
		for(i=0;i<32;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				start1[i][j]=a;
			}
		}
		fclose(cp1);
	}
	FILE *cp2 = NULL;
	cp2=fopen("BIN/CLOCK2.TXT","r");
	if (cp2==NULL) {	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<32;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp2);
				start2[i][j]=a;
			}
		}
		fclose(cp2);
	}
	if(filesOpened){
		for(x=0;x<5;++x){
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j)	{	
					printf("%c",start1[i][j]);
				}
			}
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start2[i][j]);
				}
			}
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start1[i][j]);
				}
			}
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start2[i][j]);
				}
			}
			sleep(1);
		}
				
	}
	system("cls");
	type("\nOh my god...I fell asleep while studying!\n");
	type("\nNoooo...How am I supposed to pass the exam? . . .\n");
	type("\n!!!!!Wait a second . . . I remember everything!!\n");
	type("\n. . . What a dream ! ! ! :)\n");
	sleep(1);
	type("\nI have to hurry or I'll be late . . .\n");
	type("\nI'll grab this Indeliable Pen I found on my desk\n");
	type("\nhoping that I wont have any problem writing with it . . .\n");
	type("\n\n");
	type("\nSO...DREAMING CAN SOMETIMES LEAD TO SOLVING MAJOR PROBLEMS . . . \n");
	type("\n\n");
	type("\n. . . OR NOT ? ? ? . . . \n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
}
/////////////
void outro(){
	type("\nCongratulations . . . You managed to succeed in school's exams!!!\n");
	type("\nNow FJ feels relieved ,ready to continue his education!!!\n");
	type("\nHe learned a valuable lesson during this 'ADVENTURE'. . .\n");
	sleep(1);
	type("\n\n");
	type("\nYou must try hard in order to acomplish your goals . . . \n");
	type("\nIt might be hard,but in the end . . . you are the WINNER!!! \n");
	type("\n\n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
	system("cls");
	int i,j,x;
	boolean filesOpened = TRUE;
	char start1[32][52];
	char start2[32][52];
	FILE *cp1 = NULL;
	cp1=fopen("BIN/CLOCK.TXT","r");
	if (cp1==NULL) {	
		perror("ERROR");
		filesOpened = FALSE;
		sleep(1);
	}else{
		for(i=0;i<32;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				start1[i][j]=a;
			}
		}
		fclose(cp1);
	}
	FILE *cp2 = NULL;
	cp2=fopen("BIN/CLOCK2.TXT","r");
	if (cp2==NULL) {	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<32;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp2);
				start2[i][j]=a;
			}
		}
		fclose(cp2);
	}
	if(filesOpened){
		for(x=0;x<5;++x){
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j)	{	
					printf("%c",start1[i][j]);
				}
			}
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start2[i][j]);
				}
			}
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start1[i][j]);
				}
			}
			system("cls");
			for(i=0;i<32;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start2[i][j]);
				}
			}
			sleep(1);
		}
				
	}
	system("cls");
	type("\nOh my god...I fell asleep while studying!\n");
	type("\nNoooo...How am I supposed to pass the exam? . . .\n");
	type("\nWait a second . . . What was I supposed to study yesterday???\n");
	type("\nOh,Greek Alphabet. . . And what was I dreaming about???\n");
	type("\nFighting Greek letters and my teachers...What a weird dream ! ! ! :P\n");
	sleep(1);
	type("\nI have to hurry or I'll be late . . .\n");
	type("\nI'll grab this old pencil I found on my desk\n");
	type("\nhoping that I won't have any problem writing with it . . .\n");
	type("\n\n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
	system("cls");
	type("\nWHAT A MISFORTUNE . . . FJ WAS DREAMING THE WHOLE TIME . . .\n");
	type("\nTHAT'S REALLY UNLUCKY CAUSE HE DID GREAT . . . ;)\n");
	type("\nLET'S HOPE HE'LL DO AS GREAT AS YOU DID IN THE EXAMS ! ! ! \n");
	type("\n\n");
	type("\n\n");
	type("\n\n");
	printf("Press any key to continue . . .");
	getch();
}
/////////////
void castle(){
	int i,j;
	boolean filesOpened = TRUE;
	char castle1[31][52];
	char castle2[31][52];
	char castle3[31][52];
	FILE *cp1 = NULL;
	cp1=fopen("BIN/CASTLE.TXT","r");
	if (cp1==NULL) {	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<31;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				castle1[i][j]=a;
			}
		}
		fclose(cp1);
	}
	FILE *cp2 = NULL;
	cp2=fopen("BIN/CASTLE2.TXT","r");
	if (cp2==NULL) {
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<31;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp2);
				castle2[i][j]=a;
			}
		}
		fclose(cp2);
	}
	FILE *cp3 = NULL;
	cp3=fopen("BIN/CASTLE3.TXT","r");
	if (cp3==NULL){
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<31;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp3);
				castle3[i][j]=a;
			}
		}
		fclose(cp3);
	}
	if(filesOpened){
		system("cls");
		for(i=0;i<31;++i){	
			for(j=0;j<52;++j){	
				printf("%c",castle1[i][j]);
			}
		}
		sleep(1);
		system("cls");
		for(i=0;i<31;++i){	
				for(j=0;j<52;++j){	
					printf("%c",castle2[i][j]);
			}
		}
		sleep(1);
		system("cls");
		for(i=0;i<31;++i){	
			for(j=0;j<52;++j){	
				printf("%c",castle3[i][j]);
			}
		}
		sleep(1);
		system("cls");
	}
		
}
////////////
void load(){	
	int r,c,q,i,j;
	char start1[24][52];
	char fname[] = "BIN/LOAD.TXT";
	
	FILE *cp1 = NULL;
	cp1=fopen(fname,"r");
	
	if (access(fname, F_OK) == -1) {	
		perror ("ERROR");
	}else{
		for(i=0;i<24;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				start1[i][j]=a;
			}
		}
		fclose(cp1);

		system("cls");
		for(i=0;i<24;++i){	
			for(j=0;j<52;++j){	
				printf("%c",start1[i][j]);
			}
		}
		gotoxy(10,8);
		printf("Hit SPACEBAR for select/menu");
		gotoxy(21,14);
		printf("Loading...");
		gotoxy(15,15);
		for(r=1;r<=20;r++){
			for(q=0;q<=100000000;q++);
			printf("%c",177);
		}
		system("cls");
	}
}
/////////////
void type(char *s){	
	for(;*s;s++){
		putchar(*s);
		fflush(stdout);
		usleep(100000);
	}
}	
//////////////
void pressenter(){	
	char c;
	boolean e = TRUE;
	printf ("\n%*s[ Press enter to continue ]", 24, " ");
	while(e){	
		c=getch();
		if(c==13) e = FALSE;
	}
}
//////////////////
void start(){		
	int i,j,hp=0,x=1,lvl=10;
	char a;
	boolean filesOpened = TRUE;
	char fname[] = "BIN/START.TXT";
	char fname2[] = "BIN/START2.TXT";
	char start1[24][52];
	char start2[24][52];
	
	FILE *cp1 = NULL;
	cp1=fopen(fname,"r");
	
	if (access(fname, F_OK) == -1){	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<24;++i)		{	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				start1[i][j]=a;
			}
		}
		fclose(cp1);
	}
	
	FILE *cp2 = NULL;
	cp2=fopen(fname2,"r");
	
	if (access(fname2, F_OK) == -1) {	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<24;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp2);
				start2[i][j]=a;
			}
		}
		fclose(cp2);
	}

	if(filesOpened){
		for(i=0;i<24;++i){	
			for(j=0;j<52;++j){	
				printf("%c",start1[i][j]);
			}
		}
	}				
	while (1==1){	
		a=getch();
		switch (a){	
			case 'w':
			case 'W':
				system("cls");
				for(i=0;i<24;++i){	
					for(j=0;j<52;++j){	
						printf("%c",start1[i][j]);
					}
				}		
				x=1;
				break;
			case 's':
			case 'S':
				system("cls");
				for(i=0;i<24;++i){	
					for(j=0;j<52;++j){	
						printf("%c",start2[i][j]);
					}
				}		
				x=2; 
				break;
			case ' ': 
				if (x==1) return;
				else HTP(hp,lvl);
				x=2;
				break;
		}
	}
						
}
//////////////////
void HTP(int hp,int lvl){		
	int i,j;
	char start2[24][52];
	system("cls");
	printf("\n\t~HOW-TO-PLAY MENU~\n");	
	printf("\n=> SPACE = call menu for HINTS\n");
	printf("=> Switch keyboard to English\n");
	printf("=> Turn NUM LOCK on (optional)\n");
	
	if (lvl < 3)printf("=> 95%% chance to play at least one time first(are you lucky enough?)\n\n\n\n");
	else printf("\n\n\n\n");
	if (lvl==0) printf("Map 1 (H)\n\n");
	if (lvl==1) printf("Map 2 (%C)\n\n",143);
	if (lvl==2) printf("Map 3 (%c)\n\n",150);
	if (lvl==3) printf("Map 4 \n\n");
	if((lvl < 3)){
		if (lvl==0){ 
			printf("Greek letters = enemies HP:100 Atk:60 Armor:10 (if you have studied well!)\n");
			printf("@ = FJ  MaxHp:100\n");
		}
		if (lvl==1){
			printf("Greek letters = enemies HP:150 Atk:65 Armor:10 (if you have studied well!)\n");
			printf("@ = FJ  MaxHp:110\n");
		}
		if (lvl==2){
			 printf("Greek letters = enemies HP:180 Atk:70 Armor:10 (if you have studied well!)\n");
			 printf("@ = FJ  MaxHp:120\n");
		}
		printf("! = potion = +55 hp \n");
		printf("* = teleporters\n");
		printf("%c = door leading to the BOSS\n\n",176);
		printf("Figure out which enemy you should fight each time or you'll DIE !! \n");
		printf("Defeat the BOSS to clear the map.\n");
	}
	if(lvl==3){
		printf("? = enemies HP:210 Atk:80 Armor:10 (if you have studied well!)\n");
		printf("@ = FJ  MaxHp:130\n");
		printf(")O( = BOSS \n");
		printf("! = potion = +55 hp \n");
		printf("\" = cliff edge (falling underground)\n");
		printf("_ & | = door\n");
		printf("%c = column\n",254);
		printf(". = button\n");
		printf("%c = cracked ground\n",176);
		printf("-If you step on a button, the ground behind you will start cracking.\n");
		printf("You MUST step on EVERY part of the ground and the door will OPEN.\n");
		printf("BE CAREFUL not to be trapped between cracked ground because you will fall UNDERGROUND.\n");
		printf("-Be sure to answer teachers' questions correct or you will DIE !!\n");
	}
	gotoxy(1,24);
	printf("\n\n\n\n~Press any key to return~\n\n");
	getch();
	system("cls");
	
	if(hp==0){
		FILE *cp2 = NULL;
		cp2=fopen("BIN/START2.TXT","r");
		if (cp2==NULL) {	
			perror ("ERROR");
		}else{
			for(i=0;i<24;++i){	
				for(j=0;j<52;++j){	
					int a= fgetc(cp2);
					start2[i][j]=a;
				}
			}
			fclose(cp2);
			for(i=0;i<24;++i){	
				for(j=0;j<52;++j){	
					printf("%c",start2[i][j]);
				}
			}	
		}
	}
}
/////////////////
void letter(lvl){
	int i,j;
	boolean filesOpened = TRUE;
	char G=135;
	char letter1[22][52];
	char letter2[22][52];
	char letter3[22][52];
	char *file1; char *file2; char *file3;
	if(lvl==0){
		file1 = "BIN/HTTA1.TXT";
		file2 = "BIN/HTTA2.TXT";
		file3 = "BIN/HTTA3.TXT";
	}
	if(lvl==1){
		file1 = "BIN/PI1.TXT";
		file2 = "BIN/PI2.TXT";
		file3 = "BIN/PI3.TXT";
	}
	if(lvl==2){
		file1 = "BIN/PSI1.TXT";
		file2 = "BIN/PSI2.TXT";
		file3 = "BIN/PSI3.TXT";
	}
	
	FILE *cp1 = NULL;
	cp1=fopen(file1,"r");
	if (cp1==NULL){	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				letter1[i][j]=a;
				letter1[11][48]=G;
			}
		}
		fclose(cp1);
	}
		
	FILE *cp2 = NULL;
	cp2=fopen(file2,"r");
	if (cp2==NULL){	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp2);
				letter2[i][j]=a;
				letter2[11][48]=G;
			}
		}
		fclose(cp2);
	}
		
	FILE *cp3 = NULL;
	cp3=fopen(file3,"r");
	if (cp3==NULL){	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp3);
				letter3[i][j]=a;
				letter3[11][48]=G;
			}
		}
		fclose(cp3);
	}
	if(filesOpened){
		sleep(1);
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				printf("%c",letter1[i][j]);
			}
		}
		sleep(1);
		system("cls");
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){
				printf("%c",letter2[i][j]);
			}
		}
		sleep(1);
		system("cls");
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				printf("%c",letter3[i][j]);
			}
		}	
	}		

	sleep(1);
}	
//////////////////
void chest(int lvl){	
	int i,j;
	char chest1[22][52];
	char chest2[22][52];
	boolean filesOpened = TRUE;
	
	FILE *cp1 = NULL;
	cp1=fopen("BIN/CHEST1.TXT","r");
	if (cp1==NULL){	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp1);
				chest1[i][j]=a;
			}
		}
		fclose(cp1);
	}
					
	FILE *cp2 = NULL;
	cp2=fopen("BIN/CHEST2.TXT","r");
	if (cp2==NULL) {	
		perror ("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp2);
				chest2[i][j]=a;
			}
		}
		fclose(cp2);
	}
	if(filesOpened){
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				
				printf("%c",chest1[i][j]);
			}
		}	
		sleep(2);
		system("cls");
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				
				printf("%c",chest2[i][j]);
			}
		}
		sleep(1);
		gotoxy(13,22);
		printf(" YOU FOUND  < %s > ",w [lvl].name);
		sleep(3);
	}	
				
}
//////////////////
void gotoxy(int eex, int eey){
  COORD coord;
  coord.X = eex;
  coord.Y = eey;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//////////////////
void gameover(){	
	char go;
	int i,j;
	char gameover[22][52];
	boolean filesOpened = TRUE;
	FILE *cp = NULL;
	cp=fopen("BIN/GAMEOVER.TXT","r");
	if (cp==NULL){	
		perror ("ERROR");
	}else{
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp);
				gameover[i][j]=a;
			}
		}
		fclose(cp);
	}
	
	if(filesOpened){
		for(i=0;i<22;++i){	
			for(j=0;j<52;++j){	
				printf("%c",gameover[i][j]);
			}
		}
		do{
			go=getch();
		}while((go!='y')&&(go!='n')&&(go!='Y')&&(go!='N'));
		if ((go=='n')||(go=='N')) exit(1);
	}
}
/////////////////////
char choose(char cho,int m,int pot,int hp,int atk,int armor,int lvl){
	char G=135,W=151;
	int i,j;
	char choice[22][52];
	char choice2[22][52];
	char choice3[22][52];
	
	if(lvl==0){
		FILE *cp = NULL;
		cp=fopen("BIN/TEXT1.TXT","r");
		if (cp==NULL) {	
			perror ("ERROR");
		}else{
			for(i=0;i<22;++i){	
				for(j=0;j<52;++j){	
					int a= fgetc(cp);
					choice[i][j]=a;
					choice[11][48]=G;
				}
			}
			fclose(cp);
			for(i=0;i<22;++i){	
				for(j=0;j<52;++j){	
					printf("%c",choice[i][j]);
				}
			}
		}
		
	}
	if(lvl==1){
		FILE *cp = NULL;
		cp=fopen("BIN/TEXT2.TXT","r");
		if (cp==NULL){	
			perror ("ERROR");
		}else{
			for(i=0;i<22;++i){	
				for(j=0;j<52;++j){	
					int a= fgetc(cp);
					choice2[i][j]=a;
					choice2[11][48]='O';
				}
			}
			fclose(cp);
			for(i=0;i<22;++i)	{	
				for(j=0;j<52;++j){	
					printf("%c",choice2[i][j]);
				}
			}
		}
		
	}
	if(lvl==2){
		FILE *cp = NULL;
		cp=fopen("BIN/TEXT3.TXT","r");
		if (cp==NULL){	
			perror ("ERROR");
		}else{
			for(i=0;i<22;++i){	
				for(j=0;j<52;++j){	
					int a= fgetc(cp);
					choice3[i][j]=a;
					choice3[11][48]=W;
				}
			}
			fclose(cp);
			for(i=0;i<22;++i){	
				for(j=0;j<52;++j){	
					printf("%c",choice3[i][j]);
				}
			}
		}
		
	}		
								
	do{
		cho=getch();
	}while((cho!='y')&&(cho!='n')&&(cho!='Y')&&(cho!='N'));
	return cho;
}
/////////////////
int quiz(int m,int pot,int hp,int atk,int armor,int lvl){	
	system("cls");
	int i,j,quest,ans,cho=0;
	char quiz[26][52],r,correct;
	boolean filesOpened = TRUE;
	FILE *cp = NULL;
	cp=fopen("BIN/TEXT4.TXT","r");
	if(cp==NULL) {	
		perror("ERROR");
		filesOpened = FALSE;
	}else{
		for(i=0;i<26;++i){	
			for(j=0;j<52;++j){	
				int a= fgetc(cp);
				quiz[i][j]=a;
			}
		}
		fclose(cp);
	}
	if(filesOpened){
		
		printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
		for(i=0;i<26;++i){	
			for(j=0;j<52;++j){	
				printf("%c",quiz[i][j]);
			}
		}
		quest=(rand()%3)+1;
		ans=(rand()%3)+1;
		gotoxy(6,11);
		printf("%s:", e [m].name);
		sleep(1);
		gotoxy(24,11);
		type("Answer my question");
		gotoxy(6,12);
		type("if you are worthy to proceed...");
		sleep(1);
		gotoxy(52,10);
		printf("Press the number corresponding to");
		gotoxy(52,11);
		printf("the answer you want to choose ");
		
		switch (m){
			case 21:
				if(quest==1){//PHYSICS
					gotoxy(6,13);
					type("Light year is a unit of");
					sleep(1);
					
					if(ans==1){
						gotoxy(6,14);
						type("1. time");
						gotoxy(6,15);
						type("2. distance");
						gotoxy(6,16);
						type("3. intensity of light");
						gotoxy(6,17);
						type("4. light");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. distance");
						gotoxy(6,15);
						type("2. light");
						gotoxy(6,16);
						type("3. time");
						gotoxy(6,17);
						type("4. intensity of light");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. intensity of light");
						gotoxy(6,15);
						type("2. time");
						gotoxy(6,16);
						type("3. light");
						gotoxy(6,17);
						type("4. distance");
						correct=52;
					}
				}
				if(quest==2){
					gotoxy(6,13);
					type("Sound of frequency below 20Hz is a(n)");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. audio sound");
						gotoxy(6,15);
						type("2. infrasonic");
						gotoxy(6,16);
						type("3. ultrasonic");
						gotoxy(6,17);
						type("4. supersonic");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. infrasonic");
						gotoxy(6,15);
						type("2. ultrasonic");
						gotoxy(6,16);
						type("3. supersonic");
						gotoxy(6,17);
						type("4. audio sound");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. supersonic");
						gotoxy(6,15);
						type("2. audio sound");
						gotoxy(6,16);
						type("3. infrasonic");
						gotoxy(6,17);
						type("4. ultrasonic");
						correct=51;
					}
				}
				if(quest==3){
					gotoxy(6,13);
					type("Sound travels faster in");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. vacuum");
						gotoxy(6,15);
						type("2. steel");
						gotoxy(6,16);
						type("3. water");
						gotoxy(6,17);
						type("4. air");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. steel");
						gotoxy(6,15);
						type("2. water");
						gotoxy(6,16);
						type("3. air");
						gotoxy(6,17);
						type("4. vacuum");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. water");
						gotoxy(6,15);
						type("2. air");
						gotoxy(6,16);
						type("3. vacuum");
						gotoxy(6,17);
						type("4. steel");
						correct=52;
					}
				}
				break;
			case 22:
				if(quest==1){//GEOGRAPHY
					gotoxy(6,13);
					type("Which city is the capital of Greece?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. Thessaloniki");
						gotoxy(6,15);
						type("2. Athens");
						gotoxy(6,16);
						type("3. Sparta");
						gotoxy(6,17);
						type("4. Nafplio");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. Athens");
						gotoxy(6,15);
						type("2. Sparta");
						gotoxy(6,16);
						type("3. Nafplio");
						gotoxy(6,17);
						type("4. Thessaloniki");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. Sparta");
						gotoxy(6,15);
						type("2. Nafplio");
						gotoxy(6,16);
						type("3. Thessaloniki");
						gotoxy(6,17);
						type("4. Athens");
						correct=52;
					}
				}		
				if(quest==2){	
					gotoxy(6,13);
					type("Which country is NOT in Africa?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. Morocco");
						gotoxy(6,15);
						type("2. Thailand");
						gotoxy(6,16);
						type("3. Cameroon");
						gotoxy(6,17);
						type("4. Madagascar");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. Thailand");
						gotoxy(6,15);
						type("2. Morocco");
						gotoxy(6,16);
						type("3. Madagascar");
						gotoxy(6,17);
						type("4. Cameroon");
						correct=49;
					}
					if(ans==3){	
						gotoxy(6,14);
						type("1. Madagascar");
						gotoxy(6,15);
						type("2. Cameroon");
						gotoxy(6,16);
						type("3. Thailand");
						gotoxy(6,17);
						type("4. Morocco");
						correct=51;
					}
					}
				if(quest==3){	
					gotoxy(6,13);
					type("Select the capital of Australia");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. Sidney");
						gotoxy(6,15);
						type("2. Canberra");
						gotoxy(6,16);
						type("3. Madrid");
						gotoxy(6,17);
						type("4. Tripoli");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. Canberra");
						gotoxy(6,15);
						type("2. Madrid");
						gotoxy(6,16);
						type("3. Tripoli");
						gotoxy(6,17);
						type("4. Sidney");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. Tripoli");
						gotoxy(6,15);
						type("2. Sidney");
						gotoxy(6,16);
						type("3. Madrid");
						gotoxy(6,17);
						type("4. Canberra");
						correct=52;
					}
				}
				break;
			case 23:
				if(quest==1){//HISTORY
					gotoxy(6,13);
					type("World War I began in which year?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. 1923");
						gotoxy(6,15);
						type("2. 1914");
						gotoxy(6,16);
						type("3. 1917");
						gotoxy(6,17);
						type("4. 1938");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. 1914");
						gotoxy(6,15);
						type("2. 1917");
						gotoxy(6,16);
						type("3. 1938");
						gotoxy(6,17);
						type("4. 1923");
						correct=49;
					}
					if(ans==3){	
						gotoxy(6,14);
						type("1. 1917");
						gotoxy(6,15);
						type("2. 1923");
						gotoxy(6,16);
						type("3. 1938");
						gotoxy(6,17);
						type("4. 1914");
						correct=52;
					}
				}
				if(quest==2){	
					gotoxy(6,13);
					type("Konstantinopel fell in which year?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. 1821");
						gotoxy(6,15);
						type("2. 1453");
						gotoxy(6,16);
						type("3. 1512");
						gotoxy(6,17);
						type("4. 1942");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. 1453");
						gotoxy(6,15);
						type("2. 1821");
						gotoxy(6,16);
						type("3. 1942");
						gotoxy(6,17);
						type("4. 1512");
						correct=49;
					}
					if(ans==3){	
						gotoxy(6,14);
						type("1. 1512");
						gotoxy(6,15);
						type("2. 1942");
						gotoxy(6,16);
						type("3. 1453");
						gotoxy(6,17);
						type("4. 1821");
						correct=51;
					}
				}
				if(quest==3){	
					gotoxy(6,13);
					type("When did the French Revolution start?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. 1799");
						gotoxy(6,15);
						type("2. 1789");
						gotoxy(6,16);
						type("3. 1612");
						gotoxy(6,17);
						type("4. 1453");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. 1789");
						gotoxy(6,15);
						type("2. 1612");
						gotoxy(6,16);
						type("3. 1453");
						gotoxy(6,17);
						type("4. 1799");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. 1799");
						gotoxy(6,15);
						type("2. 1453");
						gotoxy(6,16);
						type("3. 1612");
						gotoxy(6,17);
						type("4. 1789");
						correct=52;
					}
				}
				break;
			case 24:
				if (quest==1){//MATHS
					gotoxy(6,13);
					type("A^2-2AB+B^2=?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. (A+B)^2");
						gotoxy(6,15);
						type("2. (A-B)^2");
						gotoxy(6,16);
						type("3. A^2-B^2");
						gotoxy(6,17);
						type("4. A^2+B^2");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. (A-B)^2");
						gotoxy(6,15);
						type("2. A^2-B^2");
						gotoxy(6,16);
						type("3. A^2+B^2");
						gotoxy(6,17);
						type("4. (A+B)^2");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. A^2-B^2");
						gotoxy(6,15);
						type("2. A^2+B^2");
						gotoxy(6,16);
						type("3. (A+B)^2");
						gotoxy(6,17);
						type("4. (A-B)^2");
						correct=52;
					}
				}
				if(quest==2){	
					gotoxy(6,13);
					type("1/5+1/3=?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. 2/8");
						gotoxy(6,15);
						type("2. 8/15");
						gotoxy(6,16);
						type("3. 8/30");
						gotoxy(6,17);
						type("4. 1/8");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. 8/15");
						gotoxy(6,15);
						type("2. 8/30");
						gotoxy(6,16);
						type("3. 1/8");
						gotoxy(6,17);
						type("4. 2/8");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. 2/8");
						gotoxy(6,15);
						type("2. 1/8");
						gotoxy(6,16);
						type("3. 8/15");
						gotoxy(6,17);
						type("4. 8/30");
						correct=51;
					}
				}
				if(quest==3){	
					gotoxy(6,13);
					type("(-2)*(-6)=?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. 4");
						gotoxy(6,15);
						type("2. 12");
						gotoxy(6,16);
						type("3. -8");
						gotoxy(6,17);
						type("4. -12");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. 12");
						gotoxy(6,15);
						type("2. -8");
						gotoxy(6,16);
						type("3. -12");
						gotoxy(6,17);
						type("4. 4");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. -12");
						gotoxy(6,15);
						type("2. 4");
						gotoxy(6,16);
						type("3. -8");
						gotoxy(6,17);
						type("4. 12");
						correct=52;
					}
				}
				break;
			case 25:
				gotoxy(6,13);//GREEK MASTER
				type("Which was Achilles' vulnerability?");
				sleep(1);
				if(ans==1){
					gotoxy(6,14);
					type("1. His long hair");
					gotoxy(6,15);
					type("2. His heel");
					gotoxy(6,16);
					type("3. Trusting his wife");
					gotoxy(6,17);
					type("4. He was invulnerable");
					correct=50;
				}
				if(ans==2){	
					gotoxy(6,14);
					type("1. His heel");
					gotoxy(6,15);
					type("2. Trusting his wife");
					gotoxy(6,16);
					type("3. He was invulnerable");
					gotoxy(6,17);
					type("4. His long hair");
					correct=49;
				}
				if(ans==3){
					gotoxy(6,14);
					type("1. Trusting his wife");
					gotoxy(6,15);
					type("2. He was invulnerable");
					gotoxy(6,16);
					type("3. His long hair");
					gotoxy(6,17);
					type("4. His heel");
					correct=52;
				}
				do{
					r=getch();
				}while ((r!=49)&&(r!=50)&&(r!=51)&&(r!=52));
				if(r==correct) cho=1;
				sleep(1);
				if(cho==1){	
					ans=(rand()%3)+1;
					gotoxy(60,15);
					type("!Correct!");
					sleep(1);
					gotoxy(6,13);
					printf("                                     ");
					gotoxy(6,14);
					printf("                                     ");
					gotoxy(6,15);
					printf("                                     ");
					gotoxy(6,16);
					printf("                                     ");
					gotoxy(6,17);
					printf("                                     ");
					cho=0;
					gotoxy(60,15);
					type("            ");
					gotoxy(6,13);
					type("Who is the Father of Philosophy?");
					sleep(1);
					if(ans==1){
						gotoxy(6,14);
						type("1. Platonas");
						gotoxy(6,15);
						type("2. Socrates");
						gotoxy(6,16);
						type("3. Aristoteles");
						gotoxy(6,17);
						type("4. Ippokrates");
						correct=50;
					}
					if(ans==2){	
						gotoxy(6,14);
						type("1. Socrates");
						gotoxy(6,15);
						type("2. Aristoteles");
						gotoxy(6,16);
						type("3. Ippokrates");
						gotoxy(6,17);
						type("4. Platonas");
						correct=49;
					}
					if(ans==3){
						gotoxy(6,14);
						type("1. Ippokrates");
						gotoxy(6,15);
						type("2. Platonas");
						gotoxy(6,16);
						type("3. Sokrates");
						gotoxy(6,17);
						type("4. Aristoteles");
						correct=51;
					}
					do{
						r=getch();
					}while ((r!=49)&&(r!=50)&&(r!=51)&&(r!=52));
					if(r==correct)cho=1;
					sleep(1);
					if(cho==1){	
						ans=(rand()%3)+1;
						gotoxy(60,15);
						type("!Correct!");
						sleep(1);
						gotoxy(6,13);
						printf("                                     ");
						gotoxy(6,14);
						printf("                                     ");
						gotoxy(6,15);
						printf("                                     ");
						gotoxy(6,16);
						printf("                                     ");
						gotoxy(6,17);
						printf("                                     ");
						cho=0;
						gotoxy(60,15);
						type("            ");
						gotoxy(6,13);
						type("Who built the Parthenon?");
						sleep(1);
						if(ans==1){
							gotoxy(6,14);
							type("1. Kyrillos & Methodius");
							gotoxy(6,15);
							type("2. Iktinos & Kallikrates");
							gotoxy(6,16);
							type("3. Phidias");
							gotoxy(6,17);
							type("4. Pythia & Tiresias");
							correct=50;
						}
						if(ans==2){	
							gotoxy(6,14);
							type("1. Iktinos & Kallikrates");
							gotoxy(6,15);
							type("2. Pythia & Tiresias");
							gotoxy(6,16);
							type("3. Kyrillos & Methodius");
							gotoxy(6,17);
							type("4. Phidias");
							correct=49;
						}
						if(ans==3){
							gotoxy(6,14);
							type("1. Kyrillos & Methodius");
							gotoxy(6,15);
							type("2. Phidias");
							gotoxy(6,16);
							type("3. Pythia & Tiresias");
							gotoxy(6,17);
							type("4. Iktinos & Kallikrates");
							correct=52;
						}
						do{
							r=getch();
						}while ((r!=49)&&(r!=50)&&(r!=51)&&(r!=52));
						if(r==correct) cho=1;
						return cho;
					}
					return cho;
				}
				return cho;		
		}
		
		do{
			r=getch();
		}while ((r!=49)&&(r!=50)&&(r!=51)&&(r!=52)); 
		if(r==correct) cho=1;							 
		return cho;
	}
}
////////////////
void battle (int m,int ehp,int eatk,int earmor,int pot,int hp,int* newhp,int*newpot,int maxhp,int atk,int armor,int lvl){ 	int damage,hurt,round=1,luck;
	char p;
	srand(time(0));
	luck=(rand()%3)+1;//5.% pithanothta na pai3oun ola ta terata prwta
	if((luck==1)){		
		while(hp>0 && ehp>0){	
			system("cls");
			printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
			printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
			printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
			printf("ROUND %d\n\n\n",round);
			sleep(1);
			if (pot>0){
				printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				p=getch();
				if ((p=='p')||(p=='P')){	
					hp+=55;
					if (hp>maxhp)	hp=maxhp;
					pot--;
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
					printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
					printf("ROUND %d\n\n\n",round);
					printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				}
			}
			sleep(1);
			if (hp > 0){	
				damage = atk - earmor;
				printf ("You hit for %d damage\n\n", damage);
				ehp-=damage;
				system("cls");
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
				printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
				if (ehp<0)	ehp = 0;
				printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
				printf("ROUND %d\n\n\n",round);
				if (pot>0) printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				printf ("You hit for %d damage\n\n", damage);
				sleep(1);
				if (ehp < 1) printf ("\n\n\nYou have killed the enemy\n");
				sleep(1);
				if (ehp == 0){
					printf ("\nThe gigantic %s is DEAD!\n\n", e [m].name);
					pressenter ();
					*newpot=pot;
					*newhp=hp;
				}
			}
			if (ehp > 0){
				hurt = eatk - armor;
				hp-=hurt;
				system("cls");
				if (hp<0) hp = 0;
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
				printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
				printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
				printf("ROUND %d\n\n\n",round);
				if (pot>0) printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				printf ("You hit for %d damage\n\n", damage);
				printf ("%s hits for %d damage\n\n",e [m].name, hurt);
				sleep(1);
				round++;
				if (hp == 0){	
					printf ("\n\n\nYou LOST!\n");
					sleep(1);
					*newpot=pot;
					*newhp=hp;
				}
			}
		}
	}
	else{
		while(hp>0 && ehp>0){	
			system("cls");
			printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
			printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
			printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
			printf("ROUND %d\n\n\n",round);
			sleep(1);
			if (pot>0){
				printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				p=getch();
				if ((p=='p')||(p=='P')){	
					hp+=55;
					if (hp>maxhp)	hp=maxhp;
					pot--;
					system("cls");
					printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
					printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
					printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
					printf("ROUND %d\n\n\n",round);
					printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				}
			}
			sleep(1);
			if (ehp > 0){	
				hurt = eatk - armor;
				printf ("%s hits for %d damage\n",e [m].name, hurt);
				hp-=hurt;
				system("cls");
				if (hp<0) hp = 0;
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
				printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
				printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
				printf("ROUND %d\n\n\n",round);
				if (pot>0) printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				printf ("%s hits for %d damage\n\n",e [m].name, hurt);
				sleep(1);
				if (hp == 0){	
					printf ("\n\n\nYou LOST!\n");
					sleep(1);
					*newpot=pot;
					*newhp=hp;
				}
			}
			if (hp > 0){
				damage = atk - earmor;
				ehp-=damage;
				system("cls");
				printf("LVL:%d \t HP:%d\t Weapon:%s\t Atk:%d \t Armor%d \t Potions:%d\n",lvl+1,hp,w [lvl].name,atk,armor,pot);
				printf ("\nYou are in combat with a gigantic  %s\n", e [m].name);
				if (ehp<0)  ehp = 0;
				printf ("%s's HP:%d\n\n\n",e [m].name,ehp);
				printf("ROUND %d\n\n\n",round);
				if (pot>0)printf ("If you want to use a potion press <P>\n\t-OR-\nPress any key to continue\n\n\n ");
				printf ("%s hits for %d damage\n\n",e [m].name, hurt);
				printf ("You hit for %d damage\n\n", damage);
				sleep(1);
				round++;
				if (ehp < 1) printf ("\n\n\nYou have killed the enemy\n");
				sleep(1);
				if(ehp == 0){
					printf ("\nThe gigantic %s is DEAD!\n\n", e [m].name);
					pressenter ();
					*newpot=pot;
					*newhp=hp;
				}
			}
		}
	}
}
