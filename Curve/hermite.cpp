#include <GLUT/glut.h>
#include <iostream>
#include <vector>
#include <list>
#include <cmath>

#define max2(a, b) (a > b ? a : b)
#define min2(a, b) (a < b ? a : b)
#define min3(a, b, c) min2(a, min2(b, c))
#define max3(a, b, c) max2(a, max2(b, c))

template<typename T>
struct Vec3 {
    T x, y, z;

    Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
    Vec3(T x) : x(x), y(x), z(x) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    Vec3& normalize() {
        T nor2 = dot(*this);

        if (nor2 > 0) {
            T invNor = 1 / sqrt(nor2);
            x *= invNor, y *= invNor, z *= invNor;
        }

        return *this;
    }
    Vec3<T> operator * (const T& f) const {
        return Vec3<T>(x * f, y * f, z * f);
    }
    T operator * (const Vec3<T>& v) const {
        return x * v.x + y * v.y + z * v.z;
    }
    T cross(const Vec3<T>& v) const {
        return x * v.y - y * v.x;
    }
    Vec3<T> operator - (const Vec3<T>& v) const {
        return Vec3<T>(x - v.x, y - v.y, z - v.z);
    }
    Vec3<T> operator + (const Vec3<T>& v) const {
        return Vec3<T>(x + v.x, y + v.y, z + v.z);
    }
    Vec3<T>& operator += (const Vec3<T>& v) {
        x += v.x, y += v.y, z += v.z;

        return *this;
    }
    Vec3<T>& operator *= (const Vec3<T>& v) {
        x *= v.x, y *= v.y, z *= v.z;

        return *this;
    }
    Vec3<T> operator - () const {
        return Vec3<T>(-x, -y, -z);
    }
    T length() const {
        return sqrt(x * x + y * y + z * z);
    }

    friend std::ostream & operator << (std::ostream &os, const Vec3<T> &v) {
        os << "[" << v.x << " " << v.y << " " << v.z << "]";
        return os;
    }
};

typedef Vec3<GLfloat> Vec3f;

const char *title = "Hermite";

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

void hermite(Vec3f P1, Vec3f P2, Vec3f T1, Vec3f T2) {
    int steps = 1000;

    for (int t = 0; t < steps; t++) {
        float s = (float) t / (float) steps;                 // scale s to go from 0 to 1
        float h1 = 2 * s * s * s - 3 * s * s + 1;          // calculate basis function 1
        float h2 = -2 * s * s * s + 3 * s * s;                 // calculate basis function 2
        float h3 = s * s * s - 2 * s * s + s;              // calculate basis function 3
        float h4 = s * s * s -  s * s;                     // calculate basis function 4

        Vec3f p = P1 * h1 +                    // multiply and sum all funtions
                  P2 * h2 +                    // together to build the interpolated
                  T1 * h3 +                    // point along the curve.
                  T2 * h4;

        std::cout << p << "\n";

        glVertex2f(p.x, p.y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        hermite(Vec3f(-5, -5, 0), Vec3f(5, 5, 0), Vec3f(0, 10, 0), Vec3f(0, 10, 0));
    glEnd();
    glFlush();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                                    // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(500, 500);                             // Set the window's initial width & height
    glutCreateWindow(title);                                  // Create window with the given title
    glutDisplayFunc(display);                                 // Register callback handler for window re-paint event
    initGL();                                                 // Our own OpenGL initialization
    glutMainLoop();                                           // Enter the infinite event-processing loop
    return 0;
}


