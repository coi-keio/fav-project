//
//  Viewer.h
//  fav_library
//
//  Created by atsmsmr on 2016/02/03.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//

#ifndef __fav_library__Viewer__
#define __fav_library__Viewer__

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <iostream>
#include "Fav.h"

class Viewer{
    
private:
    void setupCallback();
    static void displayCallback();
    static void reshapeCallback(int width, int height);
    static void idleCallback();
    static void mouseCallback(int button, int state, int x, int y);
    static void motionCallback(int x, int y);
    static void keyboadCallback(unsigned char key, int x, int y);
    
    void display();
    void reshape(int width, int height);
    void idle();
    void mouse(int button, int state, int x, int y);
    void motion(int x, int y);
    void keyboad(unsigned char key, int x, int y);
    
    void drawRectangle(Box* voxel, float g_angle);
    void drawVoxelModel();
    void drawMeshModel();
    
    float g_angle;
    int g_prevX;
    
    int zoom = -100;
    int slice = 0;
    bool is_voxel = false;
    bool is_mesh = true;
    bool is_path = false;
    bool is_fastmode = true;
    
    FabAbleVoxel* fav;
    
public:
    Viewer();
    ~Viewer();
    void setupGlut(FabAbleVoxel* fav);
    void run();
    int getIndex(int x, int y, int z);

};

static Viewer* glut_viewr_instance;

#endif /* defined(__fav_library__Viewer__) */
