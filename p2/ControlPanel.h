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
    void getInitValues( void );

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
           NEXTSCENE_BUTTON,
           PREVSCENE_BUTTON,
           SET_PROJECTION,
           SET_LOOKAT,
           LOOKAT,
           SET_ADVANCED,
           ADVANCED,
           PERSPECTIVE,
           BOX_BUTTON,
           CLOWN_BUTTON,
           DONUT_BUTTON,
           EYE_BUTTON,
           HAT_BUTTON,
           HEAD_BUTTON,
           SNOWMAN_BUTTON,
           SPHERE_BUTTON
         };

    //object-level method for handling changes in controls
    void controlChanged( int control_enum_value );

    // go to next scene
    void nextScene();
    // go to the previous scene
    void prevScene();
    void resetSliders( void );

    void setPanel( void );
    void clearPanels( void );

    // Scene updaters
    void updateWorldWithSlider( void );
    void updateWorldProjections( void );
    void updateAdvanced( void );
    float* packageOrtho( void );
    float* packageFrustum( void );

    // Slider updaters
    void setLookAtSliders( void );
    void setAdvancedSliders( void );

    // ControlPanel Builders
    void buildProjectionChoice( GLUI* g );
    void buildLookAtPanel( GLUI* g );
    void buildPerspectivePanel( GLUI* g );
    void buildAdvancedPanel( GLUI* g );
    void buildCreateShapeButtons( GLUI* g );

    //----Member variables----
    GLUI *glui; //GLUI window

    GLUI_RadioGroup *advanced_group, *lookAt_group, *projection_group;
    int lighting;
    int drawAxes;
    int which_lookat, which_advanced, which_projection;
    float translate_xy[2];     //  Translation XY Live Variable
    float translate_z;         //  Translation Z Live Variable
    float rotation_matrix[16]; //  Rotation Matrix Live Variable Array


    float scale;
    float zoom;
    GLUI_Panel *lookAtPanel, *perspectivePanel, *advancedPanel;
    //----gluLookat----
    float newX, newY, newZ;
    float eyeX, eyeY, eyeZ; // eye position
    GLUI_Scrollbar *slider0, *slider1, *slider2, *slider3;

    float lookX, lookY, lookZ; // look at position

    float upX, upY, upZ; // up vector

    //----gluPerspective----
    float viewAngle, aspectRatio, near, far;
    GLUI_Scrollbar *slider4, *slider5, *slider6, *slider7;

    //----glOrtho----
    float newLeft, newRight, newBottom, newTop, newNear, newFar;
    float left, right, bottom, top, onear, ofar;
    GLUI_Scrollbar *slider8, *slider9, *slider10, *slider11, *slider12, *slider13;

    //----glfrustum----
    float fleft, fright, fbottom, ftop, fnear, ffar;
};

#endif /*CONTROLPANEL_H_*/
