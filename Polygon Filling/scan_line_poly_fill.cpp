#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct {
    int first, second;
} O;

class Point {
  public:
    int first, second;

    Point (int x = 0, int y = 0) : first (x), second (y) {}

    bool operator< (Point b) {
        double ta = atan2 (second - O.second, first - O.first),
               tb = atan2 (b.second - O.second, b.first - O.first);

        if (ta < tb)
            return true;
        else
            return false;
    }
};

std::vector< Point > points;

void sort (std::vector< Point > points) {
    O.first = O.second = 0;

    for (auto a : points) {
        O.first += a.first;
        O.second += a.second;
    }

    O.first /= points.size ();
    O.second /= points.size ();

    Point temp;

    for (size_t i = 0; i < points.size (); i++) {
        for (size_t j = i; j < points.size (); j++) {
            if (!(points[i] < points[j])) {
                temp = points[j];
                points[j] = points[i];
                points[i] = temp;
            }
        }
    }
}

void initOpenGL(void) {
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glColor3f (0.0, 0.0, 0.0);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (-300.0, 300.0, -300.0, 300.0);
    glMatrixMode (GL_MODELVIEW);
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT);
    glBegin (GL_LINE_LOOP);
    for (auto a : points) {
        glVertex2i (a.first, a.second);
    }

    Point rect[4];

    rect[0].second = points[0].second;
    rect[0].first = points[0].first;
    rect[2].first = points[0].first;
    rect[2].second = points[0].second;
    for (auto a : points) {
        if (a.second < rect[0].second) {
            rect[0].second = a.second;
        }
        if (a.first < rect[0].first) {
            rect[0].first = a.first;
        }
        if (a.second > rect[2].second) {
            rect[2].second = a.second;
        }
        if (a.first > rect[2].first) {
            rect[2].first = a.first;
        }
    }
    rect[1].first = rect[2].first;
    rect[1].second = rect[0].second;
    rect[3].first = rect[0].first;
    rect[3].second = rect[2].second;

    glEnd ();
    glFlush ();
}

int main (int argc, char **argv) {
    int n, x, y;
    std::cout << "Enter the no. of points: ";
    std::cin >> n;
    std::cout << "Enter polygon points: ";
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        points.push_back (Point (x, y));
    }

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("OpenGL");
    glutDisplayFunc (display);
    initOpenGL ();
    glutMainLoop ();
    return 0;
}
