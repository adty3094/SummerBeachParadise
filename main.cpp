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
#define PI			3.14159265

GLMmodel *sample1, *sample2, *sample3, *sample4;
float ratio;
float sumbux[101],sumbuz[101], putar[101], angle=0;
float radians     = 0.0f;			   // camera angle in radians
float cameraX, cameraY, cameraZ;
int ganti[101];


int num = 0, a = 0;

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
    if(!sample2){                                           //buat load obj
        sample2 = glmReadOBJ("machete1/1.obj",num);
        if(!sample2) exit(0);
        glmUnitize(sample2);
    }
    if(ganti[2]>0){                                         //buat ganti texture
        sample2 = glmReadOBJ("machete1/1.obj",ganti[2]);
        ganti[2]==0;
        if(!sample2) exit(0);
        glmUnitize(sample2);
        //printf("%d ganti2 ",ganti[2]);
    }
    //printf("ab");
    //printf("%d ganti2 ",ganti[2]);
    if(num == 0) glTranslatef(-1, 0, 0);
    else{
        if(num == 2)
        {
            glTranslatef(sumbux[2]-1, 0, sumbuz[2]);
            glRotated(putar[2], 0, 1, 0);
        }
        else{
            glTranslatef(sumbux[2]-1, 0, sumbuz[2]);
            glRotated(putar[2], 0, 1, 0);
        }
    }
    glScalef(1, 2, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample2, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display3()
{
    glPushMatrix();
    if(!sample3)
    {
        sample3 = glmReadOBJ("Palm-arecaceae.obj",num);
        if(!sample3) exit(0);
        glmUnitize(sample3);
    }
    if(num == 0) glTranslatef(3, 0, -4);
    else{
        if(num == 3)
        {
            glTranslatef(sumbux[3]+3, 0, sumbuz[3]-4);
            glRotated(putar[3], 0, 1, 0);
        }
        else{
            glTranslatef(sumbux[3]+3, 0, sumbuz[3]-4);
            glRotated(putar[3], 0, 1, 0);
        }
    }
    glScalef(1, 2, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3ub(255, 255, 255);
    glmDraw(sample3, GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();
    glFlush();
}

void display4()
{
    glPushMatrix();
    if(!sample4)
    {
        sample4 = glmReadOBJ("rumah.obj",num);
        if(!sample4) exit(0);
        glmUnitize(sample4);
    }
    if(num == 0) glTranslatef(2, 0, -2);
    else{
        if(num == 4)
        {
            glTranslatef(sumbux[2]+2, 0, sumbuz[2]-2);
            glRotated(putar[2], 0, 1, 0);
        }
        else{
            glTranslatef(sumbux[2]+2, 0, sumbuz[2]-2);
            glRotated(putar[2], 0, 1, 0);
        }
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
        sample1 = glmReadOBJ("machete2/2.obj",num);
        if(!sample1) exit(0);
        glmUnitize(sample1);
    }
    if(ganti[1]>0){                                         //buat ganti texture
        sample1 = glmReadOBJ("machete2/2.obj",ganti[1]);
        ganti[1]==0;
        if(!sample1) exit(0);
        glmUnitize(sample1);
        //printf("%d ganti2 ",ganti[2]);
    }
    radians = float(PI*(angle-90.0f)/180.0f);

	cameraX = 0 + sin(radians);
	cameraZ = 3 + cos(radians);

	//printf("%f lookx\n",cameraX);
    //printf("%f lookz\n",cameraZ);

    gluLookAt(0, 3, 5, 0, 0, -5, 0.0, 1.0, 0.0);
    //if(num == 100) glRotatef(sumbux[100],0,1,0);
    display2();
    display3();
    //display4();
    if(num == 0) glTranslatef(0, 0, -5);
    else{
        if(num == 1)
        {
            glTranslatef(sumbux[1], 0, -5+sumbuz[1]);
            glRotated(putar[1], 0, 1, 0);
        }
        else{
            glTranslatef(sumbux[1], 0, -5+sumbuz[1]);
            glRotated(putar[1], 0, 1, 0);
        }
    }

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
        sumbuz[num] -= 0.1;
    }
    if(key == GLUT_KEY_DOWN)
    {
        sumbuz[num] += 0.1;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        sumbux[num] += 0.1;
        if(num == 100) angle += 10;
        //if(num == 4 || num == 2)
    }
    if(key == GLUT_KEY_LEFT)
    {
        sumbux[num] -= 0.1;
        if(num == 100) angle -= 10;
        //if(num == 4 || num == 2)
    }
    //if(key == GLUT_KEY_PAGE_UP)
    //if(key == GLUT_KEY_PAGE_DOWN)
}

void keyboard(unsigned char key, int x, int y ){
    if(key=='1') num = 1;
    if(key=='2') num = 2;
    if(key=='3') num = 3;
    if(key=='4') num = 4;
    if(key=='c') num = 100;
    if(key=='t'){
        if(ganti[num]==1) ganti[num] = 2;
        else if(ganti[num] == 0) ganti[num] = 1;
        else if(ganti[num] == 2) ganti[num] = 1;
    }
    if(key==',') putar[num] += 90;
    if(key=='.') putar[num] -= 90;
}

int main(int argc, char** argv)
{
    for(int i = 0; i < 101; i++)
    {
        sumbux[i] = 0.0;
        sumbuz[i] = 0.0;
        putar[i] = 0.0;
        ganti[i] = 0;
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300, 1);
    glutInitWindowSize(1000, 700);
    glutCreateWindow("Final Project");

    //int palm = glutCreateMenu(mymenu);
    //glutAddMenuEntry("Translasi", 1);
    //glutAddMenuEntry("Rotasi", 2);

    //int rumah = glutCreateMenu(mymenu);
    //glutAddMenuEntry("Translasi", 3);
    //glutAddMenuEntry("Rotasi", 4);

    //glutCreateMenu(mymenu);
    //    glutAddSubMenu("Palm", palm);
        //glutAddSubMenu("Rumah", rumah);
    //glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    //glutMouseFunc(mouse);
    glutSpecialFunc(KeyboardFuncs);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    Init();
    glutMainLoop();
}
