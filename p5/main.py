#!/usr/bin/env python
"""
Maintains the main window for the app and handles building all of the menus and 
scenes
"""
import wx
from OpenGL.GLUT import *
from demos import Demo1, Demo2, Demo3, Demo4, Demo5, P5
#----------------------------------------------------------------------
# There are better ways to do IDs, but this demo requires that the window
# IDs be in a specific range. There are better ways to do that, too, but
# this will do for purposes of this demo.
# Window edge labels
ID_WINDOW_TOP   = 5000
ID_WINDOW_LEFT  = 5001
ID_WINDOW_MIDD  = 5002
ID_WINDOW_RIGHT = 5003
# File menu button labels
ID_Menu_Exit = 5005
# Button labels
DEMO1_BUTTOM = 5006
DEMO2_BUTTOM = 5007
DEMO3_BUTTOM = 5008
DEMO4_BUTTOM = 5009
DEMO5_BUTTOM = 5010
P5_BUTTOM    = 5011
# GUI Elements
LIGHTING   = 6000
X_SLIDER   = 6001
Y_SLIDER   = 6002
NEXT_SCENE = 6003
PREV_SCENE = 6004
RED_LIGHT  = 6005
AXES_BUTTN = 6006
PROJECTION_TYPE = 6007
LOOK_AT_CONTROL = 6008
LOOK_AT_SLIDE_X = 6009
LOOK_AT_SLIDE_Y = 6010
LOOK_AT_SLIDE_Z = 6011
PERSPECTIVE_ANGLE = 6012
PERSPECTIVE_RATIO = 6013
PERSPECTIVE_NEAR  = 6014
PERSPECTIVE_FAR   = 6015
BOX_BUTTON    = 7001
CLOWN_BUTTON  = 7002
DONUT_BUTTON  = 7003
EYE_BUTTON    = 7004
HEAD_BUTTON   = 7005
SNOW_BUTTON   = 7006
SPHERE_BUTTON = 7007
#----------------------------------------------------------------------
class MyParentFrame(wx.MDIParentFrame):
    """
    The main frame for the app
    """
    def __init__(self):
        wx.MDIParentFrame.__init__(self, None, -1, '770W P5 (Final Version)', size=(1000,700),
                        style=wx.DEFAULT_FRAME_STYLE | wx.HSCROLL | wx.VSCROLL)

        self.winCount = 0
        menu = wx.Menu()
        menu.Append(ID_Menu_Exit, 'Exit')

        menubar = wx.MenuBar()
        menubar.Append(menu, 'File')
        self.SetMenuBar(menubar)

        self.Bind(wx.EVT_MENU, self.OnExit, id=ID_Menu_Exit)

        self.Bind(wx.EVT_SIZE, self.OnSize)

        # A window to the left of the client window
        win = wx.SashLayoutWindow(self, ID_WINDOW_LEFT, style=wx.NO_BORDER|wx.SW_3D)
        win.SetDefaultSize((120, 100))
        win.SetOrientation(wx.LAYOUT_VERTICAL)
        win.SetAlignment(wx.LAYOUT_LEFT)
        win.SetBackgroundColour(wx.Colour(0, 255, 0))
        win.SetExtraBorderSize(10)

        sizer = wx.FlexGridSizer(cols=1, hgap=20, vgap=20)

        b = wx.Button(win, DEMO1_BUTTOM, 'Demo1', (10,10))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        sizer.Add(b)

        b = wx.Button(win, DEMO2_BUTTOM, 'Demo2', (10,50))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        sizer.Add(b)

        b = wx.Button(win, DEMO3_BUTTOM, 'Demo3', (10,90))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        sizer.Add(b)

        b = wx.Button(win, DEMO4_BUTTOM, 'Demo4', (10, 130))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        sizer.Add(b)

        b = wx.Button(win, DEMO5_BUTTOM, 'Demo5', (10, 170))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        sizer.Add(b)

        b = wx.Button(win, P5_BUTTOM, 'p5', (10,210))
        self.Bind(wx.EVT_BUTTON, self.OnButton, b)
        # b.Enable(False)
        sizer.Add(b)

        border = wx.BoxSizer(wx.VERTICAL)
        border.Add(sizer, 0, wx.ALL, 25)
        self.SetSizer(border)

        self.leftWindow1 = sizer

        self.win2 = wx.SashLayoutWindow(self, ID_WINDOW_MIDD, style=wx.NO_BORDER|wx.SW_3D)
        self.win2.SetDefaultSize((200, 1000))
        self.win2.SetOrientation(wx.LAYOUT_VERTICAL)
        self.win2.SetAlignment(wx.LAYOUT_LEFT)
        self.win2.SetBackgroundColour(wx.Colour(0, 255, 255))

        self.midWindow = self.win2

        self.win3 = wx.SashLayoutWindow(self, ID_WINDOW_RIGHT, style=wx.NO_BORDER|wx.SW_3D)
        self.windowRight = None
        self.OnButton(DEMO1_BUTTOM)

        self.SetAutoLayout(True)
        win.Show(True)

    def lights_on_off(self, event):
        """
        Toggle the lighting in the scene being on or off
        """
        self.windowRight.flicker_lights()

    def set_x_loc(self, event):
        """
        Set the x location of the most recent element in the scene
        """
        self.windowRight.set_x(event.Int)

    def set_y_loc(self, event):
        """
        Set the y location of the most recent element in the scene
        """
        self.windowRight.set_y(event.Int)

    def demo3_controls(self, win, x, y):
        """
        Build the menu for Demo3 in the specified window and at the specified
        location
        @param win: the window for the controls to be added to
        @param x: the x location for this menu to be added at
        @param y: the y location for this menu to be added at
        """
        sizer = wx.FlexGridSizer(cols=1, hgap=20, vgap=20)
        win.SetDefaultSize((200, 1000))
        win.SetOrientation(wx.LAYOUT_VERTICAL)
        win.SetAlignment(wx.LAYOUT_LEFT)
        win.SetBackgroundColour(wx.Colour(0, 255, 255))

        lights = wx.CheckBox(win, id=LIGHTING, label='Lighting', pos=(10, 15))
        lights.SetValue(True)
        self.Bind(wx.EVT_CHECKBOX, self.lights_on_off, id=LIGHTING)
        sizer.Add(lights)
        quit_b = wx.Button(win, id=ID_Menu_Exit, label='Quit', pos=(10,50))
        self.Bind(wx.EVT_BUTTON, self.OnExit, id=ID_Menu_Exit)
        sizer.Add(quit_b)
        wx.StaticText(win, id=-1, label='X Location', pos=(10, 90))
        x_slider = wx.Slider(win, id=X_SLIDER, pos=(10, 100), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        x_slider.SetMax(800)
        x_slider.SetMin(-100)
        x_slider.SetValue(300)
        self.Bind(wx.EVT_SLIDER, self.set_x_loc, id=X_SLIDER)
        sizer.Add(x_slider)
        wx.StaticText(win, id=-1, label='Y Location', pos=(10, 145))
        y_slider = wx.Slider(win, id=Y_SLIDER, pos=(10, 155), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        y_slider.SetMax(800)
        y_slider.SetMin(-100)
        y_slider.SetValue(50)
        self.Bind(wx.EVT_SLIDER, self.set_y_loc, id=Y_SLIDER)
        sizer.Add(y_slider)
        border = wx.BoxSizer(wx.VERTICAL)
        border.Add(sizer, 0, wx.ALL, 25)
        return win

    def demo4_controls(self, win, x, y):
        """
        Build the menu for Demo4 in the specified window and at the specified
        location
        @param win: the window for the controls to be added to
        @param x: the x location for this menu to be added at
        @param y: the y location for this menu to be added at
        """
        sizer = wx.FlexGridSizer(cols=1, hgap=20, vgap=20)
        win.SetDefaultSize((200, 1000))
        win.SetOrientation(wx.LAYOUT_VERTICAL)
        win.SetAlignment(wx.LAYOUT_LEFT)
        win.SetBackgroundColour(wx.Colour(0, 255, 255))

        lights = wx.CheckBox(win, id=LIGHTING, label='Lighting', pos=(10, 15))
        lights.SetValue(True)
        self.Bind(wx.EVT_CHECKBOX, self.lights_on_off, id=LIGHTING)
        sizer.Add(lights)
        draw_axes = wx.CheckBox(win, id=AXES_BUTTN, label='Draw Axes', pos=(10, 50))
        draw_axes.SetValue(True)
        self.Bind(wx.EVT_CHECKBOX, self.set_draw_axes, id=AXES_BUTTN)
        sizer.Add(draw_axes)
        quit_b = wx.Button(win, id=ID_Menu_Exit, label='Quit', pos=(10,90))
        self.Bind(wx.EVT_BUTTON, self.OnExit, id=ID_Menu_Exit)
        sizer.Add(quit_b)
        next_b = wx.Button(win, id=NEXT_SCENE, label='Next Scene', pos=(10,130))
        self.Bind(wx.EVT_BUTTON, self.next_scene, id=NEXT_SCENE)
        sizer.Add(next_b)
        wx.StaticText(win, id=-1, label='Red Light', pos=(10, 170))
        red_slider = wx.Slider(win, id=RED_LIGHT, pos=(10, 180), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        red_slider.SetMax(255)
        red_slider.SetMin(0)
        red_slider.SetValue(0)
        self.Bind(wx.EVT_SLIDER, self.set_red_light, id=RED_LIGHT)
        sizer.Add(red_slider)
        border = wx.BoxSizer(wx.VERTICAL)
        border.Add(sizer, 0, wx.ALL, 25)
        return win

    def p5_controls(self, win, x, y):
        """
        Build the menu for P5 in the specified window and at the specified
        location
        @param win: the window for the controls to be added to
        @param x: the x location for this menu to be added at
        @param y: the y location for this menu to be added at
        """
        sizer = wx.FlexGridSizer(cols=1, hgap=20, vgap=20)
        win.SetDefaultSize((200, 1000))
        win.SetOrientation(wx.LAYOUT_VERTICAL)
        win.SetAlignment(wx.LAYOUT_LEFT)
        win.SetBackgroundColour(wx.Colour(0, 255, 255))

        lights = wx.CheckBox(win, id=LIGHTING, label='Lighting', pos=(25, 2))
        lights.SetValue(True)
        self.Bind(wx.EVT_CHECKBOX, self.lights_on_off, id=LIGHTING)
        sizer.Add(lights)

        draw_axes = wx.CheckBox(win, id=AXES_BUTTN, label='Draw Axes', pos=(105, 2))
        draw_axes.SetValue(True)
        self.Bind(wx.EVT_CHECKBOX, self.set_draw_axes, id=AXES_BUTTN)
        sizer.Add(draw_axes)

        quit_b = wx.Button(win, id=ID_Menu_Exit, label='Quit', pos=(50, 20))
        self.Bind(wx.EVT_BUTTON, self.OnExit, id=ID_Menu_Exit)
        sizer.Add(quit_b)

        prev_b = wx.Button(win, id=PREV_SCENE, label='Last Scene', pos=(3, 45))
        self.Bind(wx.EVT_BUTTON, self.prev_scene, id=PREV_SCENE)
        sizer.Add(prev_b)

        next_b = wx.Button(win, id=NEXT_SCENE, label='Next Scene', pos=(100, 45))
        self.Bind(wx.EVT_BUTTON, self.next_scene, id=NEXT_SCENE)
        sizer.Add(next_b)

        titles = ['Parallel', 'Perspective']
        radio_box = wx.RadioBox(win, id=PROJECTION_TYPE,
                                label='Projection Type', choices=titles,
                                majorDimension=1, pos=(10, 75))
        radio_box.SetSelection(1)
        self.Bind(wx.EVT_RADIOBOX, self.set_projection_type, radio_box)
        sizer.Add(radio_box)

        titles = ['Eye', 'Look At', 'Up']
        radio_box = wx.RadioBox(win, id=LOOK_AT_CONTROL,
                                label='Look At Controls', choices=titles,
                                majorDimension=1, pos=(10, 145))
        self.Bind(wx.EVT_RADIOBOX, self.set_look_at_type, radio_box)
        sizer.Add(radio_box)
        self.l_type = 'Eye'

        wx.StaticText(win, id=-1, label='X', pos=(10, 235))
        self.look_x_slider = wx.Slider(win, id=LOOK_AT_SLIDE_X, pos=(25, 224), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.look_x_slider.SetMax(255)
        self.look_x_slider.SetMin(0)
        self.look_x_slider.SetValue(10)
        self.Bind(wx.EVT_SLIDER, self.set_look_at_x, id=LOOK_AT_SLIDE_X)
        sizer.Add(self.look_x_slider)

        wx.StaticText(win, id=-1, label='Y', pos=(10, 270))
        self.look_y_slider = wx.Slider(win, id=LOOK_AT_SLIDE_Y, pos=(25, 258), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.look_y_slider.SetMax(255)
        self.look_y_slider.SetMin(0)
        self.look_y_slider.SetValue(3)
        self.Bind(wx.EVT_SLIDER, self.set_look_at_y, id=LOOK_AT_SLIDE_Y)
        sizer.Add(self.look_y_slider)

        wx.StaticText(win, id=-1, label='Z', pos=(10, 305))
        self.look_z_slider = wx.Slider(win, id=LOOK_AT_SLIDE_Z, pos=(25, 292), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.look_z_slider.SetMax(255)
        self.look_z_slider.SetMin(0)
        self.look_z_slider.SetValue(10)
        self.Bind(wx.EVT_SLIDER, self.set_look_at_z, id=LOOK_AT_SLIDE_Z)
        sizer.Add(self.look_z_slider)

        wx.StaticText(win, id=-1, label='Perspective Controls', pos=(10, 330))
        wx.StaticText(win, id=-1, label='View Angle', pos=(10, 345))
        self.angle_slider = wx.Slider(win, id=PERSPECTIVE_ANGLE, pos=(10, 355), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.angle_slider.SetMax(255)
        self.angle_slider.SetMin(0)
        self.angle_slider.SetValue(10)
        self.Bind(wx.EVT_SLIDER, self.set_angle, id=PERSPECTIVE_ANGLE)
        sizer.Add(self.angle_slider)

        wx.StaticText(win, id=-1, label='Aspect Ratio', pos=(10, 390))
        self.ratio_slider = wx.Slider(win, id=PERSPECTIVE_RATIO, pos=(10, 395), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.ratio_slider.SetMax(255)
        self.ratio_slider.SetMin(0)
        self.ratio_slider.SetValue(1.33)
        self.Bind(wx.EVT_SLIDER, self.set_ratio, id=PERSPECTIVE_RATIO)
        sizer.Add(self.ratio_slider)

        wx.StaticText(win, id=-1, label='Near', pos=(10, 435))
        self.near_slider = wx.Slider(win, id=PERSPECTIVE_NEAR, pos=(10, 440), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.near_slider.SetMax(255)
        self.near_slider.SetMin(0.1)
        self.near_slider.SetValue(0.1)
        self.Bind(wx.EVT_SLIDER, self.set_near, id=PERSPECTIVE_NEAR)
        sizer.Add(self.near_slider)

        wx.StaticText(win, id=-1, label='Far', pos=(10, 475))
        self.far_slider = wx.Slider(win, id=PERSPECTIVE_FAR, pos=(10, 480), style=wx.SL_HORIZONTAL|wx.SL_AUTOTICKS|wx.SL_LABELS)
        self.far_slider.SetMax(255)
        self.far_slider.SetMin(0)
        self.far_slider.SetValue(10.0)
        self.Bind(wx.EVT_SLIDER, self.set_far, id=PERSPECTIVE_FAR)
        sizer.Add(self.far_slider)

        box_b = wx.Button(win, id=BOX_BUTTON, label='Add Box', pos=(2, 520))
        self.Bind(wx.EVT_BUTTON, self.add_box, id=BOX_BUTTON)
        sizer.Add(box_b)

        clown_b = wx.Button(win, id=CLOWN_BUTTON, label='Add Clown', pos=(90, 520))
        self.Bind(wx.EVT_BUTTON, self.add_clown, id=CLOWN_BUTTON)
        sizer.Add(clown_b)

        donut_b = wx.Button(win, id=DONUT_BUTTON, label='Add Donut', pos=(2, 545))
        self.Bind(wx.EVT_BUTTON, self.add_donut, id=DONUT_BUTTON)
        sizer.Add(donut_b)

        eye_button = wx.Button(win, id=EYE_BUTTON, label='Add Eye', pos=(90, 545))
        self.Bind(wx.EVT_BUTTON, self.add_eye, id=EYE_BUTTON)
        sizer.Add(eye_button)

        head_button = wx.Button(win, id=HEAD_BUTTON, label='Add Head', pos=(2, 570))
        self.Bind(wx.EVT_BUTTON, self.add_head, id=HEAD_BUTTON)
        sizer.Add(head_button)

        sphere_button = wx.Button(win, id=SPHERE_BUTTON, label='Add Sphere', pos=(90, 570))
        self.Bind(wx.EVT_BUTTON, self.add_sphere, id=SPHERE_BUTTON)
        sizer.Add(sphere_button)

        snow_button = wx.Button(win, id=SNOW_BUTTON, label='Add Snowman', pos=(2, 595))
        self.Bind(wx.EVT_BUTTON, self.add_snowman, id=SNOW_BUTTON)
        sizer.Add(snow_button)

        border = wx.BoxSizer(wx.VERTICAL)
        border.Add(sizer, 0, wx.ALL, 25)
        return win

    def add_box(self, event):
        """
        Callback function for the Add Box button
        """
        print 'Add Box'
        self.windowRight.add_box()

    def add_clown(self, event):
        """
        Callback function for the Add Clown button
        """
        print 'Add Clown'
        self.windowRight.add_clown()

    def add_donut(self, event):
        """
        Callback function for the Add Donut button
        """
        print 'Add Donut'
        self.windowRight.add_donut()

    def add_eye(self, event):
        """
        Callback function for the Add Eye button
        """
        print 'Add Eye'
        self.windowRight.add_eye()

    def add_head(self, event):
        """
        Callback function for the Add Head button
        """
        print 'Add Head'
        self.windowRight.add_head()

    def add_sphere(self, event):
        """
        Callback function for the Add Sphere button
        """
        print 'Add Sphere'
        self.windowRight.add_sphere()

    def add_snowman(self, event):
        """
        Callback function for the Add Snowman button
        """
        print 'Add Snowman'
        self.windowRight.add_snowman()

    def set_projection_type(self, event):
        """
        Callback function for the set projection type radio buttons
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.String
        p_type = event.String
        self.windowRight.set_projection_type(p_type)

    def set_look_at_type(self, event):
        """
        Callback function for set lookat type radio buttons
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.String
        l_type = event.String
        self.l_type = l_type
        scene = self.windowRight.get_scene()
        if self.l_type == 'Eye':
            eye_x, eye_y, eye_z = scene.eye()
            self.look_x_slider.SetValue(eye_x)
            self.look_y_slider.SetValue(eye_y)
            self.look_z_slider.SetValue(eye_z)
        elif self.l_type == 'Look At':
            look_x, look_y, look_z = scene.look()
            self.look_x_slider.SetValue(look_x)
            self.look_y_slider.SetValue(look_y)
            self.look_z_slider.SetValue(look_z)
        else:
            up_x, up_y, up_z = scene.up()
            self.look_x_slider.SetValue(up_x)
            self.look_y_slider.SetValue(up_y)
            self.look_z_slider.SetValue(up_z)

    def set_look_at_x(self, event):
        """
        Callback function for changing the x value for the currently selected 
        parameter
        @param event: The current status of the event responsible for calling 
                      this method
        """
        new_x = event.Int
        print new_x
        if self.l_type == 'Eye':
            self.windowRight.set_look_at(eye_x=new_x)
        elif self.l_type == 'Look At':
            self.windowRight.set_look_at(look_x=new_x)
        else: # l_type == 'Up'
            self.windowRight.set_look_at(up_x=new_x)
        self.windowRight.redraw()

    def set_look_at_y(self, event):
        """
        Callback function for changing the y value for the currently selected 
        parameter
        @param event: The current status of the event responsible for calling 
                      this method
        """
        new_y = event.Int
        print new_y
        if self.l_type == 'Eye':
            self.windowRight.set_look_at(eye_y=new_y)
        elif self.l_type == 'Look At':
            self.windowRight.set_look_at(look_y=new_y)
        else: # l_type == 'Up'
            self.windowRight.set_look_at(up_y=new_y)
        self.windowRight.redraw()

    def set_look_at_z(self, event):
        """
        Callback function for changing the z value for the currently selected 
        parameter
        @param event: The current status of the event responsible for calling 
                      this method
        """
        new_z = event.Int
        print new_z
        if self.l_type == 'Eye':
            self.windowRight.set_look_at(eye_z=new_z)
        elif self.l_type == 'Look At':
            self.windowRight.set_look_at(look_z=new_z)
        else: # l_type == 'Up'
            self.windowRight.set_look_at(up_z=new_z)
        self.windowRight.redraw()

    def set_draw_axes(self, event):
        """
        Callback function for toggling the draw axes checkbox
        @param event: The current status of the event responsible for calling 
                      this method
        """
        self.windowRight.toggle_draw_axes()

    def set_angle(self, event):
        """
        Callback function for the set angle slider
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.Int
        self.windowRight.set_angle(event.Int)

    def set_ratio(self, event):
        """
        Callback function for the set ratio slider
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.Int
        self.windowRight.set_ratio(event.Int)

    def set_near(self, event):
        """
        Callback function for the set near slider
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.Int
        self.windowRight.set_near(event.Int)

    def set_far(self, event):
        """
        Callback function for the set far slider
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.Int
        self.windowRight.set_far(event.Int)

    def set_red_light(self, event):
        """
        Callback function for the set red light slider
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print event.Int
        self.windowRight.set_red_light(event.Int)

    def prev_scene(self, event):
        """
        Callback function for the previous scene button
        @param event: The current status of the event responsible for calling 
                      this method
        """
        self.windowRight.prev_scene()
        try:
            scene = self.windowRight.get_scene()
            if self.l_type == 'Eye':
                eye_x, eye_y, eye_z = scene.eye()
                self.look_x_slider.SetValue(eye_x)
                self.look_y_slider.SetValue(eye_y)
                self.look_z_slider.SetValue(eye_z)
            elif self.l_type == 'Look At':
                look_x, look_y, look_z = scene.look()
                self.look_x_slider.SetValue(look_x)
                self.look_y_slider.SetValue(look_y)
                self.look_z_slider.SetValue(look_z)
            else:
                up_x, up_y, up_z = scene.up()
                self.look_x_slider.SetValue(up_x)
                self.look_y_slider.SetValue(up_y)
                self.look_z_slider.SetValue(up_z)
            perspective = scene.perspective()
            self.angle_slider.SetValue(perspective[0])
            self.ratio_slider.SetValue(perspective[1])
            self.near_slider.SetValue(perspective[2])
            self.far_slider.SetValue(perspective[3])
        except Exception:
            pass

    def next_scene(self, event):
        """
        Callback function for the next scene button
        @param event: The current status of the event responsible for calling 
                      this method
        """
        self.windowRight.next_scene()
        try:
            scene = self.windowRight.get_scene()
            if self.l_type == 'Eye':
                eye_x, eye_y, eye_z = scene.eye()
                self.look_x_slider.SetValue(eye_x)
                self.look_y_slider.SetValue(eye_y)
                self.look_z_slider.SetValue(eye_z)
            elif self.l_type == 'Look At':
                look_x, look_y, look_z = scene.look()
                self.look_x_slider.SetValue(look_x)
                self.look_y_slider.SetValue(look_y)
                self.look_z_slider.SetValue(look_z)
            else:
                up_x, up_y, up_z = scene.up()
                self.look_x_slider.SetValue(up_x)
                self.look_y_slider.SetValue(up_y)
                self.look_z_slider.SetValue(up_z)
            perspective = scene.perspective()
            self.angle_slider.SetValue(perspective[0])
            self.ratio_slider.SetValue(perspective[1])
            self.near_slider.SetValue(perspective[2])
            self.far_slider.SetValue(perspective[3])
        except Exception:
            pass

    def OnButton(self, event):
        """
        Callback function for demo buttons
        @param event: The current status of the event responsible for calling 
                      this method
        """
        try:
            event_id = event.GetId()
        except AttributeError:
            event_id = event
        print 'Button %d Clicked' % event_id
        if event_id == DEMO1_BUTTOM:
            print '\tDemo1'
            self.midWindow.DestroyChildren()
            self.windowRight = Demo1(self.win3)
            self.windowRight.SetSizeWH(800, 700)
        elif event_id == DEMO2_BUTTOM:
            print '\tDemo2'
            self.midWindow.DestroyChildren()
            self.windowRight = Demo2(self.win3)
            self.windowRight.SetSizeWH(800, 700)
        elif event_id == DEMO3_BUTTOM:
            print '\tDemo3'
            self.midWindow.DestroyChildren()
            self.windowRight = Demo3(self.win3)
            self.midWindow = self.demo3_controls(self.win2, 0, 0)
            self.windowRight.SetSizeWH(800, 700)
        elif event_id == DEMO4_BUTTOM:
            print '\tDemo4'
            self.midWindow.DestroyChildren()
            self.windowRight = Demo4(self.win3)
            self.midWindow = self.demo4_controls(self.win2, 0, 0)
            self.windowRight.SetSizeWH(800, 700)
        elif event_id == DEMO5_BUTTOM:
            print '\tDemo5'
            self.midWindow.DestroyChildren()
            self.windowRight = Demo5(self.win3)
            self.windowRight.SetSizeWH(800, 700)
        elif event_id == P5_BUTTOM:
            print '\tP5'
            self.midWindow.DestroyChildren()
            self.windowRight = P5(self.win3)
            self.midWindow = self.p5_controls(self.win2, 0, 0)
            self.windowRight.SetSizeWH(800, 700)
        else:
            print 'ERROR: Invalid Button Input Received'

    def OnSize(self, event):
        """
        Callback function for handing window resizing
        @param event: The current status of the event responsible for calling 
                      this method
        """
        wx.LayoutAlgorithm().LayoutFrame(self)

    def OnExit(self, evt):
        """
        General Callback function for exiting the app
        @param event: The current status of the event responsible for calling 
                      this method
        """
        print 'Exiting...'
        self.Close(True)

if __name__ == '__main__':
    class MyApp(wx.App):
        def OnInit(self):
            frame = MyParentFrame()
            frame.Show(True)
            self.SetTopWindow(frame)
            return True

    app = MyApp(False)
    app.MainLoop()
