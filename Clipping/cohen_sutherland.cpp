#include <GLUT/glut.h>
#include <iostream>

const char *title = "Cohen-Sutherland";

const GLfloat xmax = 5, ymax = 5, xmin = -5, ymin = -5;

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to white and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
}

typedef int BinaryCode;

const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

BinaryCode ComputeOutCode(GLfloat x, GLfloat y) {
    BinaryCode code;

    code = INSIDE;          // initialised as being inside of [[clip window]]

    if (x < xmin)           // to the left of clip window
    	code |= LEFT;
    else if (x > xmax)      // to the right of clip window
	code |= RIGHT;
    if (y < ymin)           // below the clip window
	code |= BOTTOM;
    else if (y > ymax)      // above the clip window
	code |= TOP;

    return code;
}

void cohen_sutherland(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1,
                      GLfloat& x2, GLfloat& y2, GLfloat& x3, GLfloat& y3) {
    BinaryCode outcode0 = ComputeOutCode(x0, y0);
    BinaryCode outcode1 = ComputeOutCode(x1, y1);
    bool accept = false;

    while (true) {
	if (!(outcode0 | outcode1)) {
		accept = true;
		break;
	} else if (outcode0 & outcode1) {
		break;
	} else {
	    GLfloat x, y;

	    BinaryCode outcodeOut = outcode0 ? outcode0 : outcode1;

	    if (outcodeOut & TOP) {
		x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
		y = ymax;
	    } else if (outcodeOut & BOTTOM) {
		x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
		y = ymin;
	    } else if (outcodeOut & RIGHT) {
		y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
		x = xmax;
	    } else if (outcodeOut & LEFT) {
		y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
		x = xmin;
	    }

    	    if (outcodeOut == outcode0) {
		x0 = x;
		y0 = y;
		outcode0 = ComputeOutCode(x0, y0);
	    } else {
		x1 = x;
		y1 = y;
		outcode1 = ComputeOutCode(x1, y1);
	    }
	}
    }
    if (accept) {
        std::cout << "Found\n";
        x2 = x0;
        y2 = y0;
        x3 = x1;
        y3 = y1;
    }
}

void display() {
    GLfloat x0 = -7, y0 = 6, x1 = 8, y1 = 3, x2, y2, x3, y3;
    cohen_sutherland(x0, y0, x1, y1, x2, y2, x3, y3);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin);
        glVertex2i(xmin, ymax);
        glVertex2i(xmax, ymax);
        glVertex2i(xmax, ymin);
    glEnd();  // End of drawing color-cube

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x2, y2);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x3, y3);
    glEnd();

    glFlush();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
   glutInitWindowSize(500, 500);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}

