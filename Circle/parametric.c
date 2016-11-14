#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

#define PLOT(x,y) glVertex2i(x,y)

int x, y, rx, ry;

void initGL (void);
void showGraphic(void);

int main(int argc, char **argv) {
	printf ("Enter the center and radius: ");
	scanf("%d %d %d %d", &x, &y, &rx, &ry);
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

void initGL (void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, 500.0, 0.0, 500.0);
	glMatrixMode (GL_MODELVIEW);
}

void showGraphic (void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glBegin (GL_POINTS);

	void plotEllipse (int, int, int, int);

	GLfloat step, theta, xp, yp;
	
	step = 2;
	step /= (rx + ry);
	theta = 0;
	
	while (theta < M_PI / 2) {
		xp = rx * cos (theta);
		yp = ry * sin (theta);

		plotEllipse(x, y, round(xp), round(yp));

		theta += step;
	}

	glEnd ();
	glFlush ();
}

void plotEllipse (int xc, int yc, int x, int y) {
	PLOT (xc + x, yc + y);
	PLOT (xc - x, yc + y);
	PLOT (xc - x, yc - y);
	PLOT (xc + x, yc - y);
}
