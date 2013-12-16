import OpenGL
# OpenGL.ERROR_CHECKING = False
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from shapes import Triangle, Box, Sphere, Cone, Donut, Eye, Hat, Head, \
                   Snowman, Clown
from GLutils import Color, Scene, Scene3D, Texture
import os
import argparse
import wx
from wx import glcanvas, Panel

ID_WINDOW_MIDD = 5002

WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

class MyCanvasBase(glcanvas.GLCanvas):
    """
    Base class for all OpenGL scenes to be drawn on
    """
    def __init__(self, parent):
        glcanvas.GLCanvas.__init__(self, parent, -1)
        self.init = False
        self.context = glcanvas.GLContext(self)

        # initial mouse position
        self.lastx = self.x = 30
        self.lasty = self.y = 30
        self.size = None
        self.Bind(wx.EVT_ERASE_BACKGROUND, self.OnEraseBackground)
        self.Bind(wx.EVT_SIZE, self.OnSize)
        self.Bind(wx.EVT_PAINT, self.OnPaint)
        self.Bind(wx.EVT_LEFT_DOWN, self.OnMouseDown)
        self.Bind(wx.EVT_LEFT_UP, self.OnMouseUp)
        self.Bind(wx.EVT_MOTION, self.OnMouseMotion)

    def OnEraseBackground(self, event):
        pass # Do nothing, to avoid flashing on MSW.

    def OnSize(self, event):
        wx.CallAfter(self.DoSetViewport)
        event.Skip()

    def DoSetViewport(self):
        size = self.size = self.GetClientSize()
        self.SetCurrent(self.context)
        glViewport(0, 0, size.width, size.height)

    def OnPaint(self, event):
        dc = wx.PaintDC(self)
        self.SetCurrent(self.context)
        if not self.init:
            self.appInit()
            self.init = True
        self.redraw()

    def OnMouseDown(self, evt):
        self.CaptureMouse()
        self.x, self.y = self.lastx, self.lasty = evt.GetPosition()

    def OnMouseUp(self, evt):
        self.ReleaseMouse()

    def OnMouseMotion(self, evt):
        if evt.Dragging() and evt.LeftIsDown():
            self.lastx, self.lasty = self.x, self.y
            self.x, self.y = evt.GetPosition()
            self.Refresh(False)

class Demo1(MyCanvasBase):
    """
    PyOpenGL demo for Demo1
    """
    def appInit(self):
        self.shapes = []
        # set viewing projection
        glClearColor(1.0, 1.0, 1.0, 0.0)
        glColor(0.0, 0.0, 0.0)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT)

        tri = Triangle()
        tri.set_location(10, 50)
        tri.set_color(0, 1, 1)
        self.shapes.append(tri)

        tri = Triangle()
        tri.set_location(70, 50)
        tri.set_color(1, 0, 1)
        tri.set_size(2, 2)
        self.shapes.append(tri)

        tri = Triangle()
        tri.set_location(300, 50)
        self.shapes.append(tri)

    def redraw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        for shape in self.shapes:
            shape.redraw()
        glFlush()
        self.SwapBuffers()

class Demo2(MyCanvasBase):
    """
    PyOpenGL demo for Demo2
    """
    def appInit(self):
        self.shapes = []
        glClearColor(1.0, 1.0, 1.0, 1.0)
        glColor(0.0, 0.0, 0.0)
        # glPointSize(4.0)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT)

        tri = Triangle()
        tri.set_location(10, 50)
        tri.set_color(0, 1, 1)
        self.shapes.append(tri)

        tri = Triangle()
        tri.set_location(70, 50)
        tri.set_color(1, 0, 1)
        tri.set_size(2, 2)
        self.shapes.append(tri)

        tri = Triangle()
        tri.set_location(300, 50)
        self.shapes.append(tri)

        self.Bind(wx.EVT_CONTEXT_MENU, self.OnContextMenu)

    def redraw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        for shape in self.shapes:
            shape.redraw()
        glFlush()
        self.SwapBuffers()

    def OnContextMenu(self, event):
        print 'OnContextMenu\n'

        # only do this part the first time so the events are only bound once
        #
        # Yet another anternate way to do IDs. Some prefer them up top to
        # avoid clutter, some prefer them close to the object of interest
        # for clarity.
        if not hasattr(self, 'popupID1'):
            self.popupID1 = wx.NewId()
            self.popupID2 = wx.NewId()
            self.popupID3 = wx.NewId()

            self.Bind(wx.EVT_MENU, self.clear_scene, id=self.popupID1)
            self.Bind(wx.EVT_MENU, self.redraw_menu, id=self.popupID2)
            self.Bind(wx.EVT_MENU, self.exit_menu, id=self.popupID3)

        # make a menu
        menu = wx.Menu()
        menu.Append(self.popupID1, 'Clear')
        menu.Append(self.popupID2, 'Redraw')
        menu.Append(self.popupID3, 'Exit')

        # Popup the menu.  If an item is selected then its handler
        # will be called before PopupMenu returns.
        self.PopupMenu(menu)
        menu.Destroy()

    def clear_scene(self, event):
        self.shapes = []
        self.redraw()

    def redraw_menu(self, event):
        self.appInit()
        self.redraw()

    def exit_menu(self, event):
        exit()

class Demo3(MyCanvasBase):
    """
    PyOpenGL demo for Demo3
    """
    def appInit(self):
        glClearColor(1.0, 1.0, 1.0, 1.0)
        glColor(0.0, 0.0, 0.0)
        glPointSize(4.0)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT)

        self.scene = Scene()

        tri = Triangle()
        tri.set_location(10, 50)
        tri.set_color(0, 1, 1)
        self.scene.addShape(tri)

        tri = Triangle()
        tri.set_location(70, 50)
        tri.set_color(1, 0, 1)
        tri.set_size(2, 2)
        self.scene.addShape(tri)

        tri = Triangle()
        tri.set_location(300, 50)
        self.scene.addShape(tri)

    def redraw(self):
        self.scene.redraw()
        self.SwapBuffers()

    def set_x(self, x):
        self.scene.set_x_loc(x)
        self.redraw()

    def set_y(self, y):
        self.scene.set_y_loc(y)
        self.redraw()

    def set_location(self, x, y):
        self.scene.set_location(x, y)
        self.redraw()

    def get_location(self):
        self.scene.get_location()

    def flicker_lights(self):
        print 'Lights Set'

class Demo4(MyCanvasBase):
    """
    PyOpenGL demo for Demo4
    """
    def __init__(self, parent):
        super(Demo4, self).__init__(parent)
        self.scenes = []
        self.draw_axes = True
        self.lighting = True
        self.current_scene = 0
        self.objects = []
        self.diffuse_light = [0.8, 0.8, 0.8, 1]

    def next_scene(self):
        if self.current_scene == len(self.scenes) - 1:
            self.current_scene = 0
        else:
            self.current_scene += 1
        self.redraw()

    def make_box(self, scale, color):
        box = Box()
        box.set_color(c=color)
        box.set_location(0, 0, 0)
        box.set_size(scale, scale, scale)
        return box

    def make_ball(self, scale, color):
        sphere = Sphere()
        sphere.set_location(0, 0, 0)
        sphere.set_size(scale, scale, scale)
        sphere.set_color(c=color)
        return sphere

    def make_simple_scenes(self):
        box1 = self.make_box(1, Color(1, 0, 1))
        self.objects.append(box1)

        box1Scene = Scene3D()
        box1Scene.add_object(box1)
        self.scenes.append(box1Scene)

        box2 = self.make_box(0.25, Color(0, 1, 1))
        box2.set_rotate(45, 0, 0, 1)
        self.objects.append(box2)

        box2Scene = Scene3D()
        box2Scene.add_object(box2)
        self.scenes.append(box2Scene)

        sp = self.make_ball(0.5, Color(0.8, 0.8, 0))
        self.objects.append(sp)

        ballScene = Scene3D()
        ballScene.add_object(sp)
        self.scenes.append(ballScene)

    def make_multi_object_scene(self):
        multi1 = Scene3D()
        box = self.objects[0]
        box.set_location(1, 0, 0)
        box.set_size(0.4, 0.4, 0.1)
        multi1.add_object(box)

        box = self.objects[1]
        box.set_location(-1, 0, 0)
        multi1.add_object(box)

        self.scenes.append(multi1)

    def draw_coordinate_axes(self):
        glDisable(GL_LIGHTING)
        scale = 1.8
        glPushMatrix()

        glScalef(scale, scale, scale)
        origin = [0, 0, 0]

        xaxis = [1, 0, 0]
        yaxis = [0, 1, 0]
        zaxis = [0, 0, 1]

        glLineWidth(3.0)

        glBegin(GL_LINES)
        glColor3f(1, 0, 0)
        glVertex3fv(origin)
        glVertex3fv(xaxis)
        glColor3f(0, 1, 0)
        glVertex3fv(origin)
        glVertex3fv(yaxis)
        glColor3f(0, 0, 1)
        glVertex3fv(origin)
        glVertex3fv(zaxis)
        glEnd()
        glPopMatrix()
        glEnable(GL_LIGHTING)

    def set_lighting(self):
        lightPosition = [-1, 1, 1, 0]
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition)

        ambientLight = [0.1, 0.1, 0.1, 1]

        if self.lighting:
            glEnable(GL_LIGHTING)
            glEnable(GL_LIGHT0)
            glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight)
            glLightfv(GL_LIGHT0, GL_DIFFUSE, self.diffuse_light)
        else:
            glDisable(GL_LIGHTING)
            glDisable(GL_LIGHT0)

    def appInit(self):
        glMatrixMode( GL_PROJECTION )
        glLoadIdentity()
        glMatrixMode( GL_MODELVIEW )
        glLoadIdentity()

        glClearColor(0.0, 0.0, 0.0, 0.0)
        glClearDepth(1.0)
        glEnable( GL_DEPTH_TEST )
        glShadeModel( GL_SMOOTH )
        glEnable( GL_NORMALIZE )
        glEnable( GL_COLOR_MATERIAL )

        self.set_lighting()
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH)
        self.make_simple_scenes()
        self.make_multi_object_scene()

    def toggle_draw_axes(self):
        if self.draw_axes:
            self.draw_axes = False
        else:
            self.draw_axes = True
        self.redraw()

    def flicker_lights(self):
        print 'Lights Set HUR'
        if self.lighting:
            self.lighting = False
        else:
            self.lighting = True
        self.redraw()

    def set_red_light(self, value):
        self.diffuse_light[0] = value
        self.redraw()

    def redraw(self):
        self.appInit()
        scene = self.scenes[self.current_scene]
        angle, ratio, near, far = scene.perspective()
        print angle, ratio, near, far
        eye_x, eye_y, eye_z, look_x, look_y, look_z, up_x, up_y, up_z = scene.look_at()
        print eye_x, eye_y, eye_z, look_x, look_y, look_z, up_x, up_y, up_z

        glMatrixMode(GL_PROJECTION)
        gluPerspective(angle, ratio, near, far)
        glMatrixMode(GL_MODELVIEW)
        gluLookAt(eye_x, eye_y, eye_z, look_x, look_y, look_z, up_x, up_y, up_z)

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)

        if self.draw_axes:
            self.draw_coordinate_axes()

        scene.redraw()
        self.SwapBuffers()

class Demo5(MyCanvasBase):
    """
    PyOpenGL demo for Demo5
    """
    def __init__(self, parent):
        super(Demo5, self).__init__(parent)
        self.angle = 0.0
        self.replication = 1.0
        self.offset = 0.0
        self.deltaRep = 1
        self.revolution = 0
        self.stepsPer90 = 180
        self.stepsLeft = self.stepsPer90
        self.deltaAng = 90.0
        self.deltaOff = 0.15
        self.spin = True
        self.x2yAspect = 1.0
        self.texture = None

    def appInit(self):
        glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH )

        glClearColor(0.4, 0.4, 0.5, 1.0)
        glShadeModel(GL_SMOOTH)

        glEnable(GL_DEPTH_TEST)

        glEnable(GL_BLEND)
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)

        self.texture = Texture()
        self.texture.load_jpeg('Sunrise.jpg')
        self.x2yAspect = self.texture.GetWidth()/self.texture.GetHeight()
        glutReshapeFunc(self.reshape)
        glutDisplayFunc(self.redraw)

    def reshape(self, w, h):
        glViewport(0, 0, w, h)

        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(40.0, w/h, 1.0, 1000.0)
        glutPostRedisplay()

    def update_spin(self):
        if self.spin:
            self.angle += self.deltaAng
            self.stepsLeft -= 1
            if self.stepsLeft == 0:
                self.replication += self.deltaRep
                if self.revolution % 2 == 0:
                    self.offset += self.deltaOff
                self.stepsLeft = self.stepsPer90

            if self.angle >= 360.0:
                self.revolution += 1
                self.angle = 0
                self.offset = 0
                self.deltaRep = -self.deltaRep
            glutPostRedisplay()

    def redraw(self):
        self.update_spin()
        glMatrixMode( GL_MODELVIEW )
        glLoadIdentity()

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )
        self.SetCurrent()
        texture_id = self.texture.texture_id
        width = self.texture.GetWidth()
        height = self.texture.GetHeight()

        glBindTexture(GL_TEXTURE_2D, texture_id)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT )
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT )
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR )
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR )
        # map the image data to the texture. note that if the input
        # type is GL_FLOAT, the values must be in the range [0..1]
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_LUMINANCE,
                     GL_UNSIGNED_BYTE, self.texture.GetData())
        self.texture.enable()

        glTranslatef( 0.0, 0.0, -5.0 )
        glRotatef( self.angle, 0, 1.0, 0 )
        yscale = 1.75
        xscale = yscale * self.x2yAspect

        glScalef( xscale, yscale, 2.0 )

        glBegin( GL_QUADS )
        # Lower left quad corner
        glTexCoord2f( self.offset, self.offset )
        glVertex3f(-1.0, -1.0, 0.0)

        # Lower right quad corner
        glTexCoord2f( self.replication + self.offset, self.offset )
        glVertex3f(1.0, -1.0, 0.0)

        # Upper right quad corner
        glTexCoord2f( self.replication + self.offset, self.replication + self.offset )
        glVertex3f(1.0, 1.0, 0.0)

        # Upper left quad corner
        glTexCoord2f( self.offset, self.replication + self.offset )
        glVertex3f(-1.0, 1.0, 0.0)
        glEnd()

        self.texture.disable()
        glutSwapBuffers()

class P5(MyCanvasBase):
    """
    PyOpenGL rendition of P2
    """
    def __init__(self, parent):
        super(P5, self).__init__(parent)
        self.shapes = []
        self.scenes = []
        self.current_scene = 0
        self.objects = []
        self.lighting = True
        self.draw_axes = True

    def next_scene(self):
        if self.current_scene == len(self.scenes) - 1:
            self.current_scene = 0
        else:
            self.current_scene += 1
        print 'Scene: {}'.format(self.current_scene)
        self.redraw()

    def prev_scene(self):
        if self.current_scene == 0:
            self.current_scene = len(self.scenes) - 1
        else:
            self.current_scene -= 1
        print 'Scene: {}'.format(self.current_scene)
        self.redraw()

    def make_box(self, scale, color):
        box = Box()
        box.set_color(c=color)
        box.set_location(0, 0, 0)
        box.set_size(scale, scale, scale)
        return box

    def make_ball(self, scale, color):
        sphere = Sphere()
        sphere.set_location(0, 0, 0)
        sphere.set_size(scale, scale, scale)
        sphere.set_color(c=color)
        return sphere

    def make_simple_scenes(self):
        clown = Clown()
        clown.set_location( 0, 0, 0 )
        clown.set_size( 1, 1, 1 )
        self.objects.append( clown )

        clown1Scene = Scene3D()
        clown1Scene.add_object( clown )
        self.scenes.append( clown1Scene )

        head = Head()
        head.set_location( 0, 0, 0 )
        head.set_size( 1.5, 1.5, 1.5 )
        self.objects.append( head )

        headScene = Scene3D()
        headScene.add_object( head )
        self.scenes.append( headScene )

        hat = Hat()
        hat.set_location( 0, 0, 0 )
        hat.set_size( 1.5, 1.5, 1.5 )
        self.objects.append( hat )

        hat1Scene = Scene3D()
        hat1Scene.add_object( hat )
        self.scenes.append( hat1Scene )

        eye = Eye()
        eye.set_color(1, 0, 0)
        eye.set_location(0, 1, 1)
        eye.set_size(1.3, 1.3, 1.3)
        eye.set_rotate( 45, 1, 0, 0 )
        self.objects.append( eye )

        eye1Scene = Scene3D()
        eye1Scene.add_object( eye )
        self.scenes.append( eye1Scene )

        donut = Donut()
        donut.set_color(1, 0, 1 )
        donut.set_location( 0, 0, 0 )
        donut.set_size( 2.0, 2.0, 2.0 )
        donut.set_rotate( 45, 0, 1, 0)
        self.objects.append( donut )

        donut1Scene = Scene3D()
        donut1Scene.add_object( donut )
        self.scenes.append( donut1Scene )

        cone = Cone()
        cone.set_color( 1, 0, 1 )
        cone.set_location( 0, 0, 0 )
        cone.set_size( 2.0, 2.0, 2.0 )
        self.objects.append( cone )

        cone1Scene = Scene3D()
        cone1Scene.add_object( cone )
        self.scenes.append( cone1Scene )

        box1 = self.make_box(1, Color(1, 0, 1))
        self.objects.append( box1 )

        box1Scene = Scene3D()
        box1Scene.add_object( box1 )
        self.scenes.append( box1Scene )

        box2 = self.make_box( 1, Color(0, 1, 1 ))
        box2.set_rotate( 45, 0, 0, 1 )
        box2.set_size(2.0, 2.0, 2.0)
        self.objects.append( box2 )

        box2Scene = Scene3D()
        box2Scene.add_object( box2 )
        self.scenes.append( box2Scene )

        sp = self.make_ball(1, Color(0.8, 0.8, 0))
        sp.set_size(2.0, 2.0, 2.0)
        self.objects.append( sp )

        ballScene = Scene3D()
        ballScene.add_object( sp )
        self.scenes.append( ballScene )

    def make_multi_object_scene(self):
        multi1 = Scene3D()
        box = self.objects[0]
        box.set_location(1, 0, 0)
        box.set_size(0.4, 0.4, 0.1)
        multi1.add_object(box)

        box = self.objects[1]
        box.set_location(-1, 0, 0)
        multi1.add_object(box)

        self.scenes.append(multi1)

    def flicker_lights(self):
        print 'Lights Set HURPDURP'
        if self.lighting:
            self.lighting = False
        else:
            self.lighting = True
        self.redraw()

    def toggle_draw_axes(self):
        if self.draw_axes:
            self.draw_axes = False
        else:
            self.draw_axes = True
        self.redraw()

    def set_projection_type(self, p_type):
        self.scenes[self.current_scene].set_projection_type(p_type)

    def set_look_at(self, eye_x=None, eye_y=None, eye_z=None, look_x=None,
                    look_y=None, look_z=None, up_x=None, up_y=None, up_z=None):
        cur_look_at = self.scenes[self.current_scene].look_at()
        e_x = eye_x or cur_look_at[0]
        e_y = eye_y or cur_look_at[1]
        e_z = eye_z or cur_look_at[2]
        l_x = look_x or cur_look_at[3]
        l_y = look_y or cur_look_at[4]
        l_z = look_z or cur_look_at[5]
        u_x = up_x or cur_look_at[6]
        u_y = up_y or cur_look_at[7]
        u_z = up_z or cur_look_at[8]

        self.scenes[self.current_scene].set_look_at(e_x, e_y, e_z, l_x, l_y,
                                                    l_z, u_x, u_y, u_z)

    def appInit(self):
        glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH )
        glClearColor(0.0, 0.0, 0.0, 0.0)
        glClearDepth(1.0 )
        glEnable( GL_DEPTH_TEST )
        glShadeModel( GL_SMOOTH )
        glEnable( GL_NORMALIZE )
        glEnable( GL_COLOR_MATERIAL )

        glEnable( GL_LIGHTING )
        glEnable( GL_LIGHT0 )

        self.set_lighting()

        self.make_simple_scenes()
        self.make_multi_object_scene()

    def draw_coordinate_axes(self):
        scale = 5.0
        glPushMatrix()

        glScalef(scale, scale, scale)
        origin = [0, 0, 0]

        xaxis = [1, 0, 0]
        yaxis = [0, 1, 0]
        zaxis = [0, 0, 1]

        glLineWidth(3.0)

        glBegin(GL_LINES)
        glColor3f(1, 0, 0)
        glVertex3fv(origin)
        glVertex3fv(xaxis)
        glColor3f(0, 1, 0)
        glVertex3fv(origin)
        glVertex3fv(yaxis)
        glColor3f(0, 0, 1)
        glVertex3fv(origin)
        glVertex3fv(zaxis)
        glEnd()
        glPopMatrix()

    def set_lighting(self):
        lightPosition = [-1, 1, 1, 0]
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition)

        ambientLight = [1, 1, 0.4, 0.5]

        if self.lighting:
            glEnable(GL_LIGHTING)
            glEnable(GL_LIGHT0)
            glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight)
        else:
            glDisable(GL_LIGHTING)
            glDisable(GL_LIGHT0)

    def get_scene(self):
        return self.scenes[self.current_scene]

    def set_angle(self, value):
        scene = self.scenes[self.current_scene]
        scene.set_perspective(angle=value)
        angle, ratio, near, far = scene.perspective()
        self.redraw()

    def set_ratio(self, value):
        scene = self.scenes[self.current_scene]
        scene.set_perspective(ratio=value)
        self.redraw()

    def set_near(self, value):
        scene = self.scenes[self.current_scene]
        scene.set_perspective(near=value)
        self.redraw()

    def set_far(self, value):
        scene = self.scenes[self.current_scene]
        scene.set_perspective(far=value)
        self.redraw()

    def add_box(self):
        self.scenes[self.current_scene].add_object(Box())
        self.redraw()

    def add_clown(self):
        self.scenes[self.current_scene].add_object(Clown())
        self.redraw()

    def add_donut(self):
        self.scenes[self.current_scene].add_object(Donut())
        self.redraw()

    def add_eye(self):
        self.scenes[self.current_scene].add_object(Eye())
        self.redraw()

    def add_head(self):
        self.scenes[self.current_scene].add_object(Head())
        self.redraw()

    def add_sphere(self):
        self.scenes[self.current_scene].add_object(Sphere())
        self.redraw()

    def add_snowman(self):
        self.scenes[self.current_scene].add_object(Snowman())
        self.redraw()

    def redraw(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        scene = self.scenes[self.current_scene]
        parallel = scene.projection_type()
        angle, ratio, near, far = scene.perspective()
        # gluPerspective(angle, ratio, near, far)
        print angle, ratio, near, far
        if parallel:
            left, right, bottom, top, near, far = scene.ortho()
            glOrtho(left, right, bottom, top, near, far)
        else:
            left, right, bottom, top, near, far = scene.frustum()
            print left, right, bottom, top, near, far
            glFrustum(left, right, bottom, top, near, far)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        look_at = scene.look_at()

        print ';;', look_at[0], look_at[1], look_at[2], look_at[3], look_at[4], look_at[5], look_at[6], look_at[7], look_at[8]
        gluLookAt(look_at[0], look_at[1], look_at[2],
                  look_at[3], look_at[4], look_at[5],
                  look_at[6], look_at[7], look_at[8])
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT)
        if self.draw_axes:
            self.draw_coordinate_axes()
        scene.redraw()
        self.SwapBuffers()
        glFlush()
