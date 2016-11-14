#include <GLUT/glut.h>
#include <iostream>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

const char *title = "Liang-Barsky";

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

void liang_barsky(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1,
                      GLfloat& x2, GLfloat& y2, GLfloat& x3, GLfloat& y3) {
    GLfloat t = (xmin - x0) / (x1 - x0), t1 = 1, t2 = 1;

    if (x1 > x0)
        t1 = max(t1, t);
    else
        t2 = min(t2, t);

    t = (ymax - y0) / (y1 - y0);
    if (y0 > y1)
        t1 = max(t1, t);
    else
        t2 = min(t2, t);

    t = (xmax - x0) / (x1 - x0);
    if (x0 > x1)
        t1 = max(t1, t);
    else
        t2 = min(t2, t);

    t = (ymin - y0) / (y1 - y0);
    if (y1 > y0)
        t1 = max(t1, t);
    else
        t2 = min(t2, t);

    if (t1 < t2) {
        GLfloat x = x1;
        GLfloat y = y1;
        x1 = x0 + t2 * (x1 - x0);
        y1 = y0 + t2 * (y1 - y0);
        x0 += t1 * (x - x0);
        y0 += t1 * (y - y0);
        x2 = x0;
        y2 = y0;
        x3 = x1;
        y3 = y1;
    }
}

void display() {
    GLfloat x0 = -8, y0 = -5, x1 = 3, y1 = 7, x2, y2, x3, y3;
    liang_barsky(x0, y0, x1, y1, x2, y2, x3, y3);

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

