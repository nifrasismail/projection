#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <cmath> 

int WinWidth = 500, WinHeight = 500;

typedef struct{float x;float y;}Point2D;
typedef struct{float x;float y;float z;}Point3D;

Point3D COP = {0,0,-200};	// Centre Of Projection is at (0,0,-200)

Point3D A,B,C,D,E,F,G,H;	// Vertices of the cube

Point2D Projected_A,Projected_B,Projected_C,Projected_D,Projected_E,Projected_F,Projected_G,Projected_H;

void InitCube(){
	A.x = 0; A.y = 0; A.z = 0;			// A(0,0,0)
	B.x = 200; B.y = 0; B.z = 0;		// B(200,0,0)
	C.x = 200; C.y = 200; C.z = 0;		// C(200,200,0)
	D.x = 0; D.y = 200; D.z = 0;		// D(0,200,0)

	E.x = 0; E.y = 200; E.z = 200;		// E(0,200,200)
	F.x = 0; F.y = 0; F.z = 200;		// F(0,0,200)
	G.x = 200; G.y = 0; G.z = 200;		// G(200,0,200)
	H.x = 200; H.y = 200; H.z = 200;	// H(200,200,200)
}

void DrawCube(Point2D A, Point2D B, Point2D C, Point2D D, Point2D E, Point2D F, Point2D G, Point2D H){
	glPointSize(1.0);

	glBegin(GL_LINE_LOOP);	
	//DRAWING FRONT FACE
		glVertex2i(A.x, A.y); glVertex2i(B.x, B.y);	glVertex2i(C.x, C.y); glVertex2i(D.x, D.y);
	glEnd();

	glBegin(GL_LINE_LOOP);
	//DRAWING BACK FACE
		glVertex2i(E.x, E.y); glVertex2i(F.x, F.y);	glVertex2i(G.x, G.y); glVertex2i(H.x, H.y);
	glEnd();
	
	glBegin(GL_LINES);
	//DRAWING OTHER LINES
		glVertex2i(A.x, A.y); glVertex2i(F.x, F.y);

		glVertex2i(B.x, B.y); glVertex2i(G.x, G.y);

		glVertex2i(C.x, C.y); glVertex2i(H.x, H.y);

		glVertex2i(D.x, D.y); glVertex2i(E.x, E.y);
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

void Draw3DTranslation(){
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	Point3D COP ={100,100,-200};
	A = translate3D(A,-100,-100,200);
	B = translate3D(B,-100,-100,200);
	C = translate3D(C,-100,-100,200);
	D = translate3D(D,-100,-100,200);
	E = translate3D(E,-100,-100,200);
	F = translate3D(F,-100,-100,200);
	G = translate3D(G,-100,-100,200);
	H = translate3D(H,-100,-100,200);

	Projected_A = Project_Perspective(A,COP);
	Projected_B = Project_Perspective(B,COP);
	Projected_C = Project_Perspective(C,COP);
	Projected_D = Project_Perspective(D,COP);
	Projected_E = Project_Perspective(E,COP);
	Projected_F = Project_Perspective(F,COP);
	Projected_G = Project_Perspective(G,COP);
	Projected_H = Project_Perspective(H,COP);

	//2D Translation to Move Projected to Center Screen
	Projected_A = translate2D(Projected_A,WinWidth/2,WinHeight/2); 
	Projected_B = translate2D(Projected_B,WinWidth/2,WinHeight/2); 
	Projected_C = translate2D(Projected_C,WinWidth/2,WinHeight/2); 
	Projected_D = translate2D(Projected_D,WinWidth/2,WinHeight/2); 
	Projected_E = translate2D(Projected_E,WinWidth/2,WinHeight/2); 
	Projected_F = translate2D(Projected_F,WinWidth/2,WinHeight/2); 
	Projected_G = translate2D(Projected_G,WinWidth/2,WinHeight/2); 
	Projected_H = translate2D(Projected_H,WinWidth/2,WinHeight/2); 

	DrawCube(Projected_A,Projected_B,Projected_C,Projected_D,Projected_E,Projected_F,Projected_G,Projected_H);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(EXIT_SUCCESS);
}

void myMouse(int button, int state, int x, int y) {
	if(state == GLUT_DOWN) 
	{
		if(button == GLUT_LEFT_BUTTON) 
		{
			 
		}
		else if (button == GLUT_RIGHT_BUTTON) 
		{
			 Draw3DTranslation();
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

	//TRANSLATE TO MID POINT OF THE SCREEN
	Projected_A = translate2D(Projected_A,WinWidth/2,WinHeight/2); 
	Projected_B = translate2D(Projected_B,WinWidth/2,WinHeight/2); 
	Projected_C = translate2D(Projected_C,WinWidth/2,WinHeight/2); 
	Projected_D = translate2D(Projected_D,WinWidth/2,WinHeight/2); 
	Projected_E = translate2D(Projected_E,WinWidth/2,WinHeight/2); 
	Projected_F = translate2D(Projected_F,WinWidth/2,WinHeight/2); 
	Projected_G = translate2D(Projected_G,WinWidth/2,WinHeight/2); 
	Projected_H = translate2D(Projected_H,WinWidth/2,WinHeight/2); 

	DrawCube(
		// Calculate the following values
		Projected_A,
		Projected_B,
		Projected_C,
		Projected_D,
		Projected_E,
		Projected_F,
		Projected_G,
		Projected_H
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

	InitCube();

	glutKeyboardFunc(keyboard); 
	glutMouseFunc( myMouse );
	glutDisplayFunc( myDisplay );
	glutMainLoop();

	return( 0 );
}
