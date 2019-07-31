#include <SFML/Graphics.hpp>
#include <SFML/Window/Export.hpp>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <sstream>
using namespace sf;
using namespace std;


int rnd (void);//random num between 1 - 4
////pac_man move
void move_up(void);
void move_down(void);
void move_right(void);
void move_left(void);
////
////check for ghosts
int check_up (int x, int y);
int check_dw (int x, int y);
int check_ri (int x, int y);
int check_lf (int x, int y);
////
struct ghost_location {
    int x;
    int y;
};

void manual_move_ghost (void);
bool x,y;
int main_counter=0;//counter for manual move and pac-man texture
int r;//random int
int i,j,k;
/////ghost location in manual_move
int ghost1_x=13;
int ghost1_y=10;
int ghost2_x=14;
int ghost2_y=10;
int ghost3_x=15;
int ghost3_y=10;
int ghost4_x=16;
int ghost4_y=10;
////
char move_pac;
char move_pac_temp;
int pack_x=15;
int pack_y=18;
char b[30][30]={
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','#','#','#','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','.','.','#','#','.','#','.','#','#','.','#','.','#','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','#','#','#','#','#','#','.','#','.','.','.','.','#','.','#','#','#','#','#','#','#','#','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#','.','.','.','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','.','#','.','#','#','#','.','#','.','#','#','#','#','#','#','.','#','.','#','#','#','.','#','.','#','.','#'},
        {'#','.','.','.','#','.','#','#','#','.','#','.',' ',' ',' ',' ',' ',' ','.','#','.','#','#','#','.','#','.','.','.','#'},
        {'#','#','#','.','#','.','#','#','#','.','#','.','#','#',' ',' ','#','#','.','#','.','#','#','#','.','#','.','#','#','#'},
        {'#','#','#','.','.','.','.','.','.','.','.','.','#','1','2','3','4','#','.','.','.','.','.','.','.','.','.','#','#','#'},
        {'#','#','#','.','#','#','#','#','#','#','#','.','#','#','#','#','#','#','.','#','#','#','#','#','#','#','.','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','.','.','.','.','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','#','.','.','.','#','.','#','#','.','#','.','#','#','.','#','.','#','#','.','#','.','.','.','#','#','.','#'},
        {'#','.','#','#','.','#','.','.','.','#','#','.','#','.','#','#','.','#','.','#','#','.','.','.','#','.','#','#','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','.','#','#','.','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','.','.','.','.','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','.','.','.','#','.','#','#','.','#','.','.','.','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','.','#','#','.','#','#','#','#','.','#','.','#','#','.','#','.','#','#','#','#','.','#','#','.','#','.','#'},
        {'#','.','.','.','#','#','.','#','#','#','#','.','#','.','#','#','.','#','.','#','#','#','#','.','#','#','.','.','.','#'},
        {'#','.','#','.','#','#','.','#','#','#','#','.','#','.','.','.','.','#','.','#','#','#','#','.','#','#','.','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','#','#','.','#','.','#','#','.','#','.','#','#','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','#','#','#','#','#','.','#','#','.','.','.','#','#','.','.','.','#','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','.','.','#','#','.','#','#','#','#','#','#','.','#','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#','.','#'},
        {'#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
        };//the map for ghosts
char a[30][30]={
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','#','#','#','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','.','o','#','#','.','#','.','#','#','.','#','.','#','#','o','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','#','#','#','#','#','#','#','.','#','.','.','.','.','#','.','#','#','#','#','#','#','#','#','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#','.','.','.','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','.','#','.','#','#','#','.','#','.','#','#','#','#','#','#','.','#','.','#','#','#','.','#','.','#','.','#'},
        {'#','o','.','.','#','.','#','#','#','.','#','.',' ',' ',' ',' ',' ',' ','.','#','.','#','#','#','.','#','.','.','o','#'},
        {'#','#','#','.','#','.','#','#','#','o','#','.','#','#',' ',' ','#','#','.','#','o','#','#','#','.','#','.','#','#','#'},
        {'#','#','#','.','.','.','.','.','.','.','.','.','#',' ',' ',' ',' ','#','.','.','.','.','.','.','.','.','.','#','#','#'},
        {'#','#','#','.','#','#','#','#','#','#','#','.','#','#','#','#','#','#','.','#','#','#','#','#','#','#','.','#','#','#'},
        {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','.','.','.','.','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','#','.','.','.','#','.','#','#','.','#','.','#','#','.','#','.','#','#','.','#','.','.','.','#','#','.','#'},
        {'#','.','#','#','.','#','o','.','.','#','#','.','#','.','#','#','.','#','.','#','#','.','.','o','#','.','#','#','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','.','#','#','.','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','#','.','#','#','#','.','#','#','.','#','.','.','@','.','#','.','#','#','.','#','#','#','.','#','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','.','.','.','#','.','#','#','.','#','.','.','.','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','.','#','#','.','#','#','#','#','.','#','.','#','#','.','#','.','#','#','#','#','.','#','#','.','#','.','#'},
        {'#','.','.','.','#','#','.','#','#','#','#','.','#','.','#','#','.','#','.','#','#','#','#','.','#','#','.','.','.','#'},
        {'#','.','#','.','#','#','.','#','#','#','#','.','#','.','.','.','.','#','.','#','#','#','#','.','#','#','.','#','.','#'},
        {'#','.','#','.','.','.','.','.','.','#','#','.','#','.','#','#','.','#','.','#','#','.','.','.','.','.','.','#','.','#'},
        {'#','.','#','#','#','#','#','#','.','#','#','.','.','.','#','#','.','.','.','#','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','o','.','.','.','.','.','.','#','#','.','#','#','#','#','#','#','.','#','#','.','.','.','.','.','.','o','.','#'},
        {'#','.','#','#','#','#','#','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','#','#','#','#','#','.','#'},
        {'#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','.','#'},
        {'#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','#'},
        {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
        };
    int main (){
    Time tt;
    Time pc_t;
    Time gh_t;
    Time load;
    Clock clock_ghost;
    Clock clock_pac;
    load = seconds(1);
    tt = seconds(0.15);
    srand (time(NULL));
    ghost_location ghost[4];
    ///////GHOST-LOCATION------------
    ghost[0].x=12;
    ghost[0].y=8;
    ghost[1].x=11;
    ghost[1].y=6;
    ghost[2].x=18;
    ghost[2].y=10;
    ghost[3].x=17;
    ghost[3].y=8;
    ///////--------------------------
    ///////TEXTURE & SHAPE-----------
        ContextSettings setting;
        setting.antialiasingLevel=32;
        setting.depthBits=32;
        RenderWindow window(VideoMode(1100,900),"PAC-MAN",Style::Default,setting);
        //
        CircleShape pacman (10.f);
        pacman.setFillColor(Color::Yellow);
        //
        CircleShape food (2.f);
        food.setFillColor(Color::Yellow);
        //
        Texture door;
        if (!door.loadFromFile("door.png")){
            printf("error");
        }
        door.setSmooth(true);
        Sprite Spritedoor(door);
        //
        Texture wall;
        if (!wall.loadFromFile("wall.png")){
            printf("error");
        }
        wall.setSmooth(true);
        Sprite Spritewall(wall);
        //
        Texture sfml;
        if (!sfml.loadFromFile("sfml.png")){
            printf("error");
        }
        sfml.setSmooth(true);
        Sprite Spritesf(sfml);
        //
        Texture foodd;
        if (!foodd.loadFromFile("food.png")){
            printf("error");
        }
        foodd.setSmooth(true);
        Sprite Spritefood (foodd);
        //
        Texture ghost1;
        if (!ghost1.loadFromFile("pink.png")){
            printf("error");
        }
        ghost1.setSmooth(true);
        Sprite Spritegho1(ghost1);
        //

        Texture ghost2;
        if (!ghost2.loadFromFile("blue.png")){
            printf("error");
        }
        ghost2.setSmooth(true);
        Sprite Spritegho2(ghost2);
        //

        Texture ghost3;
        if (!ghost3.loadFromFile("orange.png")){
            printf("error");
        }
        ghost3.setSmooth(true);
        Sprite Spritegho3(ghost3);
        //

        Texture ghost4;
        if (!ghost4.loadFromFile("red.png")){
            printf("error");
        }
        ghost4.setSmooth(true);
        Sprite Spritegho4(ghost4);
        ///////----------------

        while(window.isOpen()){
            Event event;
            while (window.pollEvent(event)){
                if (event.type == Event::Closed)
                    window.close();
            }

        /////////SHOW---------------------------------------------------
            window.clear();
            if (main_counter<1){//first credit and loading
            Spritesf.setPosition(285,290);
            window.draw(Spritesf);
            window.display();
            sleep(load);
            window.clear();
            }
            for (i=0;i<30;i++){
                for (j=0;j<30;j++){
                        //printf("%2c",b[i][j]);
                    if (a[j][i] == '#'){
                        Spritewall.setPosition ((i*30)+100,j*30);
                        window.draw(Spritewall);
                    }
                    else if (a[j][i] == '.'){
                        food.setPosition (((i*30)+13)+100,(j*30)+13);
                        window.draw(food);
                    }
                    else if (a[j][i] == 'o'){
                        Spritefood.setPosition (((i*30))+100,(j*30));
                        window.draw(Spritefood);
                    }
                    else if (a[j][i] == '@'){
                        pacman.setPosition (((i*30)+5)+100,(j*30)+5);
                        window.draw(pacman);
                    }
                    else if (a[j][i] == '$'){
                        Spritedoor.setPosition (((i*30))+100,(j*30));
                        window.draw(Spritedoor);
                    }
                    if(main_counter<8){
                        //
                        Spritegho1.setPosition ((ghost1_x*30)+100,(ghost1_y*30));
                        window.draw(Spritegho1);
                        //
                        Spritegho2.setPosition ((ghost2_x*30)+100,(ghost2_y*30));
                        window.draw(Spritegho2);
                        //
                        Spritegho3.setPosition ((ghost3_x*30)+100,(ghost3_y*30));
                        window.draw(Spritegho3);
                        //
                        Spritegho4.setPosition ((ghost4_x*30)+100,(ghost4_y*30));
                        window.draw(Spritegho4);
                        //

                    }
                    if(main_counter>7){
                        //
                        Spritegho1.setPosition ((ghost[0].x*30)+100,(ghost[0].y*30));
                        window.draw(Spritegho1);
                        //
                        Spritegho2.setPosition ((ghost[1].x*30)+100,(ghost[1].y*30));
                        window.draw(Spritegho2);
                        //
                        Spritegho3.setPosition ((ghost[2].x*30)+100,(ghost[2].y*30));
                        window.draw(Spritegho3);
                        //
                        Spritegho4.setPosition ((ghost[3].x*30)+100,(ghost[3].y*30));
                        window.draw(Spritegho4);
                        //
                    }

                }
                //printf ("\n");
        }
        window.display();
        /////////////------------------------------------------------

        ///////////INPUT---------------------------------------------
        if(event.type == Event::KeyPressed){

                if(Keyboard::isKeyPressed(Keyboard::Up)){
                        move_pac= 'w';
                }
                if(Keyboard::isKeyPressed(Keyboard::Left) ){
                        move_pac= 'a';
                }
                if(Keyboard::isKeyPressed(Keyboard::Down) ){
                        move_pac= 's';
                }
                if(Keyboard::isKeyPressed(Keyboard::Right) ){
                        move_pac= 'd';
                }
                }
        ///////////--------------------------------------------------

        ////////MOVE-------------------------------------------------
            pc_t = clock_pac.getElapsedTime();
            if (pc_t.asMilliseconds() > 150){
                //main up move
                if(move_pac == 'w' && a[pack_y-1][pack_x] != '#' && a[pack_y-1][pack_x] != '$'){
                            move_up();
                            move_pac_temp= 'w';
                }
                else if (move_pac == 'w' && a[pack_y-1][pack_x] == '#'){
                    //printf("wwwwwwww\n");
                }
                //main  right move
                else if(move_pac == 'd' && a[pack_y][pack_x+1] != '#' && a[pack_y][pack_x+1] != '$' ){
                            move_right();
                            move_pac_temp= 'd';

                }
                else if (move_pac == 'd' && a[pack_y][pack_x+1] == '#' ){
                    //printf("dddddddddddd\n");
                }
                //main down move
                else if(move_pac == 's' && a[pack_y+1][pack_x] != '#' && a[pack_y+1][pack_x] != '$'){
                            move_down();
                            move_pac_temp= 's';

                }
                else if (move_pac == 's' && a[pack_y+1][pack_x] == '#'){
                    //printf("ssssssss\n");
                }
                //main left move
                else if(move_pac == 'a' && a[pack_y][pack_x-1] != '#'  && a[pack_y][pack_x-1] != '$'){
                            move_left();
                            move_pac_temp= 'a';

                }
                else if (move_pac == 'a' && a[pack_y][pack_x-1] == '#'){
                    //printf ("aaaaaaa\n");
                }
                clock_pac.restart();
            }
        //////////---------------------------------------------

        /////////GHOST-MOVE------------------------------------

        if(main_counter<8)
        manual_move_ghost();
        else {
            gh_t = clock_ghost.getElapsedTime();
            if (gh_t.asMilliseconds() > 150){
            for (k=0;k<=3;k++){
/*

                    ////
                    //while (1){
		int Node_y =pack_x - ghost[k].x;
		int Node_x =pack_y - ghost[k].y;
		printf ("%d \t %d ",Node_x,Node_y);
		//system("pause");
		if (x == true){
			if (Node_y > 0){

				if( (check_ri(ghost[k].x , ghost[k].y)) == 0 || b[ghost[k].y-1][ghost[k].x] != '$'){

					if ( (check_ri(ghost[k].x , ghost[k].y)) != 1){
						//printf("boro bala\n");
						b[ghost[k].y][ghost[k].x]=' ';
						ghost[k].y -- ;
						b[ghost[x].y][ghost[k].x]=k;
						//show();
						//Sleep(250);
						//system("cls");
					}
				}
					//a[e_x][e_y]=' ';
					//e_y ++ ;
					//a[e_x][e_y]='E';

			}
			if (Node_y < 0){
				if( check_lf(ghost[k].x , ghost[k].y) == 0 ){
					if ( check_lf(ghost[k].x , ghost[k].y) != 1){
						printf("boro bala\n");
						b[ghost[k].y][ghost[k].x]=' ';
						ghost[k].y -- ;
						b[ghost[k].y][ghost[k].x]=k;
						//show();
						//Sleep(250);
						//system("cls");

					}
				}
			//	a[e_x][e_y]=' ';
			//	e_y -- ;
			//	a[e_x][e_y]='E';

			}
			//show();
		//	Sleep(500);
			//system("cls");
			x = false;
		}
		/*else if ( y== true){
			if (Node_x > 0){
				if( (ch_d(e_x , e_y)) == 1 ){
					while ( (ch_d(e_x , e_y)) != 0){
						printf("boro pain\n");
					}
				}
			}
			else if (Node_x < 0){
			printf("bala\n");
			}
		}
		else{
		//win
		if (Node_x == 0 && Node_y == 0){
			system("cls");
			printf(" YOU LOST \n");
			Sleep(1000);
			return 0 ;
		}
		//X
		if ((main_counter)%2 == 0){
		if (Node_x > 0){

			if ( a[(ghost[k].y + 1)][ghost[k].x] != '#'){
				b[ghost[k].y][ghost[k].x]=' ';
				ghost[k].y ++ ;
				b[ghost[k].y][ghost[k].x]=k;
			}
			main_counter++;
		}
		else if (Node_x <0){

			if ( a[(ghost[k].y - 1)][ghost[k].x] != '#'){
				b[ghost[k].y][ghost[k].x]=' ';
				ghost[k].y -- ;
				b[ghost[k].y][ghost[k].x]='E';
			}
			main_counter++;
		}
		else if (Node_x == 0){
			printf (" x is synced\n");
			main_counter++;
			x=true;
		}
		//show();
		//Sleep(250);
		//system("cls");
	}

		// Y
		if ((main_counter)%2 == 1){
		if(Node_y > 0) {
			if ( a[(ghost[k].y)][ghost[k].x+1] != '#'){
				b[ghost[k].y][ghost[k].x]=' ';
				ghost[k].x ++ ;
				b[ghost[k].y][ghost[k].x]='E';
			}
			main_counter++;
		}
		else if (Node_y < 0){
			if ( a[(ghost[k].y)][ghost[k].x - 1] != '#'){
				b[ghost[k].y][ghost[k].x]=' ';
				ghost[k].x -- ;
				b[ghost[k].y][ghost[k].x]='E';
			}
			main_counter++;
		}
		else if (Node_y == 0){
			printf (" y is synced\n");
			main_counter++;
			y = true;
		}
		//show();
		//Sleep(250);
		//system("cls");
		}
	}
//}

*/

                    ////


            while (1){
            r=rnd();
        //printf("\n\t%d\t\n",r);
        if (r==1 && check_up(ghost[k].x,ghost[k].y)==1 ){

                if (b[ghost[k].y][ghost[k].x-1]=='1' || b[ghost[k].y][ghost[k].x-1]=='2'|| b[ghost[k].y][ghost[k].x-1]=='3' || b[ghost[k].y][ghost[k].x-1]=='4')
                    break;

                char temp;
                temp=b[ghost[k].y-1][ghost[k].x];
                if (temp == '1' || temp == '2' || temp == '3' || temp == '4')
                    break;
                b[ghost[k].y][ghost[k].x]= temp;
                ghost[k].y--;

                if(k==0){
                    b[ghost[k].y][ghost[k].x]= '1';
                }
                else if (k==1){
                    b[ghost[k].y][ghost[k].x]= '2';
                }
                else if (k==2){
                    b[ghost[k].y][ghost[k].x]= '3';
                }
                else if (k==3){
                    b[ghost[k].y][ghost[k].x]= '4';
                }
        break;
        }

            if (r==2 && check_ri(ghost[k].x,ghost[k].y)==1 ){

                if (b[ghost[k].y][ghost[k].x-1]=='1' || b[ghost[k].y][ghost[k].x-1]=='2'|| b[ghost[k].y][ghost[k].x-1]=='3' || b[ghost[k].y][ghost[k].x-1]=='4')
                    break;

                char temp;
                temp=b[ghost[k].y][ghost[k].x+1];
                if (temp == '1' || temp == '2' || temp == '3' || temp == '4')
                    break;
                b[ghost[k].y][ghost[k].x]= temp;
                ghost[k].x++;

                if(k==0){
                    b[ghost[k].y][ghost[k].x]= '1';
                }
                else if (k==1){
                    b[ghost[k].y][ghost[k].x]= '2';
                }
                else if (k==2){
                    b[ghost[k].y][ghost[k].x]= '3';
                }
                else if (k==3){
                    b[ghost[k].y][ghost[k].x]= '4';
                }
        break;
        }

            if (r==3 && check_dw(ghost[k].x,ghost[k].y)==1 ) {

                if (b[ghost[k].y][ghost[k].x-1]=='1' || b[ghost[k].y][ghost[k].x-1]=='2'|| b[ghost[k].y][ghost[k].x-1]=='3' || b[ghost[k].y][ghost[k].x-1]=='4')
                    break;

                char temp;
                temp=b[ghost[k].y+1][ghost[k].x];
                if (temp == '1' || temp == '2' || temp == '3' || temp == '4')
                    break;
                b[ghost[k].y][ghost[k].x]= temp;
                ghost[k].y++;

                if(k==0){
                    b[ghost[k].y][ghost[k].x]= '1';
                }
                else if (k==1){
                    b[ghost[k].y][ghost[k].x]= '2';
                }
                else if (k==2){
                    b[ghost[k].y][ghost[k].x]= '3';
                }
                else if (k==3){
                    b[ghost[k].y][ghost[k].x]= '4';
                }
        break;
        }

            if (r==4 && check_lf(ghost[k].x,ghost[k].y)==1 ) {

                if ( b[ghost[k].y][ghost[k].x-1]=='1' || b[ghost[k].y][ghost[k].x-1]=='2'|| b[ghost[k].y][ghost[k].x-1]=='3' || b[ghost[k].y][ghost[k].x-1]=='4')
                    break;

                char temp;
                temp=b[ghost[k].y][ghost[k].x-1];
                if (temp == '1' || temp == '2' || temp == '3' || temp == '4')
                    break;
                b[ghost[k].y][ghost[k].x]= temp;
                ghost[k].x--;

                if(k==0){
                    b[ghost[k].y][ghost[k].x]= '1';
                }
                else if (k==1){
                    b[ghost[k].y][ghost[k].x]= '2';
                }
                else if (k==2){
                    b[ghost[k].y][ghost[k].x]= '3';
                }
                else if (k==3){
                    b[ghost[k].y][ghost[k].x]= '4';
                }
        break;
        }
        }*/
        }
        clock_ghost.restart();
        }
        }
        ///////////---------------------------------------------

        //sleep (tt);
        main_counter++;
        //system ("pause");
        ////////score---------------------

        int g=0;
        for (i=0;i<30;i++){
            for (j=0;j<30;j++){
                if (a[j][i] == '.'){
                    g++;
                   }
                }
            }
            int k=381-g;
            //printf ("%d\n",k);
            if (g == 0){
                printf("YOU WIN");
                window.close();
                break;
            }
        ////////--------------------------
    }

       return 0;
}
    void manual_move_ghost (void){
    if ( main_counter<2){
            b[ghost2_y][ghost2_x]=' ';
            b[ghost3_y][ghost3_x]=' ';
            ghost2_y--;
            b[ghost2_y][ghost2_x]='2';
            ghost3_y--;
            b[ghost3_y][ghost3_x]='3';
        }
        if (main_counter<1){
            b[ghost1_y][ghost1_x]=' ';
            b[ghost4_y][ghost4_x]=' ';
            ghost1_x++;
            ghost4_x--;
            b[ghost1_y][ghost1_x]='1';
            b[ghost4_y][ghost4_x]='4';
        }
        if (main_counter>3 && main_counter<6){
            b[ghost1_y][ghost1_x]=' ';
            b[ghost4_y][ghost4_x]=' ';
            ghost1_y--;
            b[ghost1_y][ghost1_x]='1';
            ghost4_y--;
            b[ghost4_y][ghost4_x]='4';
        }
        if (main_counter>2 && main_counter<6){
            b[ghost2_y][ghost2_x]=' ';
            b[ghost3_y][ghost3_x]=' ';
            ghost2_x--;
            b[ghost2_y][ghost2_x]='2';
            ghost3_x++;
            b[ghost3_y][ghost3_x]='3';
        }
        if(main_counter>5 && main_counter<8 ){
            b[ghost2_y][ghost2_x]=' ';
            b[ghost3_y][ghost3_x]=' ';
            ghost2_y--;
            b[ghost2_y][ghost2_x]='2';
            ghost3_y++;
            b[ghost3_y][ghost3_x]='3';
            //
            b[ghost1_y][ghost1_x]=' ';
            b[ghost4_y][ghost4_x]=' ';
            ghost1_x--;
            b[ghost1_y][ghost1_x]='1';
            ghost4_x++;
            b[ghost4_y][ghost4_x]='4';
            b[9][14]='#';
            b[9][15]='#';
            a[9][14]='$';
            a[9][15]='$';
        }
}
int rnd (void){
    int k;
    k=(rand()%4)+1;
    return k;
}

int check_up (int x, int y){
    if (b[y-1][x]!='#' )
        return 1;
    else
        return 0;
}
int check_dw (int x, int y){
    if (b[y+1][x]!='#')
        return 1;
    else
        return 0;
}
int check_ri (int x, int y){
    if (b[y][x+1]!='#')
        return 1;
    else
        return 0;
}
int check_lf (int x, int y){
    if (b[y][x-1]!='#')
        return 1;
    else
        return 0;
}

void move_up(void){
    a[pack_y][pack_x]=' ';
    pack_y--;
    a[pack_y][pack_x]='@';
}
void move_down(void){
    a[pack_y][pack_x]=' ';
    pack_y ++ ;
    a[pack_y][pack_x]='@';
}
void move_right(void){
    a[pack_y][pack_x]=' ';
    pack_x ++ ;
    a[pack_y][pack_x]='@';
}
void move_left(void){
    a[pack_y][pack_x]=' ';
    pack_x -- ;
    a[pack_y][pack_x]='@';

}
