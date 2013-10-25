//include librarii de opengl, glut si glu
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

//includes
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>

//glut and glew
#include "glut.h"


//camera
#include "camera_top.h"
#include "camera_fps.h"
#include "camera_tps.h"

//cam
int cam=1;
float step=0;
Camera_top camera_top;
Camera_FPS camera_fps;
Camera_TPS camera_tps;

//castig
bool won;
char **message;
int mess_m,mess_n;
GLdouble angle =0;
//labirintul
char **labirint;
//dimensiunea hartii
int n,m;
//pozitia portalului
typedef struct punct{
float x,y,z;
};

punct portal;
Vector3D hero;
Vector3D hero_forward= Vector3D(0.0,0.0,-1.0);
Vector3D hero_right = Vector3D(1.0,0.0,0.0);
Vector3D hero_up = Vector3D(0.0,1.0,0.0);

//
void read_file()
{
FILE *fd= fopen("in.txt","r");
char buf[100];

fgets(buf,10,fd);

//printf("buf is %s \n",buf);
char*p;
p=strtok(buf," ");
n=atoi(p);
p=strtok(NULL," ");
m=atoi(p);

//printf("n=%d m=%d \n",n,m);

labirint = (char **) calloc (n,sizeof(char *));
	for(int i=0;i<n;i++)
	{
		fgets(buf,m+2,fd);
		//printf("buf is %s \n",buf);
		labirint[i]=(char *) calloc(m,sizeof(char)); 
		
		for(int j=0;j<m;j++)
		{
		labirint[i][j] = buf[j];
			if(buf[j]=='$')
			{hero.x=j;
			hero.z=i;
			hero.y=2;
			}

			if(buf[j]=='@')
			{portal.x=j;
			portal.z=i;
			portal.y=2;
			}

		}
	}

}

//Labirintul este desenat conform datelor citite din fisier
void draw_maze()
{
for(int i=0;i<n;i++)
{	for(int j=0;j<m;j++)
	{	if(labirint[i][j]=='*')
		{glPushMatrix();
		glColor3f(0.4,0.2,0.0);
		glTranslatef(j,0.5,i);
		glScalef(1,2,1);
		glutSolidCube(0.999);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(0.0,0.0,0.0);
		glTranslatef(j,0.5,i);
		glScalef(1,2,1);
		glutWireCube(1);
		
		glPopMatrix();
		}
		if(labirint[i][j]=='@')
		{glPushMatrix();
		glColor3f(0.0,1.0,0.0);
		glTranslatef(j,0.8,i);
		glRotatef(step,0,0,1);
		glutWireTorus(0.24,0.25,50,100);
		glPopMatrix();}
	}
}
}
//Este desenata suprafata pe care se misca eroul
void draw_ground()
{
	glBegin(GL_QUADS);

	glNormal3f(0.0,1.0,0.0);
	glVertex3f(-1,0,-1);
	glVertex3f(m,0,-1);
	glVertex3f(m,0,n);

	glVertex3f(-1,0,n);

	glEnd();


}

//Este citit mesajul ce se afiseaza la final
void read_message()
{
	FILE *fd= fopen("message.txt","r");
	char buf[200];

	fgets(buf,10,fd);

	
	//printf("buf is %s \n",buf);
	char*p;
	p=strtok(buf," ");
	mess_n=atoi(p);
	p=strtok(NULL," ");
	mess_m=atoi(p);

message = (char **) calloc (mess_n,sizeof(char *));
for(int i=0;i<mess_n;i++)
{
fgets(buf,mess_m+5,fd);
//printf("buf is %s \n",buf);
message[i]=(char *) calloc(mess_m,sizeof(char)); 
for(int j=0;j<mess_m;j++)
	{
	message[i][j] = buf[j];
	}
}
}
//Se afiseaza mesajul de castig
void draw_message()
{
	for(int i=0;i<mess_n;i++)
	{	for(int j=0;j<mess_m;j++)
	{	if(message[i][j]!=' ')
		{glPushMatrix();
		glColor3f(0.5,0.0,0.5);
		glTranslatef(j,0.5,i);
		glScalef(1,2,1);
		glutSolidCube(0.8);
		glPopMatrix();
		
	
	}}}
}

float aprox(float x)
{return floor(x+0.5);}

/* functia check_collision returneaza :
	1  - daca mutarea provoca coliziunea cu peretii
	2  - daca mutarea aduce eroul la portal
	0  - altfel

	Detectarea coliziunilor este destul de permisiva , 
	altfel ingreuneaza destul de mult navigarea colturilor
*/
int check_collision(int dir,Vector3D move)
{
	Vector3D position;

	position = hero + move.operator *(0.4 * dir);

	float x,z;

	x = position.x;
	z = position.z;
	
	int i= (int) aprox(z), j = (int)aprox(x);
	

	if(labirint[i][j]=='*') return 1;
	if(labirint[i][j]=='@') return 2;

 return 0;
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!won){
	step+=0.4;
	//setup view
	//camera_top.init(hero.x,20,hero.z);	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(cam==1){
	camera_top.render();
	}else{
		if (cam==2){
		camera_fps.render();}
		else
		{camera_tps.render();}
	}

	//ground &  maze
	glColor3f(0.5,0.5,0.5);
	draw_ground();
	draw_maze();



	//desenare erou
	glPushMatrix();
	glColor3f(0.0,0.0,1.0);

	glTranslatef(hero.x,1,hero.z);
	glutSolidSphere(0.2,20,15);
	

	

	glRotatef(angle,0,1,0);
	glRotatef(180,0,1,0);


	glutSolidCone(0.2,0.5,10,10);
	

	glPopMatrix();
	}
	else
	{
		camera_top.init(mess_m/2,100,mess_n/2);	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera_top.render();
		draw_message();}


	//swap buffers
	glutSwapBuffers();
}

void reshape(int width, int height){
	//set viewport
	glViewport(0,0,width,height);

	//set proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)width/(float)height,0.2,100);

	}

void idle();

void keyboard(unsigned char ch, int x, int y){
	switch(ch){
		case 27:	//esc
			exit(0);
			break;

		case 'w': {
			if(check_collision(1,hero_forward) !=1)
			{
			 if(check_collision(1,hero_forward)==2) {won=true; read_message();}
			camera_fps.translate_Forward(0.1); 
			hero = hero + hero_forward.operator *(0.1);
			camera_tps.translate_Forward(0.1,hero_forward);}			
				  }break;
		case 's': {
			if(check_collision(-1,hero_forward) !=1)
			{
				if(check_collision(-1,hero_forward) ==2) {won=true; read_message();}
			hero = hero - hero_forward.operator *(0.1);
			camera_fps.translate_Forward(-0.1); 
			camera_tps.translate_Forward(-0.1,hero_forward);}
				  }break;
		
		case 'a': {
			angle+=11.4592;
			camera_fps.rotateFPS_OY(-0.2);
			camera_tps.rotateTPS_OY(-0.2,1.5); 
			hero_forward = hero_forward.operator *(cos(-0.2)) + hero_right.operator *(sin(-0.2));
			hero_right = hero_forward.CrossProduct(hero_up);

				  }break;
		case 'd': {
			angle-=11.4592;
			camera_fps.rotateFPS_OY(0.2); 
			camera_tps.rotateTPS_OY(0.2,1.5); 
			hero_forward = hero_forward.operator *(cos(0.2)) + hero_right.operator *(sin(0.2));
			hero_right = hero_forward.CrossProduct(hero_up);

				  }break;

		case 'z': {
			if(check_collision(-1,hero_right) !=1)
			{
				if(check_collision(-1,hero_right) ==2) {won=true; read_message();}
			hero = hero - hero_right.operator *(0.1);
			camera_fps.translate_Right(-0.1); 
			camera_tps.translate_Right(-0.1,hero_right);}
				  }break;
		case 'c': {
			if(check_collision(1,hero_right) !=1)
			{
				if(check_collision(1,hero_right) ==2) {won=true; read_message();}
			hero = hero + hero_right.operator *(0.1);
			camera_fps.translate_Right(0.1); 
			camera_tps.translate_Right(0.1,hero_right);}
				  }break;
		

		case '1':{cam=1;}break;
		case '2':{cam=2;}break;
		case '3':{cam=3;}break;
		
		case 'i':{camera_tps.rotateTPS_OX(0.2,1.5);}break;
		case 'k':{camera_tps.rotateTPS_OX(-0.2,1.5);}break;
		case 'j':{camera_tps.rotateTPS_OZ(0.2,1.5);}break;
		case 'l':{camera_tps.rotateTPS_OZ(-0.2,1.5);}break;		
		default:
			break;
	}
}



//idle
void idle(){

	glutPostRedisplay();
}



int main(int argc, char *argv[]){
	
	read_file();

	//init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//init window
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Labirint");

	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);


	//z test on
	glEnable(GL_DEPTH_TEST);

	//set background
	glClearColor(0.2,0.2,0.2,1.0);

	//init camera
	camera_top.init(m/2,50,n/2);
	camera_fps.init(hero.x,1.2,hero.z);
	camera_tps.init(hero.x,1.8,hero.z+1.5);
	//loop
	glutMainLoop();

	return 0;
}