/**
 * ControlPanel.h - a class to set up user controls and handle changes
 *  in them.
 * 
 * mdp
 * September 21, 2008
 * History:
 * 09302012 changed by Can Xiong by adding more items
 */
#ifndef CONTROLPANEL_H_
#define CONTROLPANEL_H_

#include "Scene.h"
#include "Object3D.h"
#include <string>
#include <vector>

//compatible with windows and linux operating systems
#if defined( __linux__ ) || defined( __CYGWIN )
  #include <GL/glut.h>
  #include <GL/glui.h>
#else 
  #include <glut.h>
  #include <glui.h>
#endif 

class ControlPanel
{
public:
    //----Singleton Pattern getInstance method----
    static ControlPanel *getInstance();
    static void redraw_cb();    // call back for redrawing, needs to be static

    //----Methods----
    void setSceneWorld( std::vector<Scene*>* allScenes );
    void initialize(std::string name, int windowID = -1);
    void setEyePos( float eyeX, float eyeY, float eyeZ );
    void redraw();

protected: 
    //----Singleton Pattern parts----
    ControlPanel();
    static ControlPanel *instance;

    //------ scene collection -----------
    std::vector<Scene*>* world;
    int  curSceneIndex;
    Scene* curScene;

    //----Callback for when controls change, enum to tell them apart.---
    //Callback to register w/ GLUI, and call object-level method
    static void controlChanged_cb( int control_enum_value );
    enum {
           LIGHTING_CHECKBOX,
           DRAWAXES_CHECKBOX,
           QUIT_BUTTON,
           NEXTSCENE_BUTTON
         };
    
    //object-level method for handling changes in controls
    void controlChanged( int control_enum_value );
    
    // go to next scene
    void nextScene();

    //----Member variables----
    GLUI *glui; //GLUI window

    GLUI_RadioGroup *view_group;
    int lighting;
    int drawAxes;
    float translate_xy[2];        //  Translation XY Live Variable
    float translate_z;        //  Translation Z Live Variable
    float rotation_matrix[16]; //  Rotation Matrix Live Variable Array
    
    
    float scale;
    float zoom;
    //----gluLookat----
    float eyeX, eyeY, eyeZ; // eye position
    GLUI_Spinner *spinner0, *spinner1, *spinner2, *spinner3;

    float lookX, lookY, lookZ; // look at position
    GLUI_Spinner *spinner4, *spinner5, *spinner6;

    float upX, upY, upZ; // up vector
    GLUI_Spinner *spinner7, *spinner8, *spinner9;

    //----gluPerspective----
    float viewAngle, aspectRatio, near, far; 
    GLUI_Spinner *spinner10, *spinner11,*spinner12, *spinner13;

    //----glOrtho----
    float left, right, bottom, top, onear, ofar; 
    GLUI_Spinner *spinner14, *spinner15, *spinner16, *spinner17, *spinner18,*spinner19;

    //----glfrustum----
    float fleft, fright, fbottom, ftop, fnear, ffar; 
    GLUI_Spinner *spinner20, *spinner21, *spinner22, *spinner23, *spinner24, *spinner25;
//    Shape* movableShape;
};

#endif /*CONTROLPANEL_H_*/
