#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

GLint xa, ya, xb, yb;

void initGL (void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, 500.0, 0.0, 500.0);
	glMatrixMode (GL_MODELVIEW);
}

void showGraphic (void) {
	GLint dx = xb - xa, dy = yb - ya, steps, k;
	GLfloat xinc, yinc, p[2], x = xa, y = ya;
	
	p[0] = xa;
	p[1] = ya;
	
	if (abs (dx) > abs (dy))
		steps = abs (dx);
	else
		steps = abs (dy);

	xinc = dx / (GLfloat) steps;
	yinc = dy / (GLfloat) steps;

	glClear (GL_COLOR_BUFFER_BIT);
	glBegin (GL_POINTS);

	glVertex2fv (p);
	for (k = 0; k < steps; k++) {
		x += xinc;
		y += yinc;
		p[0] = round (x);
		p[1] = round (y);
		glVertex2fv (p);
	}

	glEnd ();
	glFlush ();
}

int main(int argc, char **argv) {
	printf ("Enter the end-points of the line (left end-point first): ");
	scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("OpenGL");
	glutDisplayFunc (showGraphic);
	initGL ();
	glutMainLoop ();
	return 0;
}
