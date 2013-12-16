import OpenGL
# OpenGL.ERROR_CHECKING = False
from OpenGL.GL import *
from OpenGL.GLU import *
import os
import wx

class Color(object):
    """
    RGBA Color object
    """
    def __init__(self, r=0.0, g=0.0, b=0.0, a=1.0):
        super(Color, self).__init__()
        self.red = r
        self.green = g
        self.blue = b
        self.alpha = a

class Scene(object):
    """
    A Scene capable of maintaining a collection of 2D objects
    """
    def __init__(self):
        super(Scene, self).__init__()
        self.shapes = []
        self.rubberbanding = False
        self.rbX = self.rbY = 0

    def addShape(self, new_shape=None):
        """
        Add a shape to this scene
        @param new_shape: New Shape to add to this scene
        """
        if new_shape != None:
            self.shapes.append(new_shape)

    def clear(self):
        """
        Clear all of the shapes from this scene
        """
        self.shapes = []

    def redraw(self):
        """
        Redraw all of the components of this scene
        """
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        for shape in self.shapes:
            shape.redraw()
        glFlush()

    def set_x_loc(self, x):
        """
        Set the x location of the last object added to this scene
        @param x: the x location for the object
        """
        if self.shapes != []:
            self.shapes[-1].set_location(x, self.shapes[-1].getY())

    def set_y_loc(self, y):
        """
        Set the y location of the last object added to this scene
        @param y: the y location for the object
        """
        if self.shapes != []:
            self.shapes[-1].set_location(self.shapes[-1].getX(), y)

    def set_location(self, x, y):
        """
        Set the x, y location of the last object added to this scene
        @param x: the x location for the object
        @param y: the y location for the object
        """
        self.shapes[-1].set_location(x, y)
        self.redraw()

class Scene3D(object):
    """
    A Scene capable of maintaining a collection of 3D objects
    """
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

    def add_object(self, new_shape=None):
        """
        Add a shape to this scene
        @param new_shape: New Shape to add to this scene
        """
        self.shapes.append(new_shape)

    def clear(self):
        """
        Clear all of the shapes from this scene
        """
        self.shapes = []
        self.redraw()

    def reset_view(self):
        """
        Reset the view for this scene
        """
        self.set_look_at(10, 3, 10, 0, 0, 0, 0, 1, 0)
        self.set_perspective(10, 1.33, 0.1, 100.0)
        self.init = True

    def set_look_at(self, eye_x, eye_y, eye_z, look_x, look_y, look_z, up_x,
                    up_y, up_z):
        """
        Set the lookat parameters for this scene
        @param eye_x: x location for the eye point of the scene
        @param eye_y: y location for the eye point of the scene
        @param eye_z: z location for the eye point of the scene
        @param look_x: x location for the lookat point in the scene
        @param look_y: y location for the lookat point in the scene
        @param look_z: z location for the lookat point in the scene
        @param up_x: x location for the up point in the scene
        @param up_y: y location for the up point in the scene
        @param up_z: z location for the up point in the scene
        """
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
        """
        Return the lookat parameters for this scene
        """
        return (self.eye_x, self.eye_y, self.eye_z, self.look_x, self.look_y,
                self.look_z, self.up_x, self.up_y, self.up_z)

    def set_perspective(self, angle=None, ratio=None, near=None, far=None):
        """
        Set the perspective for this scene
        @param angle: field of view angle for the scene in degrees
        @param ratio: aspect ratio that determines the field of view in x 
        @param near: distance from the viewer to the near clipping plane
        @param far: distance from the viewer to the far clipping plane
        """
        self.view_angle = angle or self.view_angle
        self.aspect_ratio = ratio or self.aspect_ratio
        self.near = near or self.near
        self.far = far or self.far

    def eye(self):
        """
        Return the eye values for this scene
        """
        return self.eye_x, self.eye_y, self.eye_z

    def look(self):
        """
        Return the lookat values for this scene
        """
        return self.look_x, self.look_y, self.look_z

    def up(self):
        """
        Return the up values for this scene
        """
        return self.up_x, self.up_y, self.up_z

    def perspective(self):
        """
        Return the perspective values for this scene
        """
        return self.view_angle, self.aspect_ratio, self.near, self.far

    def redraw(self):
        """
        Redraw this scene by redrawing each individual element within it
        """
        for shape in self.shapes:
            shape.redraw()
        glFlush()

    def set_ortho(self, left, right, bottom, top, near, far):
        """
        Set the ortho variables for this scene
        """
        self.left = left
        self.right = right
        self.bottom = bottom
        self.top = top
        self.near = near
        self.far = far

    def ortho(self):
        """
        Return the ortho variables for this scene
        """
        return self.left, self.right, self.bottom, self.top, self.near, self.far

    def set_frustum(self, left, right, bottom, top, near, far):
        """
        Set the frustum variables for this scene
        """
        self.fleft = left
        self.fright = right
        self.fbottom = bottom
        self.ftop = top
        self.fnear = near
        self.ffar = far

    def frustum(self):
        """
        Return the frustum variables for this scene
        """
        return self.fleft, self.fright, self.fbottom, self.ftop, self.fnear, self.ffar

    def set_draw_axes(self, yesno):
        """
        Toggle the draw_axes variable for this scene
        """
        self.draw_axes = yesno

    def set_projection_type(self, p_type=True):
        """
        Set the projection type for this scene
        """
        self.parallel = p_type

    def projection_type(self):
        """
        Return the projection type for this scene
        """
        return self.parallel

class Texture(wx.Image):
    """
    Texture object
    """
    def __init__(self, name='Sunrise.jpg'):
        wx.Image.__init__(self, name)
        self.texture_id = glGenTextures(1)

    def load_jpeg(self, file_name):
        """
        Process the jpeg data for this image
        """
        height = self.GetHeight()
        width  = self.GetWidth()
        image  = self.GetData()
        print width, height

        glBindTexture(GL_TEXTURE_2D, self.texture_id)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT )
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT )
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR )
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR )
        # map the image data to the texture. note that if the input
        # type is GL_FLOAT, the values must be in the range [0..1]
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_LUMINANCE,
                     GL_UNSIGNED_BYTE, self.GetData())

    def enable(self):
        """
        Enable the current texture
        """
        glEnable(GL_TEXTURE_2D)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL)
        glBindTexture(GL_TEXTURE_2D, self.texture_id)

    def disable(self):
        """
        Disable the current texture
        """
        glDisable( GL_TEXTURE_2D )
