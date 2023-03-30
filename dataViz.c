#define GL_SILENCE_DEPRECATION

// header files
// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <GL/glut.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string[10];
char temp[10];

char *about[] = {"This is a simple data visualization program that uses OpenGl.\n",
                 "The program is designed to visualize data in a 2D environment.\n"};

char *helper[] = {"Press  '1'  to choose Dataset -  Lasagna",
                  "Press  '2'  to choose Dataset -  Lobster",
                  "Press  '3'  to choose Dataset -  Shrimp",
                  "Press  'A'  (Shift+A) to view all graphs together",
                  "Right click to Zoom In and Out",
                  "Press  'h'  to view this help screen",
                  "Press  'q'  to  quit"};

int page = 0, click = 0, h_y = 350, h_x = 640;
#define BSIZE 80
FILE *fp;

void init()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void parse_csv(char *filename)
{
    // char filename[] = "shrimp.csv";
    char buffer[BSIZE];
    FILE *f;

    char *field;
    char year_week[] = "";
    int week_array[675];
    int score_array[675];

    int week_id;
    int score;

    f = fopen(filename, "r");
    if (f == NULL)
    {
        printf("Unable to open file '%s'\n", filename);
        exit(1);
    }
    int i = 0;
    while (fgets(buffer, BSIZE, f))
    {
        field = strtok(buffer, ",");
        field = strtok(NULL, ",");

        field = strtok(NULL, "-");
        week_id = atoi(field);

        field = strtok(NULL, ",");

        field = strtok(NULL, ",");
        score = atoi(field);

        week_array[i] = week_id;
        score_array[i] = score;
        i++;
    }

    fclose(f);

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    {
        for (int i = 0; i < 675; i++)
        {
            glVertex2i((10 + i) / 1.4, score_array[i] * 4);
        }
    }
    glEnd();
}

void draw_string(int x, int y, void *font, char *s)
{
    glRasterPos2i(x, y);
    while (*s)
    {
        glutBitmapCharacter(font, *s);
        s++;
    }
}

void begin_rectangle()
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(155, h_y - 92);
    glVertex2i(155, h_y - 132);
    glVertex2i(155 + 200, h_y - 132);
    glVertex2i(155 + 200, h_y - 92);
    glEnd();
    glColor3f(1, 0, 0.0);
    draw_string(170 + 67, h_y - 42 - 73, GLUT_BITMAP_TIMES_ROMAN_24, "Let's Go");
}

void home_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    draw_string(155, h_y, GLUT_BITMAP_TIMES_ROMAN_24, "DataViz : Visualize your Data");
    draw_string(155, h_y - 28, GLUT_BITMAP_HELVETICA_18, "About :");

    glColor3f(0.3, 1, 1);
    for (int i = 0; i < 2; i++)
    {
        draw_string(155, h_y - 42 - i * 15, GLUT_BITMAP_HELVETICA_18, about[i]);
    }

    glColor3f(0, 1, 0);
    glLineWidth(3);
    begin_rectangle();
    draw_string(440, 10, GLUT_BITMAP_TIMES_ROMAN_24, "Amartya Nambiar");

    glutPostRedisplay();
    glFlush();
}

void control_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    draw_string(180, h_y - 24, GLUT_BITMAP_TIMES_ROMAN_24, "Controls :");
    glColor3f(0.3, 1, 1);
    for (int i = 0; i < 6; i++)
    {
        draw_string(180, h_y - 42 - i * 15, GLUT_BITMAP_HELVETICA_18, helper[i]);
    }
    glColor3f(1, 0, 0);
    draw_string(440, 10, GLUT_BITMAP_TIMES_ROMAN_24, "Amartya Nambiar");
}

void lasagna_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    draw_string(240, 475, GLUT_BITMAP_TIMES_ROMAN_24, "Lasagna");

    glColor3f(0, 0, 1);
    parse_csv("lasagna.csv");
    glutPostRedisplay();
    glFlush();
}
void lobster_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    draw_string(240, 475, GLUT_BITMAP_TIMES_ROMAN_24, "Lobster");

    glColor3f(0, 1, 1);
    parse_csv("lobster.csv");
    glutPostRedisplay();
    glFlush();
}
void shrimp_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    draw_string(240, 475, GLUT_BITMAP_TIMES_ROMAN_24, "Shrimp");

    glColor3f(1, 0, 1);
    parse_csv("shrimp.csv");
    glutPostRedisplay();
    glFlush();
}
void combined_screen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    draw_string(240, 475, GLUT_BITMAP_TIMES_ROMAN_24, "Combined");

    glColor3f(1, 0, 0);
    draw_string(8, 475, GLUT_BITMAP_TIMES_ROMAN_24, "Legend");

    glColor3f(0, 0, 1);
    draw_string(12, 445, GLUT_BITMAP_HELVETICA_18, "-- Lasagna");
    parse_csv("lasagna.csv");

    glColor3f(0, 1, 1);
    draw_string(12, 455, GLUT_BITMAP_HELVETICA_18, "-- Shrimp");
    parse_csv("shrimp.csv");

    glColor3f(1, 0, 1);
    draw_string(12, 465, GLUT_BITMAP_HELVETICA_18, "-- Lobster");
    parse_csv("lobster.csv");

    glutPostRedisplay();
    glFlush();
}

void display()
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    if (page == 0)
    {
        home_screen();
    }
    if (page == 5)
    {
        control_screen();
    }
    if (page == 1)
    {
        lasagna_screen();
    }
    if (page == 2)
    {
        lobster_screen();
    }
    if (page == 3)
    {
        shrimp_screen();
    }
    if (page == 4)
    {
        combined_screen();
    }
    glutSwapBuffers();
    glFlush();
}

void selection(int x, int y)
{
    int hit, buffer[100], viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    // printf("%d %d %d %d\n", viewport[0], viewport[1], viewport[2], viewport[3]);
    glSelectBuffer(100, (GLuint *)buffer);
    glInitNames();
    glPushName(0);
    glRenderMode(GL_SELECT);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPickMatrix(x, viewport[3] - y, 500, 500, viewport);
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushName(10);
    glRectf(100, 100, 200, 200);
    glLoadName(11);
    glRectf(300, 300, 400, 400);
    glPopMatrix();
    glRenderMode(GL_RENDER);
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y)
{
    // printf("%d %d\n", x, y);
    if (page == 0)
    {
        if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (x > 500 && x < 1220 && y > 480 && y < 610)
            {
                page = 5;
                glutPostRedisplay();
            }
        }
    }

    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (click == 0)
        {
            selection(x, y);

            click = 1;
        }
        else
        {
            glViewport(0, 0, 1680, 1050);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0, 500, 0, 500);
            glMatrixMode(GL_MODELVIEW);
            glutPostRedisplay();
            click = 0;
        }
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
        exit(0);
    }
    if (page == 0)
    {
        if (key == 'g')
        {
            page = 5;
            glutPostRedisplay();
        }
    }

    switch (key)
    {
    case '1':

        page = 1;
        display();
        break;

    case '2':
        page = 2;
        display();
        break;

    case '3':
        page = 3;
        display();
        break;

    case 'A':
        page = 4;
        display();
        break;

    case 'h':
        page = 5;
        display();
        break;

    default:
        break;
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);
    glutCreateWindow("DataViz");
    init();
    glutFullScreen();
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);

    glutMainLoop();
}