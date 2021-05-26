#include <Windows.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <gl/glut.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include <dos.h>

char string[100];
bool run=false;
bool lost=false;
int ball_num=1;
float circ_x=100 , circ_y=110 , circ_r=10;
float circ2_x=500 , circ2_y=110 ;
int speed =2 , playerResult=0 , pcResult=0;
static float Xspeed = 0.5, Yspeed = 0.5;
static float Xspeed2 = 0.5, Yspeed2 = 0.5;
static float delta = 1;
struct moraba{
	float left, top, right, bottom;
};

moraba wall;
moraba player = { 0,390,40,400 };

void DrawRectangle(moraba  rect){
	glBegin(GL_QUADS);
	glVertex2f(rect.left, rect.bottom);
	glVertex2f(rect.right, rect.bottom);
	glVertex2f(rect.right, rect.top);
	glVertex2f(rect.left, rect.top);
	glEnd();
}

void Timer(int v){
    circ_y += Yspeed;
    circ_x += Xspeed;
	glutTimerFunc(speed, Timer, 1);  // 2ms , 1 ra pas midahad
}

void Timer2(int v){
       circ2_y += Yspeed2;
        circ2_x += Xspeed2;
        glutTimerFunc(speed, Timer2, 1);
}

void Test_Ball_Wall(float x , float y , float r,moraba wall , float speed_x , float speed_y){
    if (speed_x==Xspeed && speed_y==Yspeed){
        if (x + r >= wall.right){
            Xspeed = -delta;
        }
        if (x - r <= wall.left){
                Xspeed = delta;
        }
        if (y - r <= wall.top){
            Yspeed=delta;
        }

        if (y + r + 1>= wall.bottom){
            pcResult += 1;
            Yspeed=-delta;
        }
    }
    else if (speed_x==Xspeed2 && speed_y==Yspeed2){
        if (x + r >= wall.right){
            Xspeed2 = -delta;
        }
        if (x - r <= wall.left){
                Xspeed2 = delta;
        }
        if (y - r <= wall.top){
            Yspeed2=delta;
        }

        if (y + r >= wall.bottom){
            pcResult += 1;
            Yspeed2=-delta;
        }
    }

}

void Test_Ball_Player(float x , float y , float r,moraba player ,float speed_x ,float speed_y){

	if (y + r + 1 >= player.top && x + r +1>= player.left && x - r +1<= player.right)
	{
		if (speed_y==Yspeed && speed_x == Xspeed)
            Yspeed=-delta;
        else if (speed_y==Yspeed2 && speed_x==Xspeed2)
             Yspeed2=-delta;
        playerResult++;
	}
	glutPostRedisplay();

}

void init(){
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glClearColor(1,1,1,0);
   glMatrixMode(GL_PROJECTION);
   gluOrtho2D(0 , 800 , 500 , 0 );
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void echo( char *string , int x, int y){

  int len, i;
  len = strlen(string);
  glRasterPos2i(x , y);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void kuh(){
   glBegin(GL_TRIANGLES);
    glColor3f(0.5,0.2,0);
    glVertex2f(0,200);
    glVertex2f(150,200);
    glColor4f(0.5,0.2,0,0.1);
    glVertex2f(75,50);
   glEnd();
}

void dayere(float x , float y , float r , int khat){
    float theta;
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i++){
        theta = i*3.1416/180;
        glVertex2f(x + r*cos(theta), y + r*sin(theta));
    }
    glEnd();
    theta =0;
    if (khat==1){
        glBegin(GL_LINES);
        for(int i=0; i<360; i++){
         theta = i*3.1416/180;
         if (i%45==0){
                glColor3f(0.9,0.9,0.9);
                glVertex2f(x , y);
                glColor3f(0,0,0);
                glVertex2f(x + r*cos(theta), y + r*sin(theta));
            }
        }
        glEnd();
    }
}

void dayere_khali(float x , float y , float r){
    float theta=0;
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<360; i++){
        theta = i*3.1416/180;
        glVertex2f(x + r*cos(theta), y + r*sin(theta));
    }
    glEnd();
}

void background(){
   glBegin(GL_QUADS);  // zamin o hava
   glColor3f(0,1,0);
   glVertex2f(0,500);
   glVertex2f(800,500);
   glColor3f(0,0.5,0);
   glVertex2f(800,200);
   glVertex2f(0 ,200);
   glEnd();
   glBegin(GL_QUADS);
   glColor3f(0.9,0.9,1);
   glVertex2f(0,0);
   glVertex2f(800,0);
   glColor3f(1,0.5,0);
   glVertex2f(800,200);
   glVertex2f(0,200);
   glEnd();
   glPushMatrix();   //kuh ha
   kuh();
   glPopMatrix();

   glPushMatrix();
   glTranslated(150,0,0);
   kuh();
   glPopMatrix();

   glPushMatrix();
   glTranslated(300,0,0);
   kuh();
   glPopMatrix();

   glPushMatrix();
   glTranslated(450,0,0);
   kuh();
   glPopMatrix();

   glPushMatrix();   //kuhe akhar
   glTranslated(600,0,0);
   kuh();
   glPopMatrix();

   moraba simplePlayer={600, 340 , 450 , 350};   //rocket
   glColor3f(0.7, 0 , 0);
   DrawRectangle(simplePlayer);

   glColor3f(0.9,0.9,0.9);
   dayere(400 , 120 , 40 , 1);
   glColor3f(0,0,0);
   dayere_khali(400 , 120 , 40);

}

void title1(){
    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
    glColor4f(1,1,1,0.4);
    glVertex2f(100 , 50);
    glVertex2f(100 , 450);
    glVertex2f(700 , 450);
    glVertex2f(700 , 50);
    glEnd();
    glFlush();
    glColor3f(1,0,0);
    if (lost==true)
       echo ("game over !",270 , 190);
    glColor3f(0,0,0);
    echo("Welcome to the ball and racket game ." , 270 , 240);
    echo ("push Enter to play ...", 270 , 280);
    glPopMatrix();
}

static int mouse_x = 0;
void MouseMotion(int x, int y){
	mouse_x = x;
}

void reset_game(){
    pcResult=0;
    playerResult=0;
    lost=false;
    circ_x=100;
    circ_y=110;
    circ2_x=500;
    circ2_y=110;
}

void game(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0.9,0,0.1);
            glVertex2f(0 , 500);
            glVertex2f(800 , 500);
            glColor3f(0.4,0,0);
            glVertex2f(800,400);
            glVertex2f(0,400);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0.9,0,0.1);
            glVertex2f(0 , 0);
            glVertex2f(800 , 0);
            glColor3f(0.4,0,0);
            glVertex2f(800,100);
            glVertex2f(0,100);
        glEnd();
    glPopMatrix();
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor4f(0,0.1,0,0.4);
            glVertex2f(0 , 100);
            glVertex2f(800,100);
            glVertex2f(800,400);
            glVertex2f(0,400);
        glEnd();
    glPopMatrix();
    //scores
    glColor3f(1,1,1);
    sprintf(string, "Computer : %d ", pcResult);
	echo(string, 10, 80);
	glColor3f(0,0,0);
	sprintf(string, "Player : %d ", playerResult);
	echo(string, 10, 120);

    wall.left = 0;
    wall.top = 100;
	wall.right = 800;
	wall.bottom = 400;
	glPushMatrix();
	glColor3f(1,0.5,0);
    dayere(circ_x,circ_y,circ_r,0);
    glPopMatrix();
    Test_Ball_Wall(circ_x,circ_y,circ_r,wall , Xspeed , Yspeed);

	glColor3f(0,0,1);
	DrawRectangle(player);
	player.left = mouse_x - 35;
	player.right = mouse_x + 35;

	Test_Ball_Player(circ_x,circ_y,circ_r,player , Xspeed , Yspeed);
   if (ball_num==2){
             glColor3f(1,0,1);
             dayere(circ2_x,circ2_y,circ_r,0);
             Test_Ball_Wall(circ2_x,circ2_y,circ_r,wall , Xspeed2 , Yspeed2);
             Test_Ball_Player(circ2_x,circ2_y,circ_r,player , Xspeed2 , Yspeed2);
    }
    if (pcResult > playerResult && playerResult+3 <= pcResult){
        run = false;
        lost=true;
    }
    glutPostRedisplay();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if (run == false){
       background();
       glPushMatrix();
       glLineWidth(2);
       glColor3f(1, 1 ,0 );
       dayere_khali(750,50,20);
       glPopMatrix();
       glPushMatrix();
       glColor3f(0.9 , 1 ,0.9 );
       dayere(750,50,20,0);
       glPopMatrix();
       title1();
   }else {
       game();
   }
glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	switch (key) {
	case 27:
		exit(0);
		break;
    case 13://space
    case 32:
        if(run == false){
             run = true;
             reset_game();
        }
        break;
    }
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 500, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void correction(){
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

void menu(int id){
    switch (id){
    case 1:
        exit(0);
    }
}

int main(int argc, char** argv){
	std::cout << "ball numbers 1 or 2: ";
	std::cin >> ball_num;
	std::cout << "well done .";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 500);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Project For Computer Graphics");
	init();
	glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(1, Timer, 1);
	if (ball_num==2)
        glutTimerFunc(1, Timer2, 1);
    glutIdleFunc(correction);
	glutPassiveMotionFunc(MouseMotion);
	glutCreateMenu(menu);
	glutAddMenuEntry("Exit ?", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}
