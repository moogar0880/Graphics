/**
 * ControlPanel.cpp - a class to set up user controls and handle changes
 *  in them.
 * 
 * mdp
 * September 21, 2008
 * 09/30/2012 changed by Can Xiong by adding more items
 * 09/15/2013 rdb modified/simplified Can's version
 */

#include <iostream>
#include "ControlPanel.h"

//------------------ Class variables ---------------------------------
ControlPanel *ControlPanel::instance = NULL;

//------------------ Constructors ------------------------------------
/** Initialize values
 */
ControlPanel::ControlPanel()
{
    world = NULL;

    lighting = 1; // Default light is on
    drawAxes = 1; // Default drawAxes
    glui = NULL;

}
//-------------------------------------------------------------------
/** Create the GLUI window, and add controls.
 */
void ControlPanel::initialize( std::string name, int windowID )
{
    //Create interface
    glui = GLUI_Master.create_glui( name.c_str() );
    glui->add_checkbox( "Light on", &lighting,
                       LIGHTING_CHECKBOX, controlChanged_cb );
    glui->add_checkbox( "Draw Axes", &drawAxes,
                       DRAWAXES_CHECKBOX, controlChanged_cb );
    
    glui->add_button( "Quit",
                     QUIT_BUTTON, controlChanged_cb );
    glui->add_button( "Next Scene",
                     NEXTSCENE_BUTTON, controlChanged_cb );
    
    
    // Tell GLUI window which other window to recognize as the main gfx window
    if ( windowID >= 0 )
    {
        glui->set_main_gfx_window( windowID );
        GLUI_Master.set_glutDisplayFunc( redraw_cb );
    }
}

//----------------- setSceneWorld( vector<Scene*> ) -----------------------
/**
 *  define the vector of Scenes we can walk through
 */
void ControlPanel::setSceneWorld( std::vector<Scene*>* allScenes )
{
    world = allScenes;
    
    curSceneIndex = -1;   // initialize to no scene index
    curScene = NULL;
    
    if ( world->size() > 0 )
    {
        nextScene();
    }
}
//------------------ nextScene -------------------------------
/**
 *  setup next scene
 */
void ControlPanel::nextScene()
{
    curSceneIndex++;
    if ( curSceneIndex >= (int)world->size() )
        curSceneIndex = 0;   // wraparound
    std::cerr << "Next scene " << curSceneIndex << "\n";
    
    curScene = world->at( curSceneIndex );
    redraw();
}

//------------------ public class methods --------------------------
/** Return the singleton instance.  If it does not exist, create one.
 */
ControlPanel *ControlPanel::getInstance()
{
    if ( !instance )
        instance = new ControlPanel();
    return instance;
}

//---------------------------------------------------------------------
/** Pass control to the class's controlChanged method
 */
void ControlPanel::controlChanged_cb( int control_enum_value )
{
    getInstance()->controlChanged( control_enum_value );
}
//---------------------------------------------------------------------
/** 
 *  Static call method; just passes control to the class's redraw method
 */
void ControlPanel::redraw_cb()
{
    getInstance()->redraw();
}

//---------------------------------------------------------------------
/** Pass control to the class's controlChanged method
 */
void ControlPanel::redraw()
{
    if ( curScene != NULL )
        curScene->redraw();
}

//-------------------- protected methods -----------------------------
void ControlPanel::controlChanged( int control_enum_value )
{
    switch ( control_enum_value )
    {
        case LIGHTING_CHECKBOX:
            //std::cerr << "Light enabled value changed to " << lighting;
            if( !lighting )
                glDisable( GL_LIGHT0 );
            else
                glEnable( GL_LIGHT0 );
            break;
        case DRAWAXES_CHECKBOX:
            //std::cerr << "Draw Axes value changed to " << drawAxes;
            curScene->setDrawAxes( drawAxes );
            break;
        case NEXTSCENE_BUTTON:
            //std::cerr << "Next Scene \n";
            nextScene();
            break;
        case QUIT_BUTTON:
            //std::cerr << "Exiting..." << std::endl;
            exit( 0 );
            break;

    }
    std::cerr << std::endl;
}
