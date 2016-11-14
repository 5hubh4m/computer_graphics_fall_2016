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

const char *title = "Beizer";

std::vector<Vec3f> control;

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

void beizer(int depth) {
    std::cout << control.size() << "\n";

    if (depth > 20)
        return;

    std::vector<Vec3f> new_c;
    Vec3f p[4], q[4], r[4];

    for (size_t i = 0; i < control.size(); i += 4) {
        for (size_t j = 0; j < 4; j++)
            p[j] = control[i + j];

        q[0] = p[0];
        q[1] = (p[0] + p[1]) * 0.5;
        q[2] = (q[1] * 0.5) + ((p[1] + p[2]) * 0.25);
        r[3] = p[3];
        r[2] = (p[2] + p[3]) * 0.5;
        r[1] = ((p[1] + p[2]) * 0.25) + (r[2] * 0.5);
        q[3] = (q[2] + r[1]) * 0.5;
        r[0] = q[3];

        for (size_t j = 0; j < 4; j++)
            new_c.push_back(q[j]);
        for (size_t j = 0; j < 4; j++)
            new_c.push_back(r[j]);
    }

    control = new_c;

    beizer(depth + 1);
}

void display() {
    beizer(0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (auto& a : control) {
        glVertex2f(a.x, a.y);
    }
    glEnd();
    glFlush();
}

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    control.push_back(Vec3f(-5, 1, 0));
    control.push_back(Vec3f(-1, 6, 0));
    control.push_back(Vec3f(1, 0, 0));
    control.push_back(Vec3f(1, 1, 0));

    glutInit(&argc, argv);                                    // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffered mode
    glutInitWindowSize(500, 500);                             // Set the window's initial width & height
    glutCreateWindow(title);                                  // Create window with the given title
    glutDisplayFunc(display);                                 // Register callback handler for window re-paint event
    initGL();                                                 // Our own OpenGL initialization
    glutMainLoop();                                           // Enter the infinite event-processing loop
    return 0;
}


