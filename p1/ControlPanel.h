/**
 * ControlPanel.h - a class to set up user controls and handle changes
 *  in them.
 *
 * mdp
 * September 21, 2008
 */
#ifndef CONTROLPANEL_H_
#define CONTROLPANEL_H_

#include "Shape.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Quad.h"
#include "Polygon.h"
#include "Color.h"
#include <string>
#include <GL/glut.h>
#include <GL/glui.h>

class ControlPanel
{
public:
    //~~~~Singleton Pattern getInstance method~~~~
    static ControlPanel *getInstance();

    //~~~~Methods~~~~
    void initialize(std::string name, int windowID = -1);

protected:
    //~~~~Code Clean Up methods~~~~
    void buildDefaults( GLUI* g );
    void buildScrollbars( GLUI* g );
    void buildShapeRadios( GLUI* g );
    void buildColorLists( GLUI* g );
    void buildColorOptions( GLUI* g );
    void buildDelete( GLUI* g );

    //~~~~Singleton Pattern parts~~~~
    ControlPanel();
    static ControlPanel *instance;

    //~~~~Callback for when controls change, enum to tell them apart.---
    //Callback to register w/ GLUI, and call object-level method
    static void controlChanged_cb( int control_enum_value );
    enum { LIGHTING_CHECKBOX,
           QUIT_BUTTON,
           X_ORIGIN,
           Y_ORIGIN,
           CLEAR_BUTTON,
           SET_DEFAULT_SHAPE,
           BOUNDARY_COLOR,
           FILL_COLOR,
           DRAW_BOUNDARY,
           DRAW_FILL,
           DELETE_NUM
         };
    //object-level method for handling changes in controls
    void controlChanged( int control_enum_value );

    //~~~~Member variables~~~~
    GLUI *glui; //GLUI window
    int lighting;
    float scrollValue;
    float scrollValue2;
    int which_object;
    GLUI_Listbox *border_list, *fill_list;
    GLUI_Checkbox *boundary, *fill;
    GLUI_EditText* num;
    GLUI_RadioGroup* shapeRadios;

    Shape* movableShape;
};

#endif /*CONTROLPANEL_H_*/
