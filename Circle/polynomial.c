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

	GLfloat xp = x + rx, ytemp;

	while (xp >= x - rx) {
		xp--;
		ytemp = ry * sqrt (1 - pow((xp - x) / rx, 2));

		PLOT (round(xp), round(y + ytemp));
		PLOT (round(xp), round(y - ytemp));
	}

	glEnd ();
	glFlush ();
}


