//
//  Viewer.cpp
//  fav_library
//
//  Created by atsmsmr on 2016/02/03.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//

#include "Viewer.h"

Viewer::Viewer(){
    g_angle = 0.0f;
    g_prevX = -1;
}

Viewer::~Viewer(){}

void Viewer::motion(int x, int y)

{
    
	g_angle += (float)(x - g_prevX);
    
	if (g_angle > 360.0f) {
        
		g_angle -= 360.0f;
        
	}
    
	g_prevX = x;
    
	glutPostRedisplay();
}



void Viewer::mouse(int button, int state, int x, int y)

{
    
	if (button == GLUT_LEFT_BUTTON) {
        
		if (state == GLUT_DOWN) {
            
			g_prevX = x;
            
			glutMotionFunc(motionCallback);
            
		}
        
		else if (state == GLUT_UP) {
            
			glutMotionFunc(NULL);
            
		}
        
	}
    
}



void Viewer::reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)width / (float)height, 0.01, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    glTranslated(0.0, 10.0, -130);
    //gluLookAt(0.5, 1.5, 2.5+zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
}


void Viewer::display()
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(0, 0, -zoom, 0, 0, -1, 0, 1, 0);
    
    drawVoxelModel();
    
    glFlush();
	glutSwapBuffers();
}

void Viewer::keyboad(unsigned char key,  int x, int y) {
    
    
	if(key=='a'){
        zoom += 2;
        display();
    }else if(key=='z'){
        zoom -= 2;
        display();
    }else if(key=='v'){
        is_voxel = true;
        is_mesh = false;
        display();
    }else if(key=='m'){
        is_voxel = false;
        is_mesh = true;
        display();
    }else if(key=='f'){
        is_fastmode = !is_fastmode;
        display();
    }
    
}

void Viewer::displayCallback(){
    glut_viewr_instance->display();
}

void Viewer::reshapeCallback(int width, int height){
    glut_viewr_instance->reshape(width, height);
}

void Viewer::mouseCallback(int button, int state, int x, int y){
    glut_viewr_instance->mouse(button, state, x, y);
}

void Viewer::motionCallback(int x, int y){
    glut_viewr_instance->motion(x, y);
}

void Viewer::keyboadCallback(unsigned char key, int x, int y){
    glut_viewr_instance->keyboad(key, x, y);
}

void Viewer::setupCallback(){
    glut_viewr_instance = this;
    glutDisplayFunc(Viewer::displayCallback);
    glutReshapeFunc(Viewer::reshapeCallback);
    glutKeyboardFunc(Viewer::keyboadCallback);
	glutMouseFunc(Viewer::mouseCallback);
}

void Viewer::setupGlut(FabAbleVoxel* fav){
    
    this->fav = fav;
    
    char *argv[] = {"Fav_Viewer"};
    int argc = 1;
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Fav Viewer");
    setupCallback();
    
    static GLfloat lightPosition[4] = {0.25f, 0.5f, 0.25f, 0.0f};
	static GLfloat lightDiffuse[3] = {1.0f, 1.0f, 1.0f};
	static GLfloat lightAmbient[3] = {1.25f, 1.25f, 1.25f};
	static GLfloat lightSpecular[3] = {1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_LIGHTING);
    //	glEnable(GL_LIGHT0);
    
}

void Viewer::run(){
    glutMainLoop();
}

int Viewer::getIndex(int x, int y, int z){
    
    int x_num = fav->objects[0]->voxel->voxel_num[0];
    int y_num = fav->objects[0]->voxel->voxel_num[1];

    return (x_num*y_num*z) + (x_num*y) + x;
    
}

void Viewer::drawRectangle(Box* voxel, float g_angle){
    
    float x = voxel->position[0];
    float y = voxel->position[2];
    float z = voxel->position[1];
    
    float length_x = voxel->length[0]/2.0f;
    float length_y = voxel->length[2]/2.0f;
    float length_z = voxel->length[1]/2.0f;
    
    GLfloat vertices[8][3] =
    {
        {x - length_x, y + length_y, z + length_z},
        {x - length_x, y - length_y, z + length_z},
        {x + length_x, y - length_y, z + length_z},
        {x + length_x, y + length_y, z + length_z},
        
        {x - length_x, y + length_y, z - length_z},
        {x - length_x, y - length_y, z - length_z},
        {x + length_x, y - length_y, z - length_z},
        {x + length_x, y + length_y, z - length_z}
    };
    
    int indices[6][4]=
    {
        //top
        {0,1,2,3},
        //bottom
        {4,5,6,7},
        //front
        {0,3,7,4},
        //back
        {1,5,6,2},
        //left
        {0,4,5,1},
        //right
        {2,6,7,3}
    };
    
    GLfloat normals[6][3]=
    {
        {0,1,0},
        {0,-1,0},
        {-1,0,0},
        {1,0,0},
        {0,0,-1},
        {0,0,1}
    };
    
    glPushMatrix();
    glRotatef(g_angle, 0.0f, 1.0f, 0.0f);
    
    for(int i=0; i<6; i++){
        glBegin(GL_POLYGON);
        glNormal3fv(normals[i]);
		glVertex3fv(vertices[indices[i][0]]);
		glVertex3fv(vertices[indices[i][1]]);
		glVertex3fv(vertices[indices[i][2]]);
		glVertex3fv(vertices[indices[i][3]]);
        glEnd();
    }
    
    glPopMatrix();
}


void Viewer::drawVoxelModel(){
    
    int voxbb_length[3];
    for(int i=0; i<3; i++){
        voxbb_length[i] = fav->objects[0]->voxel->voxel_size[i]*fav->objects[0]->voxel->voxel_num[i];
    }
    
    int x_num = fav->objects[0]->voxel->voxel_num[0];
    int y_num = fav->objects[0]->voxel->voxel_num[1];
    int z_num = fav->objects[0]->voxel->voxel_num[2];
    
    if(is_fastmode){
        glPushMatrix();
        glRotatef(g_angle, 0.0f, 1.0f, 0.0f);
        glPointSize(1);
        glBegin(GL_POINTS);
    }
    
    for(int z=0; z<z_num; z++){
        for(int y=0; y<y_num; y++){
            for(int x=0; x<x_num; x++){
                
                int index = getIndex(x,y,z);
                Voxel* voxel = &fav->objects[0]->voxel->data[index];
                if(is_fastmode && voxel->state != 0){
                    glColor4f(voxel->color.r,voxel->color.g,voxel->color.b,voxel->color.a);
                    Box currentVoxel;
                    currentVoxel.length[0] = fav->objects[0]->voxel->voxel_size[0];
                    currentVoxel.length[1] = fav->objects[0]->voxel->voxel_size[1];
                    currentVoxel.length[2] = fav->objects[0]->voxel->voxel_size[2];
                    currentVoxel.position[0] = x * currentVoxel.length[0] - (voxbb_length[0]*0.5f+currentVoxel.length[0]*0.5f);
                    currentVoxel.position[2] = y * currentVoxel.length[1] - (voxbb_length[1]*0.5f+currentVoxel.length[1]*0.5f);
                    currentVoxel.position[1] = z * currentVoxel.length[2] - (voxbb_length[2]*0.5f+currentVoxel.length[2]*0.5f);
                    
                    glVertex3f(currentVoxel.position[0],currentVoxel.position[1],currentVoxel.position[2]);
                    
                }else if(voxel->state != 0){
                    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
                    glColor4f(voxel->color.r,voxel->color.g,voxel->color.b,voxel->color.a);
                    
                    Box currentVoxel;
                    currentVoxel.length[0] = fav->objects[0]->voxel->voxel_size[0];
                    currentVoxel.length[1] = fav->objects[0]->voxel->voxel_size[1];
                    currentVoxel.length[2] = fav->objects[0]->voxel->voxel_size[2];
                    currentVoxel.position[0] = x * currentVoxel.length[0] - (voxbb_length[0]*0.5f+currentVoxel.length[0]*0.5f);
                    currentVoxel.position[1] = y * currentVoxel.length[1] - (voxbb_length[1]*0.5f+currentVoxel.length[1]*0.5f);
                    currentVoxel.position[2] = z * currentVoxel.length[2] - (voxbb_length[2]*0.5f+currentVoxel.length[2]*0.5f);
                    this->drawRectangle(&currentVoxel, g_angle);
                }
            }
        }
    }
    
    if(is_fastmode){
        glEnd();
        glPopMatrix();
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glColor4f(0,0,0,0.0);
    }
    
}



