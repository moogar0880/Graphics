/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ControlPanel.cpp - a class to set up user controls and handle changes
 *  in them.
 *
 * mdp
 * September 21, 2008
 * 09/30/2012 changed by Can Xiong by adding more items
 * 09/15/2013 rdb modified/simplified Can's version
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include "ControlPanel.h"

//------------------ Class variables ---------------------------------
ControlPanel *ControlPanel::instance = NULL;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Initialize values
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ControlPanel::ControlPanel(){
    world = NULL;

    lighting = 1; // Default light is on
    drawAxes = 1; // Default drawAxes
    glui = NULL;
    which_lookat = which_advanced = which_light = 0;
    which_projection = 1;
    newX = newY = newZ = viewAngle = aspectRatio = near = far =
        newLeft = newRight = newBottom = newTop = newNear =
        newFar = 0.0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Build the description panel
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildDescriptionField( GLUI* g ){
    GLUI_Panel* panel;
    panel = g->add_panel( "Scene Description" );
    scene_description = g->add_statictext_to_panel( panel, (char*)"TEXT" );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Build the projection type radio buttons
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildProjectionChoice( GLUI* g ){
    GLUI_Panel* panel;
    panel = g->add_panel( "Projection Type" );
    projection_group = g->add_radiogroup_to_panel( panel,
                                                   &which_projection,
                                                   SET_PROJECTION,
                                                   controlChanged_cb );
    g->add_radiobutton_to_group( projection_group, "Parallel" );
    g->add_radiobutton_to_group( projection_group, "Perspective" );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Build the Look at radio buttons and sliders
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildLookAtPanel( GLUI* g ){
    lookAtPanel = g->add_panel( "Look At Controls" );
    lookAt_group = g->add_radiogroup_to_panel( lookAtPanel,
                                               &which_lookat,
                                               SET_LOOKAT,
                                               controlChanged_cb );
    g->add_radiobutton_to_group( lookAt_group, "Eye" );
    g->add_radiobutton_to_group( lookAt_group, "Look At" );
    g->add_radiobutton_to_group( lookAt_group, "Up" );
    g->add_radiobutton_to_group( lookAt_group, "Ambient Light" );
    g->add_radiobutton_to_group( lookAt_group, "Directional Light" );
    slider1 = new GLUI_Scrollbar( lookAtPanel, "X Slider",
                                   GLUI_SCROLL_HORIZONTAL, &newX,
                                   LOOKAT, controlChanged_cb );
    slider1->set_float_limits(-300.0,300.0);
    slider2 = new GLUI_Scrollbar( lookAtPanel, "Y Slider",
                                  GLUI_SCROLL_HORIZONTAL, &newY,
                                  LOOKAT, controlChanged_cb );
    slider2->set_float_limits(-300.0,300.0);
    slider3 = new GLUI_Scrollbar( lookAtPanel, "Z Slider",
                                  GLUI_SCROLL_HORIZONTAL, &newZ,
                                  LOOKAT, controlChanged_cb );
    slider3->set_float_limits(-300.0,300.0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Build the perspective sliders
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildPerspectivePanel( GLUI* g ){
    perspectivePanel = g->add_panel( "Perspective Controls" );
    slider4 = new GLUI_Scrollbar( perspectivePanel, "View Angle",
                                   GLUI_SCROLL_HORIZONTAL, &viewAngle,
                                   PERSPECTIVE, controlChanged_cb );
    slider4->set_float_limits(-300.0,300.0);
    slider5 = new GLUI_Scrollbar( perspectivePanel, "Aspect Ratio",
                                   GLUI_SCROLL_HORIZONTAL, &aspectRatio,
                                   PERSPECTIVE, controlChanged_cb );
    slider5->set_float_limits(-300.0,300.0);
    slider6 = new GLUI_Scrollbar( perspectivePanel, "Near",
                                   GLUI_SCROLL_HORIZONTAL, &near,
                                   PERSPECTIVE, controlChanged_cb );
    slider6->set_float_limits(-300.0,300.0);
    slider7 = new GLUI_Scrollbar( perspectivePanel, "Far",
                                   GLUI_SCROLL_HORIZONTAL, &far,
                                   PERSPECTIVE, controlChanged_cb );
    slider7->set_float_limits(-300.0,300.0);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Build the light color controls
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::buildLightColorPanel( GLUI* g ){
    colorPanel = g->add_panel( "Light Color Controls");
    light_group = g->add_radiogroup_to_panel( colorPanel,
                                              &which_light,
                                              SET_LIGHT,
                                              controlChanged_cb );
    g->add_radiobutton_to_group( light_group, "Ambient" );
    g->add_radiobutton_to_group( light_group, "Directional" );
    slider14 = new GLUI_Scrollbar( colorPanel, "Red", 
                                   GLUI_SCROLL_HORIZONTAL, &newR, 
                                   COLOR, controlChanged_cb );
    slider15 = new GLUI_Scrollbar( colorPanel, "Green", 
                                   GLUI_SCROLL_HORIZONTAL, &newR, 
                                   COLOR, controlChanged_cb );
    slider16 = new GLUI_Scrollbar( colorPanel, "Blue", 
                                   GLUI_SCROLL_HORIZONTAL, &newR, 
                                   COLOR, controlChanged_cb );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Create the GLUI window and add controls
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::initialize( std::string name, int windowID ){
    //Create interface
    glui = GLUI_Master.create_glui( name.c_str() );
    buildDescriptionField( glui );
    glui->add_checkbox( "Light on", &lighting,
                       LIGHTING_CHECKBOX, controlChanged_cb );
    glui->add_checkbox( "Draw Axes", &drawAxes,
                       DRAWAXES_CHECKBOX, controlChanged_cb );

    glui->add_button( "Quit",
                     QUIT_BUTTON, controlChanged_cb );
    glui->add_button( "Previous Scene",
                     PREVSCENE_BUTTON, controlChanged_cb );
    glui->add_button( "Next Scene",
                     NEXTSCENE_BUTTON, controlChanged_cb );

    buildProjectionChoice( glui );
    buildLookAtPanel( glui );
    buildPerspectivePanel( glui );
    buildLightColorPanel( glui );

    // Tell GLUI window which other window is the main gfx window
    if ( windowID >= 0 ){
        glui->set_main_gfx_window( windowID );
        GLUI_Master.set_glutDisplayFunc( redraw_cb );
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Update the corresponding variables and reflect these changes in the
 *  current scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::updateWorldWithSlider( void ){
    switch( which_lookat ){
        case 0:
            eyeX = newX;
            eyeY = newY;
            eyeZ = newZ;
            world->at( curSceneIndex )->setLookat( eyeX, eyeY, eyeZ,
                                           lookX, lookY, lookZ,
                                           upX, upY, upZ );
            break;
        case 1:
            lookX = newX;
            lookY = newY;
            lookZ = newZ;
            world->at( curSceneIndex )->setLookat( eyeX, eyeY, eyeZ,
                                           lookX, lookY, lookZ,
                                           upX, upY, upZ );
            break;
        case 2:
            upX = newX;
            upY = newY;
            upZ = newZ;
            world->at( curSceneIndex )->setLookat( eyeX, eyeY, eyeZ,
                                           lookX, lookY, lookZ,
                                           upX, upY, upZ );
            break;
        case 3: // Ambient Light
            world->at( curSceneIndex )->setAmbientLoc( newX, newY, newZ );
            break;
        case 4: // Directional Light
            world->at( curSceneIndex )->setDirectionalLoc( newX, newY, newZ );
            break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Sets the lookat sliders when their radio button context has changed
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::setLookAtSliders(){
    float* vals = world->at( curSceneIndex )->getLookat();
    switch( which_lookat ){
        case 0:
            slider1->set_float_val( vals[0] );
            eyeX = vals[0];
            slider1->set_float_val( vals[1] );
            eyeY = vals[1];
            slider1->set_float_val( vals[2] );
            eyeZ = vals[2];
            break;
        case 1:
            slider1->set_float_val( vals[3] );
            lookX = vals[3];
            slider1->set_float_val( vals[4] );
            lookY = vals[4];
            slider1->set_float_val( vals[5] );
            lookZ = vals[5];
            break;
        case 2:
            slider1->set_float_val( vals[6] );
            upX = vals[6];
            slider1->set_float_val( vals[7] );
            upY = vals[7];
            slider1->set_float_val( vals[8] );
            upZ = vals[8];
            break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Updates the projection values and then reflects the changes in the
 *  current scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::updateAdvanced( void ){
    std::cerr << which_advanced << std::endl;
    switch( which_advanced ){
        case 0:
            left = newLeft;
            right = newRight;
            bottom = newBottom;
            top = newTop;
            onear = newNear;
            ofar = newFar;
            break;
        case 1:
            fleft = newLeft;
            fright = newRight;
            fbottom = newBottom;
            ftop = newTop;
            fnear = newNear;
            ffar = newFar;
            break;
    }
    updateWorldProjections(  );
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Set the projection sliders when their radio button context has
 *  changed
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::setAdvancedSliders(){
    switch( which_advanced ){
        case 0:
            slider8->set_float_val( left );
            slider9->set_float_val( right );
            slider10->set_float_val( bottom );
            slider11->set_float_val( top );
            slider12->set_float_val( onear );
            slider13->set_float_val( ofar );
            break;
        case 1:
            slider8->set_float_val( fleft );
            slider9->set_float_val( fright );
            slider10->set_float_val( fbottom );
            slider11->set_float_val( ftop );
            slider12->set_float_val( fnear );
            slider13->set_float_val( ffar );
            break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Get the initial values from the current scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::getInitValues(){
    if( world != NULL && world->at( curSceneIndex ) != NULL ){
        float* vals = world->at( curSceneIndex )->getLookat();
        newX = eyeX = vals[0];
        newY = eyeY = vals[1];
        newZ = eyeZ = vals[2];
        lookX = vals[3];
        lookY = vals[4];
        lookZ = vals[5];
        upX = vals[6];
        upY = vals[7];
        upZ = vals[8];

        vals = world->at( curSceneIndex )->getPerspective();
        viewAngle = vals[0];
        aspectRatio = vals[1];
        near = vals[2];
        far = vals[3];
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Package up the current Ortho values into a float array
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float* ControlPanel::packageOrtho( ){
    float* toRet = new float[6];
    toRet[0] = left;
    toRet[1] = right;
    toRet[2] = bottom;
    toRet[3] = top;
    toRet[4] = onear;
    toRet[5] = ofar;
    return toRet;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Package up the current Frustum values into a float array
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
float* ControlPanel::packageFrustum( ){
    float* toRet = new float[6];
    toRet[0] = fleft;
    toRet[1] = fright;
    toRet[2] = fbottom;
    toRet[3] = ftop;
    toRet[4] = fnear;
    toRet[5] = ffar;
    return toRet;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Update the current scene's projection values if their radio status
 *  corresponds to the values being set
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::updateWorldProjections( void ){
    switch( which_advanced ){
        case 0:
            if( world->at( curSceneIndex )->getParallelStatus() )
                world->at( curSceneIndex )->setOrtho( packageOrtho() );
            break;
        case 1:
            if( !world->at( curSceneIndex )->getParallelStatus() )
               world->at( curSceneIndex )->setFrustum(packageFrustum());
            break;
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Define the vector of Scenes we can walk through
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::setSceneWorld( std::vector<Scene*>* allScenes ){
    world = allScenes;

    curSceneIndex = -1;   // initialize to no scene index
    curScene = NULL;
    std::cerr << "World Size: " << world->size() << std::endl;
    if ( world->size() > 0 ){
        nextScene();
    }
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Reset the value of the sliders between scene changes
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::resetSliders(){
    which_lookat = which_advanced = 0;
    which_projection = 1;
    newX = newY = newZ = viewAngle = aspectRatio = near = far =
        newLeft = newRight = newBottom = newTop = newNear =
        newFar = 0.0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Setup next scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::nextScene(){
    curSceneIndex++;
    if ( curSceneIndex >= (int)world->size() )
        curSceneIndex = 0;   // wraparound
    std::cerr << "Next scene " << curSceneIndex << "\n";

    resetSliders();
    glui->sync_live();
    curScene = world->at( curSceneIndex );
    // std::cerr << curScene->getDescription() << std::endl;
    scene_description->set_text(curScene->getDescription());
    redraw();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Setup previous scene
 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void ControlPanel::prevScene(){
    curSceneIndex--;
    if ( curSceneIndex < 0 )
        curSceneIndex = (int)world->size() - 1;   // wraparound
    std::cerr << "Prev scene " << curSceneIndex << "\n";

    resetSliders();
    glui->sync_live();
    curScene = world->at( curSceneIndex );
    scene_description->set_text(curScene->getDescription());
    redraw();
}

//------------------ public class methods --------------------------
/** Return the singleton instance.  If it does not exist, create one.
 */
ControlPanel *ControlPanel::getInstance(){
    if ( !instance )
        instance = new ControlPanel();
    return instance;
}

//---------------------------------------------------------------------
/** Pass control to the class's controlChanged method
 */
void ControlPanel::controlChanged_cb( int control_enum_value ){
    getInstance()->controlChanged( control_enum_value );
}
//---------------------------------------------------------------------
/**
 *  Static call method; just passes control to the class's redraw method
 */
void ControlPanel::redraw_cb(){
    getInstance()->redraw();
}

//---------------------------------------------------------------------
/** Pass control to the class's controlChanged method
 */
void ControlPanel::redraw(){
    if ( curScene != NULL )
        curScene->redraw();
}

//-------------------- protected methods -----------------------------
void ControlPanel::controlChanged( int control_enum_value ){
    switch ( control_enum_value ){
        case LIGHTING_CHECKBOX:
            if( !lighting ){
                glDisable( GL_LIGHT0 );
                glDisable( GL_LIGHT1 );
            }
            else{
                glEnable( GL_LIGHT0 );
                glEnable( GL_LIGHT1 );
            }
            break;
        case DRAWAXES_CHECKBOX:
            curScene->setDrawAxes( drawAxes );
            break;
        case PREVSCENE_BUTTON:
            prevScene();
            break;
        case NEXTSCENE_BUTTON:
            nextScene();
            break;
        case QUIT_BUTTON:
            exit( 0 );
            break;
        case SET_PROJECTION:
            if( which_projection == 0 )
                world->at( curSceneIndex )->setParallelStatus( true );
            else
                world->at( curSceneIndex )->setParallelStatus( false );
        case LOOKAT:
            updateWorldWithSlider();
            break;
        case PERSPECTIVE:
            world->at( curSceneIndex )->setPerspective( viewAngle,
                                                        aspectRatio,
                                                        near, far );
            break;
        case SET_LOOKAT:
            setLookAtSliders(  );
            break;
        case SET_LIGHT:
            break;
        case COLOR:
            world->at( curSceneIndex )->setLightColor(which_light, newR, newG, newB);
            break;
    }
}
