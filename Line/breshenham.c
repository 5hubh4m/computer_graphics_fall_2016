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
	GLint dx = abs (xb - xa), 
              dy = abs (yb - ya),
	      param= 2 * dy - dx,
	      x, y, xEnd;
	GLfloat p[2];

	if (xa > xb) {
		x = xb;
		y = yb;
		xEnd = xa;
	} else {
		x = xa;
		y = ya;
		xEnd = xb;
	}

	glClear (GL_COLOR_BUFFER_BIT);
	glBegin (GL_POINTS);

	p[0] = x;
	p[1] = y;
	glVertex2fv (p);
	while (x < xEnd) {
		x++;
		if (param < 0) {
			param += 2 * dy;
		} else {
			y++;
			param += 2 * (dy - dx);
		}

		p[0] = x;
		p[1] = y;
		glVertex2fv (p);
	}

	glEnd ();
	glFlush ();
}

int main(int argc, char **argv) {
	GLfloat slope;
	do {
		printf ("Enter the end-points of the line (0 < slope < 1): ");
		scanf("%d %d %d %d", &xa, &ya, &xb, &yb);

		slope = (yb - ya) / (xb - xa);
	} while (slope < 0 || slope > 1);
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
