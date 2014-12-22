#include <stdio.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <gl\glut.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "glm.h"

using namespace std;

GLMmodel *sample1, *sample2;
float ratio;
float atas[101], kanan[101];
float up[101], Right[101], save[101];
int rotasi[10];

int num = 0, a = 0;

void mymenu(int id)
{
    num = id;
    printf("%d\n", num);
    //glutPostRedisplay();
}

void Init()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void display2()
{
    glPushMatrix();
    if(!sample2)
    {
        sample2 = glmReadOBJ("rumah.obj");
        if(!sample2) exit(0);
        glmUnitize(sample2);
    }
    if(num == 0) glTranslatef(2, 1.5, -5);
    else
        if(num == 3)
        {
            glTranslatef(2+kanan[num], 1.5, -5+atas[num]);
            up[3] = atas[num];
            Right[3] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            glTranslatef(2+Right[3], 1.5, -5+up[3]);
    if(num == 4)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }
    glScalef(1, 2, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0,1,1,1);
    glLoadIdentity();
    glPushMatrix();
    //glRotated(rotasi[num], 0, 1, 0);
    if(!sample1)
    {
        sample1 = glmReadOBJ("Palm-arecaceae.obj");
        if(!sample1) exit(0);
        glmUnitize(sample1);
    }
    //cout << GetObjectA() << endl;
    gluLookAt(0, 3, 3, 0, 0, -5, 0.0, 1.0, 0.0);
    //display2();
    /*if(num == 0) glTranslatef(0, 0, -5);
    else
        if(num == 1)
        {
            glTranslatef(kanan[num], 0, -5+atas[num]);
            up[1] = atas[num];
            Right[1] = kanan[num];
            glRotated(rotasi[num+1], 0, 1, 0);
        }
        else
            glTranslatef(Right[1], 0, -5+up[1]);
    if(num == 2)
    {
        glRotated(rotasi[num], 0, 1, 0);
    }*/
    glTranslatef(kanan[num], 0, -5+atas[num]);
    glRotated(rotasi[num], 0, 1, 0);
    glScalef(1, 1, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample1, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    if (h == 0) h = 1;
    ratio = 1.0 * w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(80, ratio, 1, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//int onMouse = 1;
/*void mouseClicks(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        onMouse = 1;
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        onMouse = 2;
    }
}*/

void KeyboardFuncs(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
    {
        atas[num] += 0.5;
    }
    if(key == GLUT_KEY_DOWN)
    {
        atas[num] -= 0.5;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        kanan[num] += 0.5;
        //if(num == 4 || num == 2)
    }
    if(key == GLUT_KEY_LEFT)
    {
        kanan[num] -= 0.5;
        //if(num == 4 || num == 2)
    }
    //if(key == GLUT_KEY_PAGE_UP)
    //if(key == GLUT_KEY_PAGE_DOWN)
}

void keyboard(unsigned char key, int x, int y ){
    if(key==',') rotasi[num] += 90;
    if(key=='.') rotasi[num] -= 90;
}

int main(int argc, char** argv)
{
    for(int i = 0; i < 101; i++)
    {
        atas[i] = 0.0;
        kanan[i] = 0.0;
        up[i] = 0.0;
        Right[i] = 0.0;
        save[i] = 0.0;
        rotasi[i] = 0;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300, 1);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Final Project");

    int palm = glutCreateMenu(mymenu);
    glutAddMenuEntry("Translasi", 1);
    glutAddMenuEntry("Rotasi", 2);

    //int rumah = glutCreateMenu(mymenu);
    //glutAddMenuEntry("Translasi", 3);
    //glutAddMenuEntry("Rotasi", 4);

    glutCreateMenu(mymenu);
        glutAddSubMenu("Palm", palm);
        //glutAddSubMenu("Rumah", rumah);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutIdleFunc(display);
//    glutMouseFunc(mouseClicks);
    glutSpecialFunc(KeyboardFuncs);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    Init();
    glutMainLoop();
}
