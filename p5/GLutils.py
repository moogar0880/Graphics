import OpenGL
# OpenGL.ERROR_CHECKING = False
from OpenGL.GL import *
from OpenGL.GLU import *
import os
import wx

class Color(object):
    '''docstring for Color'''
    def __init__(self, r=0.0, g=0.0, b=0.0, a=1.0):
        super(Color, self).__init__()
        self.red = r
        self.green = g
        self.blue = b
        self.alpha = a

class Scene(object):
    '''docstring for Scene'''
    def __init__(self):
        super(Scene, self).__init__()
        self.shapes = []
        self.rubberbanding = False
        self.rbX = self.rbY = 0

    def addShape(self, newShape=None):
        if newShape != None:
            self.shapes.append(newShape)

    def clear(self):
        self.shapes = []

    def redraw(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        for shape in self.shapes:
            shape.redraw()
        glFlush()

    def set_x_loc(self, x):
        if self.shapes != []:
            self.shapes[-1].setLocation(x, self.shapes[-1].getY())

    def set_y_loc(self, y):
        if self.shapes != []:
            self.shapes[-1].setLocation(self.shapes[-1].getX(), y)

    def set_location(self, x, y):
        self.shapes[-1].setLocation(x, y)
        self.redraw()

    def get_location(self):
        shape = self.shapes[0]
        return (shape.getX(), shape.getY())

class Scene3D(object):
    """docstring for Scene3D"""
    def __init__(self):
        super(Scene3D, self).__init__()
        self.shapes = []
        self.parallel = False
        self.right = self.fright = self.top = self.ftop = self.ofar = 1.0
        self.left = self.bottom = self.onear = self.fleft = 0.0
        self.fleft = self.fbottom = -1.0
        self.fnear = 1.5
        self.ffar = 20.0
        self.init = False
        self.reset_view()

    def add_object(self, obj):
        self.shapes.append(obj)

    def clear(self):
        self.shapes = []
        self.redraw()

    def reset_view(self):
        # self.set_look_at(10, 3, 10, 0, 0, 0, 0, 1, 0)
        self.set_look_at(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
        self.set_perspective(10, 1.33, 0.1, 100.0)
        self.init = True

    def set_look_at(self, eye_x, eye_y, eye_z, look_x, look_y, look_z, up_x,
                    up_y, up_z):
        self.eye_x  = eye_x
        self.eye_y  = eye_y
        self.eye_z  = eye_z
        self.look_x = look_x
        self.look_y = look_y
        self.look_z = look_z
        self.up_x   = up_x
        self.up_y   = up_y
        self.up_z   = up_z

    def look_at(self):
        return (self.eye_x, self.eye_y, self.eye_z, self.look_x, self.look_y,
                self.look_z, self.up_x, self.up_y, self.up_z)

    def set_perspective(self, angle, ratio, near, far):
        self.view_angle = float(angle)
        self.aspect_ratio = ratio
        self.near = near
        self.far = far

    def eye(self):
        return self.eye_x, self.eye_y, self.eye_z

    def look(self):
        return self.look_x, self.look_y, self.look_z

    def up(self):
        return self.up_x, self.up_y, self.up_z

    def perspective(self):
        return self.view_angle, self.aspect_ratio, self.near, self.far

    def redraw(self):
        # print self.shapes
        for shape in self.shapes:
            shape.redraw()
        glFlush()

    def set_ortho(self, left, right, bottom, top, near, far):
        self.left = left
        self.right = right
        self.bottom = bottom
        self.top = top
        self.near = near
        self.far = far

    def ortho(self):
        return self.left, self.right, self.bottom, self.top, self.near, self.far

    def set_frustum(self, left, right, bottom, top, near, far):
        self.fleft = left
        self.fright = right
        self.fbottom = bottom
        self.ftop = top
        self.fnear = near
        self.ffar = far

    def frustum(self):
        return self.fleft, self.fright, self.fbottom, self.ftop, self.fnear, self.ffar

    def set_draw_axes(self, yesno):
        self.draw_axes = yesno

    def set_projection_type(self, p_type=True):
        self.parallel = p_type

    def projection_type(self):
        return self.parallel

class Texture(wx.Image):
    """docstring for Texture"""
    def __init__(self, image='Sunrise.jpg'):
        self.texture_id = glGenTextures()
        wx.Image.__init__(self, image)

    def enable(self):
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, self.texture_id )

    def disable(self):
        glDisable( GL_TEXTURE_2D )
