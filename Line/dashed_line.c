#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>

GLint xbeg, ybeg, xend, yend, nlen, dlen;

void initGL (void) {
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glColor3f (0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0, 500.0, 0.0, 500.0);
	glMatrixMode (GL_MODELVIEW);
}

void bresh (int xa, ya, xb, yb) {
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
}


void showGraphic (void) {
	glClear (GL_COLOR_BUFFER_BIT);
	glBegin (GL_POINTS);
	GLdouble x1, y1, x2, y2,
	        theta = atan2 (yend - ybeg, xend - xbeg),
	        s = sin (theta),
	        c = cos (theta);
	x1 = xbeg;
	y1 = ybeg;

	while (x1 < xend && y1 < yend) {
		x2 = x1 + nlen * c;
		y2 = y1 + nlen * s;
		bresh (x1, y1, x2, y2);
		x1 = x2 + dlen * c;
        y1 = y2 + dlen * s; 		
	}	

	glEnd ();
	glFlush ();
}

int main(int argc, char **argv) {
	GLfloat slope;
	do {
		printf ("Enter the end-points of the line (0 < slope < 1): ");
		scanf("%d %d %d %d", &xbeg, &ybeg, &xend, &yend);

		slope = (yend - ybeg) / (xend - xbeg);
	} while (slope < 0 || slope > 1);
	printf("Enter lengths of normal line and dash space: ");
	scanf("%d %d", &nlen, &dlen);
	
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
