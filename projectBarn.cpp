#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath> 

int WinWidth = 500, WinHeight = 500;

typedef struct{float x;float y;}Point2D;
typedef struct{float x;float y;float z;}Point3D;

Point3D COP = {0,0,-200};	// Centre Of Projection is at (0,0,-200)

Point3D A,B,C,D,E,F,G,H,I,J;	// Vertices of the cube

Point2D Projected_A,Projected_B,Projected_C,Projected_D,Projected_E,Projected_F,Projected_G,Projected_H,Projected_I,Projected_J;

void constructBarn(){
	A.x = 200; A.y = 100; A.z = 200;
	B.x = 200; B.y = 00; B.z = 200;
	C.x = 400; C.y = 00; C.z = 200;
	D.x = 400; D.y = 100; D.z = 200;
	E.x = 300; E.y = 200; E.z = 200;

	F.x = 200; F.y = 100; F.z = 400;
	G.x = 200; G.y = 00; G.z= 400;
	H.x = 400; H.y = 00; H.z = 400;
	I.x = 400; I.y = 100; I.z = 400;
	J.x = 300; J.y = 200; J.z = 400;
}

void DrawBarn(Point2D A, Point2D B, Point2D C, Point2D D, Point2D E, Point2D F, Point2D G, Point2D H, Point2D I, Point2D J){
	glPointSize(1.0);

	glBegin(GL_LINE_LOOP);	
	//DRAWING FRONT FACE
	glVertex2i(A.x, A.y);
	glVertex2i(B.x, B.y);
	glVertex2i(C.x, C.y);
	glVertex2i(D.x, D.y);
	glVertex2i(E.x, E.y);

	glEnd();

	glBegin(GL_LINE_LOOP);
	//DRAWING BACK FACE
	glVertex2i(F.x, F.y);
	glVertex2i(G.x, G.y);
	glVertex2i(H.x, H.y);
	glVertex2i(I.x, I.y);
	glVertex2i(J.x, J.y);

	glEnd();
	
	glBegin(GL_LINES);

	//DRAWING OTHER LINES
	glVertex2i(A.x, A.y);
	glVertex2i(F.x, F.y);

	glVertex2i(B.x, B.y);
	glVertex2i(G.x, G.y);

	glVertex2i(C.x, C.y);
	glVertex2i(H.x, H.y);

	glVertex2i(D.x, D.y);
	glVertex2i(I.x, I.y);

	glVertex2i(E.x, E.y);
	glVertex2i(J.x, J.y);

	glEnd();

	glFlush();
}


Point2D Project_Perspective(Point3D p, Point3D CoP){
	Point2D p2;
	float d = abs(CoP.z);	// The distance between the COP and orign
	
	p2.x = d*(p.x)/(p.z+d);
	p2.y = d*(p.y)/(p.z+d);

	//.....wite necessary equations here for perspective transformation
	
	return p2;
}


Point2D translate2D(Point2D p, float tx, float ty){
    Point2D tp2;
	tp2.x = p.x + tx;
	tp2.y = p.y + ty;
	
	return tp2;
} 

Point3D translate3D(Point3D p, float tx, float ty, float tz){
    Point3D tp3;
	//.....wite the equations for 3D translation
	tp3.x = p.x + tx;
	tp3.y = p.y + ty;
	tp3.z = p.z + tz;
	return tp3;
} 

Point3D scaling3D(Point3D p, float Sx, float Sy, float Sz){
	Point3D tp4;

	tp4.x = p.x*Sx;
	tp4.y = p.y*Sy;
	tp4.z = p.z*Sz;
	return tp4;
}

void resize(float Sx,float Sy,float Sz){
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	A = scaling3D(A,Sx,Sy,Sz);
	B = scaling3D(B,Sx,Sy,Sz);
	C = scaling3D(C,Sx,Sy,Sz);
	D = scaling3D(D,Sx,Sy,Sz);
	E = scaling3D(E,Sx,Sy,Sz);
	F = scaling3D(F,Sx,Sy,Sz);
	G = scaling3D(G,Sx,Sy,Sz);
	H = scaling3D(H,Sx,Sy,Sz);
	I = scaling3D(I,Sx,Sy,Sz);
	J = scaling3D(J,Sx,Sy,Sz);
	
	//Do projection
	Projected_A = Project_Perspective(A,COP); 
	Projected_B = Project_Perspective(B,COP); 
	Projected_C = Project_Perspective(C,COP); 
	Projected_D = Project_Perspective(D,COP); 
	Projected_E = Project_Perspective(E,COP); 
	Projected_F = Project_Perspective(F,COP); 
	Projected_G = Project_Perspective(G,COP); 
	Projected_H = Project_Perspective(H,COP);
	Projected_I = Project_Perspective(I,COP); 
	Projected_J = Project_Perspective(J,COP);

	DrawBarn(
		// Calculate the following values
		Projected_A,
		Projected_B,
		Projected_C,
		Projected_D,
		Projected_E,
		Projected_F,
		Projected_G,
		Projected_H,
		Projected_I,
		Projected_J
	);

}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(EXIT_SUCCESS);

	if(key == '+')
		resize(2,2,2);

	if(key == '-')
		resize(0.5,0.5,0.5);

}

void myMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) 
	{
		if(button == GLUT_LEFT_BUTTON) 
		{
			 
		}
		else if (button == GLUT_RIGHT_BUTTON) 
		{
			 
		}
	}
}

void myDisplay()
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	Projected_A = Project_Perspective(A,COP); 
	Projected_B = Project_Perspective(B,COP); 
	Projected_C = Project_Perspective(C,COP); 
	Projected_D = Project_Perspective(D,COP); 
	Projected_E = Project_Perspective(E,COP); 
	Projected_F = Project_Perspective(F,COP); 
	Projected_G = Project_Perspective(G,COP); 
	Projected_H = Project_Perspective(H,COP);
	Projected_I = Project_Perspective(I,COP); 
	Projected_J = Project_Perspective(J,COP);

	//TRANSLATE TO MID POINT OF THE SCREEN
	Projected_A = translate2D(Projected_A,WinWidth/2,WinHeight/2); 
	Projected_B = translate2D(Projected_B,WinWidth/2,WinHeight/2); 
	Projected_C = translate2D(Projected_C,WinWidth/2,WinHeight/2); 
	Projected_D = translate2D(Projected_D,WinWidth/2,WinHeight/2); 
	Projected_E = translate2D(Projected_E,WinWidth/2,WinHeight/2); 
	Projected_F = translate2D(Projected_F,WinWidth/2,WinHeight/2); 
	Projected_G = translate2D(Projected_G,WinWidth/2,WinHeight/2); 
	Projected_H = translate2D(Projected_H,WinWidth/2,WinHeight/2); 
	Projected_I = translate2D(Projected_I,WinWidth/2,WinHeight/2); 
	Projected_J = translate2D(Projected_J,WinWidth/2,WinHeight/2); 

	DrawBarn(
		// Calculate the following values
		Projected_A,
		Projected_B,
		Projected_C,
		Projected_D,
		Projected_E,
		Projected_F,
		Projected_G,
		Projected_H,
		Projected_I,
		Projected_J
	);

	
}


int main( int argc, char ** argv ) {
	glutInit( &argc, argv );
	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( WinWidth, WinHeight );
	glutCreateWindow( "Projection of a Cube" );

	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity();
	gluOrtho2D( 0, WinWidth, 0, WinHeight );
	glViewport(0, 0, WinWidth, WinHeight);

	constructBarn();

	glutKeyboardFunc(keyboard); 
	glutMouseFunc( myMouse );
	glutDisplayFunc( myDisplay );
	glutMainLoop();

	return( 0 );
}
