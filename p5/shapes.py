import OpenGL
# OpenGL.ERROR_CHECKING = False
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from GLutils import Color

class Shape(object):
    """
    Generic shape class holding all capabilities for 2D shapes
    """
    def __init__(self):
        super(Shape, self).__init__()
        self.color = None
        self.set_color(1, 0, 0)
        self.set_location(0, 0)
        self.set_size(1, 1)

    def set_location(self, x=0.0, y=0.0):
        """
        Set the location of the current shape within it's containing scene
        @param x: x location of this shape
        @param y: y location of this shape
        """
        self.xLoc = x
        self.yLoc = y

    def set_size(self, xs=1.0, ys=1.0):
        """
        Set the size of the current shape within it's containing scene
        @param xs: width of this shape
        @param ys: height of this shape
        """
        self.xSize = xs
        self.ySize = ys

    def getX(self):
        """
        Return the current x location of this shape in it's containing scene
        """
        return self.xLoc

    def getY(self):
        """
        Return the current y location of this shape in it's containing scene
        """
        return self.yLoc

    def set_color(self, r=0.0, g=0.0, b=0.0, c=None):
        """
        Set the color of the current shape
        @param r: red color value
        @param g: green color value
        @param b: blue color value
        @param c: color object to be used as the color for this shape
        """
        if c == None:
            self.color = Color(r, g, b)
        else:
            self.color = c

class Shape3D(object):
    """
    Generic shape class holding all capabilities for 3D shapes
    """
    def __init__(self):
        super(Shape3D, self).__init__()
        self.color = Color(1, 0, 0)
        self.xLoc = self.yLoc = self.zLoc = 0.0
        self.xSize = self.ySize = self.zSize = 1
        self.angle = self.dx_rot = self.dy_rot = self.dz_rot = 0

    def set_color(self, r=0.0, g=0.0, b=0.0, c=None):
        """
        Set the color of the current shape
        @param r: red color value
        @param g: green color value
        @param b: blue color value
        @param c: color object to be used as the color for this shape
        """
        if c == None:
            self.color = Color(r, g, b)
        else:
            self.color = c

    def set_location(self, x=0.0, y=0.0, z=0.0):
        """
        Set the location of the current shape within it's containing scene
        @param x: x location of this shape
        @param y: y location of this shape
        @param z: z location of this shape
        """
        self.xLoc = x
        self.yLoc = y
        self.zLoc = z

    def set_size(self, xs=1.0, ys=1.0, zs=1.0):
        """
        Set the size of the current shape within it's containing scene
        @param xs: width of this shape
        @param ys: height of this shape
        @param zs: depth of this shape
        """
        self.xSize = xs
        self.ySize = ys
        self.zSize = zs

    def set_rotate(self, a, dx, dy, dz):
        """
        Set the rotation of the current shape within it's containing scene
        @param a: angle to rotate this shape to
        @param x: amount to rotate along the x-axis
        @param y: amount to rotate along the y-axis
        @param z: amount to rotate along the z-axis
        """
        self.angle = a
        self.dx_rot = dx
        self.dy_rot = dy
        self.dz_rot = dz

    def getX(self):
        """
        Return the current x location of this shape in it's containing scene
        """
        return self.xLoc

    def getY(self):
        """
        Return the current y location of this shape in it's containing scene
        """
        return self.yLoc

    def getZ(self):
        """
        Return the current z location of this shape in it's containing scene
        """
        return self.zLoc

    def getLocation(self):
        """
        Return the current location of this shape in it's containing scene
        """
        return self.xLoc, self.yLoc, self.zLoc

class Triangle(Shape):
    """
    A 2D tirangle object
    """
    def __init__(self):
        super(Triangle, self).__init__()
        self.nPoints = 3
        self.dx = [0.0, 40.0, 20.0]
        self.dy = [0.0, 0.0, 75.0]

    def redraw(self):
        """
        Custom Triangle redraw method handles drawing a Triangle using OpenGL
        """
        glColor(self.color.red, self.color.green, self.color.blue)
        glBegin(GL_POLYGON)
        for i in range(self.nPoints):
            glVertex2f(self.xLoc + self.dx[i] * self.xSize,
                       self.yLoc + self.dy[i] * self.ySize)
        glEnd()

class Box(Shape3D):
    """
    A 3D Cube object
    """
    def __init__(self):
        super(Box, self).__init__()
        self.length = 1

    def redraw(self):
        """
        Custom Box redraw method handles drawing a Box using OpenGL
        """
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidCube(self.length)
        glPopMatrix()

class Sphere(Shape3D):
    """
    A 3D Sphere object
    """
    def __init__(self):
        super(Sphere, self).__init__()
        self.radius = 1

    def redraw(self):
        """
        Custom Sphere redraw method handles drawing a Sphere using OpenGL
        """
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidSphere(self.radius, 360, 360)
        glPopMatrix()

class Cone(Shape3D):
    """
    A 3D Cone object
    """
    def __init__(self):
        super(Cone, self).__init__()
        self.length = 1
        self.set_rotate(-90, 0, 0, 0)

    def redraw(self):
        """
        Custom Cone redraw method handles drawing a Cone using OpenGL
        """
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidCone(self.xSize, self.ySize*2, 50, 50)
        glPopMatrix()

class Donut(Shape3D):
    """
    A 3D Donut (Taurus) shaped object
    """
    def __init__(self):
        super(Donut, self).__init__()

    def redraw(self):
        """
        Custom Taurus redraw method handles drawing a Taurus using OpenGL
        """
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidTorus(self.xSize/4, self.xSize/2, 10, 50)
        glPopMatrix()

class Eye(Shape3D):
    """
    A 3D Composite shape representing an Eye
    """
    def __init__(self):
        super(Eye, self).__init__()
        self.build_eye()
        self.build_pupil()

    def build_eye(self):
        """
        Build the sclera of the eye
        """
        self.sclera = Donut()
        self.sclera.set_color(1, 1, 1)
        self.sclera.set_location(0, 0, 0)
        self.sclera.set_size(self.xSize, self.ySize, self.zSize)

    def build_pupil(self):
        """
        Build the pupil of the eye
        """
        self.pupil = Sphere()
        self.pupil.set_color(0, 0, 1)
        self.pupil.set_location(0, 0, 0)
        self.pupil.set_size(self.xSize * 0.25, self.ySize * 0.25, self.zSize * 0.25)

    def set_size(self, xs, ys, zs):
        """
        Set the sizes of the composite objects of the eye
        @param xs: width
        @param ys: height
        @param zs: depth
        """
        self.sclera.set_size(xs*1.0, ys*1.0, zs*1.0)
        self.pupil.set_size(xs * 0.3, ys * 0.3, zs * 0.3)

    def set_location(self, x, y, z):
        """
        Set the locations of the composite objects of the eye
        @param x: x location
        @param y: y location
        @param z: z location
        """
        self.sclera.set_location(x, y, z)
        self.pupil.set_location(x, y, z)

    def set_rotate(self, angle, dx, dy, dz):
        """
        Set the rotations of the composite objects of the eye
        @param angle: angle to rotate the composite objects of this shape to
        @param dx: amount to rotate along the x-axis
        @param dy: amount to rotate along the y-axis
        @param dz: amount to rotate along the z-axis
        """
        self.sclera.set_rotate(angle, dx, dy, dz)
        self.pupil.set_rotate(angle, dx, dy, dz)

    def set_color(self, r, g, b, index=0):
        """
        Set the colors of the composite objects of the eye
        """
        if index == 1:
            self.sclera.set_color(r, g, b)
        else:
            self.pupil.set_color(r, g, b)

    def redraw(self):
        """
        Custom Eye redraw method handles drawing an Eye using OpenGL
        """
        self.sclera.redraw()
        self.pupil.redraw()

class Hat(Shape3D):
    """docstring for Hat"""
    def __init__(self):
        super(Hat, self).__init__()
        self.build_hat()
        self.build_tip()

    def build_hat(self):
        """
        Build the body of the hat
        """
        self.cone = Cone()
        self.cone.set_color(1, 1, 0)
        self.cone.set_location(0, 0, 0)
        self.cone.set_size(1, 1, 1)

    def build_tip(self):
        """
        Build the tip of the hat
        """
        self.tip = Sphere()
        self.tip.set_color(0, 0, 1)
        self.tip.set_location(self.cone.getX(), self.cone.getY() + self.cone.ySize/0.7, self.cone.getZ())
        # self.tip.set_size(0.5, 0.5, 0.5)

    def set_size(self, xs, ys, zs):
        """
        Set the size of the composite objects of the hat
        """
        self.cone.set_size(xs*1.0, ys*1.0, zs*1.0)
        self.tip.set_size(xs*0.15, ys*0.15, zs*0.15)
        self.tip.set_location(self.cone.getX(), self.cone.getY() + self.cone.ySize/0.7, self.cone.getZ())

    def set_location(self, x, y, z):
        """
        Set the location of the composite objects of the hat
        """
        self.cone.set_location(x, y, z)
        self.tip.set_location(self.cone.getX(), self.cone.getY() + self.cone.ySize/0.7, self.cone.getZ())

    def set_rotate(self, angle, dx, dy, dz):
        """
        Set the rotation of the composite objects of the hat
        """
        self.cone.set_rotate(angle, dx, dy, dz)
        self.tip.set_rotate(angle, dx, dy, dz)

    def set_color(self, r, g, b, index=0):
        """
        Set the color of the specified composite object of the hat
        """
        if index == 0:
            self.cone.set_color(r, g, b)
        else:
            self.tip.set_color(r, g, b)

    def redraw(self):
        """
        Custom Hat redraw method handles drawing a Hat using OpenGL
        """
        self.cone.redraw()
        self.tip.redraw()

class Head(Shape3D):
    """docstring for Head"""
    def __init__(self):
        super(Head, self).__init__()
        self.head = Sphere()
        self.head.set_color(0.46, 0.65, 1.0)
        self.head.set_location(0, 0, 0)
        self.head.set_size(0.75, 0.75, 0.75)
        self.build_eyes()

    def build_eyes(self):
        """
        """
        self.left = Eye()
        self.left.set_color(0, 0, 1)
        self.left.set_location(self.head.getX() + 1, self.head.getY() + 0.5, self.head.getZ() + 1)
        self.left.set_size( 0.5, 0.5, 0.5 )

        self.right = Eye()
        self.right.set_color(0, 0, 1)
        self.right.set_location(self.head.getX() + 0.5, self.head.getY() + 0.5, self.head.getZ() + 1.5)
        self.right.set_size(0.5, 0.5, 0.5)

    def set_size(self, xs, ys, zs):
        """
        """
        self.head.set_size(xs*1.0, ys*1.0, zs*1.0)
        constant = 0.6666666667
        self.left.set_size(xs * constant, ys * constant, zs * constant)
        self.right.set_size(xs * constant, ys * constant, zs * constant)

    def set_location(self, x, y, z):
        """
        """
        self.head.set_location(x, y, z)
        self.left.set_location(self.head.getX() + 1.0, self.head.getY() + 1.0, self.head.getZ() + 3.0)
        self.right.set_location(self.head.getX() + 2.0, self.head.getY() + 1.0, self.head.getZ() + 2.0)

    def set_rotate(self, angle, dx, dy, dz):
        """
        """
        self.head.set_rotate( angle, dx, dy, dz )
        self.left.set_rotate( angle, dx, dy, dz )
        self.right.set_rotate( angle, dx, dy, dz )

    def set_color(self, r, g, b, index=0):
        """
        """
        if index == 0:
            self.head.set_color( r, g, b )
        else:
            self.left.set_color( r, g, b )
            self.right.set_color( r, g, b )

    def redraw(self):
        """
        Custom Head redraw method handles drawing a Head using OpenGL
        """
        self.head.redraw()
        self.left.redraw()
        self.right.redraw()

class Snowman(Shape3D):
    """docstring for Snowman"""
    def __init__(self):
        super(Snowman, self).__init__()
        self.head = Head()
        self.head.set_color(0.46, 0.65, 1.0)
        self.head.set_location( 0, 0, 0 )
        self.head.set_size( 1.5, 1.5, 1.5 )

        self.build_nose()

    def build_nose(self):
        """
        """
        self.nose = Cone()
        self.nose.set_rotate( 90, 0, 0, 0 )
        self.nose.set_location(self.head.getX(), self.head.getY(), self.head.getZ() + 1)
        self.nose.set_size( 0.5, 0.5, 0.5 )
        self.nose.set_size(self.xSize, self.ySize, self.zSize)

    def set_size(self, xs, ys, zs):
        """
        """
        self.head.set_size(xs*2.0, ys*2.0, zs*2.0)
        self.head.set_size(xs*0.75, ys*0.75, zs*0.75)
        self.nose.set_size(xs*0.75, ys*0.75, zs*0.75)
        self.nose.set_size(xs * 0.5, ys * 0.5, zs * 0.5)

    def set_location(self, x, y, z):
        """
        """
        self.head.set_location( x, y, z )
        self.nose.set_location( self.head.getX(), self.head.getY(), self.head.getZ() + 0.9 )

    def set_rotate(self, angle, dx, dy, dz):
        """
        """
        self.head.set_rotate( angle, dx, dy, dz )
        self.nose.set_rotate( angle, dx, dy, dz )

    def set_color(self, r, g, b, index=0):
        """
        """
        if index == 0:
            self.head.set_color(r, g, b)
        else:
            self.nose.set_color(r, g, b)

    def redraw(self):
        """
        Custom Snowman redraw method handles drawing a Snowman using OpenGL
        """
        self.head.redraw()
        self.nose.redraw()

class Clown(Shape3D):
    """docstring for Clown"""
    def __init__(self):
        super(Clown, self).__init__()
        self.head = Head()
        self.head.set_color(0.46, 0.65, 1.0)
        self.head.set_location(0, 0, 0)
        self.head.set_size(1.5, 1.5, 1.5)
        self.build_hat()

    def build_hat(self):
        """
        """
        self.hat = Hat()
        self.hat.set_location(self.head.getX(), self.head.getY(), self.head.getZ())
        self.hat.set_size(1.5, 1.5, 1.5)

    def set_size(self, xs, ys, zs):
        """
        """
        constant = 0.6666666667
        self.hat.set_size(xs * 1.0, ys * 1.0, zs * 1.0)

    def set_location(self, x, y, z):
        """
        """
        self.head.set_location( x, y, z )
        self.hat.set_location( self.head.getX() - 1.0, self.head.getY() + self.head.ySize + 0.4, self.head.getZ())

    def set_rotate(self, angle, dx, dy, dz):
        """
        """
        self.head.set_rotate(angle, dx, dy, dz)
        self.hat.set_rotate(angle, dx, dy, dz)

    def set_color(self, r, g, b, index=0):
        """
        """
        if index == 0:
            self.head.set_color(r, g, b)
        else:
            self.hat.set_color(r, g, b)

    def redraw(self):
        """
        Custom Clown redraw method handles drawing a Clown using OpenGL
        """
        self.head.redraw()
        self.hat.redraw()
