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
	GLint xp = 0, 
	      yp = ry,
	      rx2 = rx * rx,
	      ry2 = ry * ry,
	      px = 0,
	      py = 2 * rx2 * yp,
	      p;

	plotEllipse (x, y, xp, yp);

	p = round(ry2 - (rx2 * ry) + (0.25 * rx2));
	while (px < py) {
		xp++;
		px += 2 * ry2;
		if (p < 0)
			p += ry2 + px;
		else {
			yp--;
			py -= 2 * rx2;
			p += ry2 + px - py;
		}
		plotEllipse(x, y, xp, yp);
	}

	p = round(ry2 * (xp + 0.5) * (xp + 0.5) + rx2 * (yp - 1) * (yp - 1) - rx2 * ry2);
	while (yp > 0) {
		yp--;
		py -= 2 * rx2;
		if (p > 0)
			p+= rx2 - py;
		else {
			xp++;
			px += 2 * ry2;
			p += rx2 - py + px;
		}
		plotEllipse(x, y, xp, yp);
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
