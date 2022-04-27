// Template untuk mainan objek 3D
// Kamera bisa maju mundur kiri kanan
// Sudah dilengkapi pencahayaan

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

float rotangle=0.0;
float rotangle1=0.0;
float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int bitmapHeight=12;
const double PI = 3.141592653589793;
int i,j,radius,jumlah_titik,x_tengah,y_tengah;
GLUquadricObj *Objek = gluNewQuadric();
void Reshape(int w1, int h1)
{
	// Fungsi reshape
	if(h1 == 0) h1 = 1;
	w = w1;
	h = h1;
	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
	x, y, z,
	x + lx,y + ly,z + lz,
	0.0f,1.0f,0.0f);
}

void orientMe(float ang)
{
	// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
	x + lx,y + ly,z + lz,
	0.0f,1.0f,0.0f);
}

void moveMeFlat(int i)
{
	// Fungsi ini untuk maju mundur kamera
	x = x + i*(lx)*0.1;
	z = z + i*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
	x + lx,y + ly,z + lz,
	0.0f,1.0f,0.0f);
}

void Grid() {
	// Fungsi untuk membuat grid di "lantai"
	double i;
	const float Z_MIN = -50, Z_MAX = 50;
	const float X_MIN = -50, X_MAX = 50;
	const float gap = 1.5;
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_LINES);
	for(i=Z_MIN;i<Z_MAX;i+=gap)
	{
		glVertex3f(i, 0, Z_MIN);
		glVertex3f(i, 0, Z_MAX);
	}
	for(i=X_MIN;i<X_MAX;i+=gap)
	{
		glVertex3f(X_MIN, 0, i);
		glVertex3f(X_MAX, 0, i);
	}
	glEnd();
}

void Roda(){
    glColor3f(.0, 0, 0);
    glutSolidCone(.55, 0, 1000, 5);
    gluCylinder(Objek, .55, .55, .5, 32, 32);
    glPushMatrix();
        glTranslatef(0, 0, .5);
        glutSolidCone(.55, 0, 1000, 5);
    glPopMatrix();
}

void cylinder(float alas,float atas,float tinggi){
	float i;
	glPushMatrix();
		glTranslatef(1.0,0.0,-alas/8);
		glutSolidCone(alas,0,32,4);
		for(i=0;i<=tinggi;i+=alas/24){
		glTranslatef(0.0,0.0,alas/24);
		glutSolidTorus(alas/4,alas-((i*(alas-atas))/tinggi),16,16);
		}
		glTranslatef(0.0,0.0,alas/4);
		glutSolidCone(atas,0,20,1);
		glColor3f(1.,0.,0.);
	glPopMatrix();
}

void TrukGandeng()
{
	//KOKPIT
	glPushMatrix();
		//BOX DEPAN
		glPushMatrix();
			glTranslatef(0.23,2,0);
			glColor3f(0, 0, 1);
			glScalef(3.5, 2, 4.5);
			glutSolidCube(1);
		glPopMatrix();
		
		//Exhaust
		glPushMatrix();
			glTranslatef(-1.2,7,2.3);
			glColor3f(0.3, 0.3, 0.3);
			glRotated(90, 1, 0, 0);
			glScalef(2, 2, 7);
			gluCylinder(Objek, .06, .06, .5, 32, 32);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-1.2,4,2.1);
			glColor3f(0.3, 0.3, 0.3);
			glRotated(90, 1, 0, 0);
			glScalef(4, 4, 9);
			gluCylinder(Objek, .10, .10, .2, 32, 32);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-1.2,7,-2.3);
			glColor3f(0.3, 0.3, 0.3);
			glRotated(90, 1, 0, 0);
			glScalef(2, 2, 7);
			gluCylinder(Objek, .06, .06, .5, 32, 32);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-1.2,4,-2.1);
			glColor3f(0.3, 0.3, 0.3);
			glRotated(90, 1, 0, 0);
			glScalef(4, 4, 9);
			gluCylinder(Objek, .10, .10, .2, 32, 32);
		glPopMatrix();
		
		//ENGINE BAY
		glPushMatrix();
			glTranslatef(2.8,2,0);
			glColor3f(0, 0, 1);
			glScalef(5, 2, 3);
			glutSolidCube(1);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(5.4,2.3,0);
			glColor3f(0, 0, 0);
			glScalef(0.2, 1.5, 3);
			glutSolidCube(1);
		glPopMatrix();
		
		//Defuser
		glPushMatrix();
			glTranslatef(3,1.3,0);
			glColor3f(0.3, 0.3, 0.3);
			glScalef(5, 0.5, 4.4);
			glutSolidCube(1);
		glPopMatrix();
		
		//KACA
		glPushMatrix();
			glTranslatef(1.14,3.9,0);
			glColor3f(0, 0, 1);
			glRotated(38, 0, 0, 1);
			glScalef(0.2, 2.5, 4.5);
			glutSolidCube(1);
		glPopMatrix();
		
		//KACA
		glPushMatrix();
			glTranslatef(1,4.2,0);
			glColor3f(0.1, 0.1, 0.1);
			glRotated(38, 0, 0, 1);
			glScalef(0.1, 1.5, 4);
			glutSolidCube(1);
		glPopMatrix();
		
		//BOX ATAS
		glPushMatrix();
			glTranslatef(-0.52,3.93,0);
			glColor3f(0, 0, 1);
			glScalef(2, 2, 4.5);
			glutSolidCube(1);
		glPopMatrix();
		
	//Muatan
		//PLATE MUATAN	1
		glPushMatrix();
			glTranslatef(-6.5,1.5,0);
			glColor3f(0.5, 0.35, 0.05);
			glScalef(10, 1, 4.4);
			glutSolidCube(1);
		glPopMatrix();
		
		//MUATAN 1
		glPushMatrix();
			glTranslatef(-6.5,4,0);
			glColor3f(0.3, 0.3, 0.3);
			glScalef(8.5, 4, 4);
			glutSolidCube(1);
		glPopMatrix();
		
		//PENYAMBUNG
		glPushMatrix();
			glTranslatef(-12,1.7,0);
			glColor3f(0, 0, 0);
			glScalef(1, 0.2, 0.2);
			glutSolidCube(1);
		glPopMatrix();
		
		//PLATE MUATAN	2
		glPushMatrix();
			glTranslatef(-17.5,1.5,0);
			glColor3f(0.5, 0.35, 0.05);
			glScalef(10, 1, 4.4);
			glutSolidCube(1);
		glPopMatrix();
		
		//MUATAN 2
		glPushMatrix();
			glTranslatef(-17.5,4,0);
			glColor3f(0.3, 0.3, 0.3);
			glScalef(8.5, 4, 4);
			glutSolidCube(1);
		glPopMatrix();
		
	//RODA
		//KANAN
			//RODA KANAN 1
			glPushMatrix();
				glTranslatef(4,1,2);
				Roda();
			glPopMatrix();
	
			//RODA KANAN 2
			glPushMatrix();
				glTranslatef(-10,1,2);
				Roda();
			glPopMatrix();
			
			//RODA KANAN 3
			glPushMatrix();
				glTranslatef(-8.7,1,2);
				Roda();
			glPopMatrix();
			
			//RODA KANAN 4
			glPushMatrix();
				glTranslatef(-3,1,2);
				Roda();
			glPopMatrix();
			
			//RODA KANAN 5
			glPushMatrix();
				glTranslatef(-14,1,2);
				Roda();
			glPopMatrix();
			
			//RODA KANAN 6
			glPushMatrix();
				glTranslatef(-21,1,2);
				Roda();
			glPopMatrix();
	
	//RODA
		//KIRI
			//RODA KIRI 1
			glPushMatrix();
				glTranslatef(4,1,-2.45);
				Roda();
			glPopMatrix();
	
			//RODA KIRI 2
			glPushMatrix();
				glTranslatef(-10,1,-2.45);
				Roda();
			glPopMatrix();
					
			//RODA KIRI 3
			glPushMatrix();
				glTranslatef(-8.7,1,-2.45);
				Roda();
			glPopMatrix();
			
			//RODA KIRI 4
			glPushMatrix();
				glTranslatef(-3,1,-2.45);
				Roda();
			glPopMatrix();
			
			//RODA KIRI 4
			glPushMatrix();
				glTranslatef(-14,1,-2.45);
				Roda();
			glPopMatrix();
			
			//RODA KIRI 4
			glPushMatrix();
				glTranslatef(-21,1,-2.45);
				Roda();
			glPopMatrix();
	glPopMatrix();
}

void display() {
	// Kalau move dan angle tidak nol, gerakkan kamera...
	if (deltaMove)
	moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Gambar grid
	Grid();
	
	// Gambar objek di sini...
	TrukGandeng();
	glutSwapBuffers();
	glFlush();
}

void pressKey(int key, int x, int y) {
	// Fungsi ini akan dijalankan saat tombol keyboard ditekan dan belum dilepas
	// Selama tombol ditekan, variabel angle dan move diubah => kamera bergerak
	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
		case GLUT_KEY_UP : deltaMove = 1;break;
		case GLUT_KEY_DOWN : deltaMove = -1;break;
	}
}

void releaseKey(int key, int x, int y) {
	// Fungsi ini akan dijalankan saat tekanan tombol keyboard dilepas
	// Saat tombol dilepas, variabel angle dan move diset nol => kamera berhenti
	switch (key) {
		case GLUT_KEY_LEFT :
		if (deltaAngle < 0.0f)
		deltaAngle = 0.0f;
		break;
		case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
		deltaAngle = 0.0f;
		break;
		case GLUT_KEY_UP : if (deltaMove > 0)
		deltaMove = 0;
		break;
		case GLUT_KEY_DOWN : if (deltaMove < 0)
		deltaMove = 0;
		break;
	}
}

// Variable untuk pencahayaan
const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting(){
	// Fungsi mengaktifkan pencahayaan
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void)
{
	glEnable (GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(900,700);
	glutCreateWindow("Optimum Pride");
	glutIgnoreKeyRepeat(1); // Mengabaikan key repeat (saat tombol keyboard dipencet terus)
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutDisplayFunc(display);
	glutIdleFunc(display); // Fungsi display-nya dipanggil terus-menerus
	glutReshapeFunc(Reshape);
//	glClearColor(0.5294, 0.8078, 0.9215, 1);
	glClearColor(1, 1, 1, 1);
	lighting();
	init();
	glutMainLoop();
	return(0);
}
