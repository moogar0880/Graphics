/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ControlPanel.cpp - a class to set up user controls and handle changes
 *  in them.
 *
 * @author Jonathan Nappi
 * @date   September 22, 2013
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include <iostream>  // gets cout, cerr
#include <stdlib.h>  // gets exit

#include "ControlPanel.h"
#include "Scene.h"

ControlPanel *ControlPanel::instance = NULL;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * No arg constructor just initializes all major values
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ControlPanel::ControlPanel(){
    //initialize values
    if( !Scene::getInstance()->empty() )
        scrollValue = Scene::getInstance()->get_most_recent()->getX();
    else
        scrollValue = 0.0;
    if( !Scene::getInstance()->empty() )
        scrollValue2 = Scene::getInstance()->get_most_recent()->getY();
    else
        scrollValue2 = 0.0;
    lighting = 0;
    glui = 0;
    movableShape = NULL;
    which_object = 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add ControlPanel functionality to enable/disable lighting, clear
 *      the display, or quit the app
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildDefaults( GLUI* g ){
    g->add_checkbox( "Lighting", &lighting,
                        LIGHTING_CHECKBOX, controlChanged_cb );

    g->add_button( "Clear Display",
                      CLEAR_BUTTON, controlChanged_cb );

    g->add_button( "Quit",
                      QUIT_BUTTON, controlChanged_cb );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add ControlPanel functionality to move the most recent shape around
 *      using GLUI sliders
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildScrollbars( GLUI* g ){
    GLUI_Scrollbar *newScroll;
    newScroll = new GLUI_Scrollbar( g->add_panel( "X location" ),
                                    "leftScroll", GLUI_SCROLL_HORIZONTAL,
                                    &scrollValue, X_ORIGIN,
                                    controlChanged_cb );
    newScroll->set_float_limits( 0.0, 800.0 );

    newScroll = new GLUI_Scrollbar( g->add_panel( "Y location" ),
                                    "RightScroll", GLUI_SCROLL_HORIZONTAL,
                                    &scrollValue2, Y_ORIGIN,
                                    controlChanged_cb );
    newScroll->set_float_limits( 0.0, 600.0 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add ControlPanel functionality to select the default shape to be drawn
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildShapeRadios( GLUI* g ){
    GLUI_Panel *panel, *radioPanel;
    radioPanel = g->add_panel( "" );
    panel = g->add_panel_to_panel( radioPanel, "Shape Selection" );
    shapeRadios = g->add_radiogroup_to_panel( panel, &which_object, SET_DEFAULT_SHAPE, controlChanged_cb );
    g->add_radiobutton_to_group( shapeRadios, "Triangle" );
    g->add_radiobutton_to_group( shapeRadios, "Rectangle" );
    g->add_radiobutton_to_group( shapeRadios, "Quad" );
    g->add_radiobutton_to_group( shapeRadios, "Polygon" );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add ControlPanel functionality to choose border and fill colors
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildColorLists( GLUI* g ){
    border_list = g->add_listbox("Select a Border Color ", NULL,
                                 BOUNDARY_COLOR, controlChanged_cb);
    border_list->add_item(1,"Red");
    border_list->add_item(2,"Green");
    border_list->add_item(3,"Blue");

    fill_list = g->add_listbox("Select a Fill Color ", NULL,
                                 FILL_COLOR, controlChanged_cb);
    fill_list->add_item(1,"Red");
    fill_list->add_item(2,"Green");
    fill_list->add_item(3,"Blue");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add ControlPanel functionality to enable/disable drawing border and
 *      fill colors
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildColorOptions( GLUI* g ){
    GLUI_Panel *panel;
    panel = g->add_panel( "Color Options" );
    boundary = g->add_checkbox_to_panel( panel, "Draw Boundary", NULL,
                                            DRAW_BOUNDARY, controlChanged_cb );
    boundary->set_int_val( 1 );
    fill = g->add_checkbox_to_panel( panel, "Draw Fill", NULL,
                                        DRAW_FILL, controlChanged_cb );
    fill->set_int_val( 1 );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Add ControlPanel functionality to delete the shape at a provided index
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildDelete( GLUI* g ){
    GLUI_Panel *panel;
    panel = g->add_panel( "Delete a Shape" );
    num = g->add_edittext_to_panel(panel, "Shape ID to Delete",
                                   DELETE_NUM, NULL, -1, controlChanged_cb);
    g->add_button_to_panel( panel, "Delete Selected Shape",
                            DELETE_NUM, controlChanged_cb);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Creates GLUI window and adds menu controls
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::initialize( std::string name, int windowID ){
    //Create interface
    glui = GLUI_Master.create_glui( name.c_str() );

    buildDefaults( glui );
    buildScrollbars( glui );
    buildShapeRadios( glui );
    buildColorLists( glui );
    buildColorOptions( glui );

    // Tell GLUI window which other window to recognize as the main gfx window
    if ( windowID >= 0 )
        glui->set_main_gfx_window( windowID );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Return the singleton instance, if one does not exist then create it
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ControlPanel *ControlPanel::getInstance(){
    if ( !instance )
        instance = new ControlPanel();
    return instance;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Callback for passing control to the controlChanged method
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::controlChanged_cb( int control_enum_value ){
    getInstance()->controlChanged( control_enum_value );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Control changed function uses a switch statement to determine the
 *      appropriate state of the control
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::controlChanged( int control_enum_value ){
    float x = 0;
    float y = 0;
    int c;
    bool b;
    Shape* s = NULL;
    if( !Scene::getInstance()->empty() )
        s = Scene::getInstance()->get_most_recent();
    switch ( control_enum_value ){
        case LIGHTING_CHECKBOX:
            std::cerr << "Lighting value changed to " << lighting;
            break;
        case QUIT_BUTTON:
            std::cerr << "Exiting..." << std::endl;
            exit( 0 );
            break;
        case X_ORIGIN:
            x = scrollValue;
            if ( s != NULL )
                s->setLocation( x, s->getY() );
            std::cerr<< "x Moved to " << x;
            break;
        case Y_ORIGIN:
            y = scrollValue2;
            if ( s != NULL )
                s->setLocation( s->getX(), y );
            std::cerr<< "Right Point Moved to " << y;
            break;
        case CLEAR_BUTTON:
            std::cerr << "Clearing the scene..." << std::endl;
            Scene::getInstance()->clear();
            break;
        case SET_DEFAULT_SHAPE:
            std::cerr << "Default shape set to " << which_object << std::endl;
            Scene::getInstance()->current_shape_set( which_object );
            break;
        case BOUNDARY_COLOR:
            c = border_list->get_int_val();
            std::cerr << c << std::endl;
            if( c == 1 ){
                std::cerr << "Border Color set to Red" << std::endl;
                Scene::getInstance()->set_boundary_color( new Color(1,0,0) );
            }
            else if( c == 2 ){
                std::cerr << "Border Color set to Green" << std::endl;
                Scene::getInstance()->set_boundary_color( new Color(0,1,0) );
            }
            else{
                std::cerr << "Border Color set to Blue" << std::endl;
                Scene::getInstance()->set_boundary_color( new Color(0,0,1) );
            }
            break;
        case FILL_COLOR:
            c = fill_list->get_int_val();
            if( c == 1 ){
                std::cerr << "Fill Color set to Red" << std::endl;
                Scene::getInstance()->set_fill_color( new Color(1,0,0) );
            }
            else if( c == 2 ){
                std::cerr << "Fill Color set to Green" << std::endl;
                Scene::getInstance()->set_fill_color( new Color(0,1,0) );
            }
            else{
                std::cerr << "Fill Color set to Blue" << std::endl;
                Scene::getInstance()->set_fill_color( new Color(0,0,1) );
            }
            break;
        case DRAW_BOUNDARY:
            b = boundary->get_int_val() != 0;
            std::cerr << "Draw Boundary set to " << b << std::endl;
            Scene::getInstance()->set_draw_boundary( b );
            break;
        case DRAW_FILL:
            b = fill->get_int_val() != 0;
            std::cerr << "Draw Fill set to " << b << std::endl;
            Scene::getInstance()->set_draw_fill( b );
            break;
        case DELETE_NUM:
            std::cerr << "Deleting shape " << num->get_text() << std::endl;
            Scene::getInstance()->remove(atoi(num->get_text()));
            break;
    }
    std::cerr << std::endl;
}
