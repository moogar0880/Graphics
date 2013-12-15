import OpenGL
# OpenGL.ERROR_CHECKING = False
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from GLutils import Color

class Shape(object):
    """docstring for Shape"""
    def __init__(self):
        super(Shape, self).__init__()
        self.color = None
        self.set_color(1, 0, 0)
        self.set_location(0, 0)
        self.set_size(1, 1)

    def set_location(self, x=0.0, y=0.0):
        self.xLoc = x
        self.yLoc = y

    def set_size(self, xs=1.0, ys=1.0):
        self.xSize = xs
        self.ySize = ys

    def getX(self):
        return self.xLoc

    def getY(self):
        return self.yLoc

    def set_color(self, r=0.0, g=0.0, b=0.0, c=None):
        if c == None:
            self.color = Color(r, g, b)
        else:
            self.color = c

class Shape3D(object):
    """docstring for Shape3D"""
    def __init__(self):
        super(Shape3D, self).__init__()
        self.color = Color(1, 0, 0)
        self.xLoc = self.yLoc = self.zLoc = 0.0
        self.xSize = self.ySize = self.zSize = 1
        self.angle = self.dx_rot = self.dy_rot = self.dz_rot = 0

    def set_color(self, r=0.0, g=0.0, b=0.0, c=None):
        if c == None:
            self.color = Color(r, g, b)
        else:
            self.color = c

    def set_location(self, x=0.0, y=0.0, z=0.0):
        self.xLoc = x
        self.yLoc = y
        self.zLoc = z

    def set_size(self, xs=1.0, ys=1.0, zs=1.0):
        self.xSize = xs
        self.ySize = ys
        self.zSize = zs

    def set_rotate(self, a, dx, dy, dz):
        self.angle = a
        self.dx_rot = dx
        self.dy_rot = dy
        self.dz_rot = dz

    def getX(self):
        return self.xLoc

    def getY(self):
        return self.yLoc

    def getZ(self):
        return self.zLoc

    def getLocation(self):
        return self.xLoc, self.yLoc, self.zLoc

class Triangle(Shape):
    """docstring for Triangle"""
    def __init__(self):
        super(Triangle, self).__init__()
        self.nPoints = 3
        self.dx = [0.0, 40.0, 20.0]
        self.dy = [0.0, 0.0, 75.0]

    def redraw(self):
        glColor(self.color.red, self.color.green, self.color.blue)
        glBegin(GL_POLYGON)
        for i in range(self.nPoints):
            glVertex2f(self.xLoc + self.dx[i] * self.xSize,
                       self.yLoc + self.dy[i] * self.ySize)
        glEnd()

class Box(Shape3D):
    """
    """
    def __init__(self):
        super(Box, self).__init__()
        self.length = 1

    def redraw(self):
        print 'Box Redraw'
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidCube(self.length)
        glPopMatrix()

class Sphere(Shape3D):
    """
    """
    def __init__(self):
        super(Sphere, self).__init__()
        self.radius = 1

    def redraw(self):
        print 'Sphere Redraw'
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidSphere(self.radius, 360, 360)
        glPopMatrix()

class Cone(Shape3D):
    """docstring for Cone"""
    def __init__(self):
        super(Cone, self).__init__()
        self.length = 1

    def redraw(self):
        print 'Cone Redraw'
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidCone(0.5, 1, 50, 50)
        glPopMatrix()

class Donut(Shape3D):
    """docstring for Donut"""
    def __init__(self):
        super(Donut, self).__init__()

    def redraw(self):
        print 'Donut redraw'
        glPushMatrix()
        glColor3f(self.color.red, self.color.green, self.color.blue)
        glTranslatef(self.xLoc, self.yLoc, self.zLoc)
        glRotatef(self.angle, self.dx_rot, self.dy_rot, self.dz_rot)
        glScalef(self.xSize, self.ySize, self.zSize)
        glutSolidTorus(self.xSize/4, self.xSize/2, 10, 50)
        glPopMatrix()

class Eye(Shape3D):
    """docstring for Eye"""
    def __init__(self):
        super(Eye, self).__init__()
        self.build_eye()
        self.build_pupil()

    def build_eye(self):
        self.sclera = Donut()
        self.sclera.set_color(1, 1, 1)
        self.sclera.set_location(0, 0, 0)
        self.sclera.set_size(self.xSize, self.ySize, self.zSize)

    def build_pupil(self):
        self.pupil = Sphere()
        self.pupil.set_color(0, 0, 1)
        self.pupil.set_location(0, 0, 0)
        self.pupil.set_size(self.xSize * 0.25, self.ySize * 0.25, self.zSize * 0.25)

    def set_size(self, xs, ys, zs):
        self.sclera.set_size(xs, ys, zs)
        self.pupil.set_size(xs * 0.25, ys * 0.25, zs * 0.25)

    def set_location(self, x, y, z):
        self.sclera.set_location(x, y, z)
        self.pupil.set_location(x, y, z)

    def set_rotate(self, angle, dx, dy, dz):
        self.sclera.set_rotate(angle, dx, dy, dz)
        self.pupil.set_rotate(angle, dx, dy, dz)

    def set_color(self, r, g, b, index=0):
        if index == 1:
            self.sclera.set_color(r, g, b)
        else:
            self.pupil.set_color(r, g, b)

    def redraw(self):
        self.sclera.redraw()
        self.pupil.redraw()

class Hat(Shape3D):
    """docstring for Hat"""
    def __init__(self):
        super(Hat, self).__init__()
        self.build_hat()
        self.build_tip()

    def build_hat(self):
        self.cone = Cone()
        self.cone.set_color(1, 1, 0)
        self.cone.set_location(0, 0, 0)
        self.cone.set_size(1, 1, 1)

    def build_tip(self):
        self.tip = Sphere()
        self.tip.set_color(0, 0, 1)
        self.tip.set_location(0, 1.1, 0)
        self.tip.set_size(0.15, 0.15, 0.15)

    def set_size(self, xs, ys, zs):
        self.cone.set_size(xs, ys, zs)
        self.tip.set_size(xs * 0.15, ys * 0.15, zs * 0.15)

    def set_location(self, x, y, z):
        self.cone.set_location(x, y, z)
        self.tip.set_location(self.cone.getX(), self.cone.getY() + 0.5, self.cone.getZ())


    def set_rotate(self, angle, dx, dy, dz):
        self.cone.set_rotate(angle, dx, dy, dz)
        self.tip.set_rotate(angle, dx, dy, dz)

    def set_color(self, r, g, b, index=0):
        if index == 0:
            self.cone.set_color(r, g, b)
        else:
            self.tip.set_color(r, g, b)

    def redraw(self):
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
        self.left = Eye()
        self.left.set_color(0, 0, 1)
        self.left.set_location(self.head.getX() + 1, self.head.getY() + 0.5, self.head.getZ() + 1)
        self.left.set_size( 0.5, 0.5, 0.5 )

        self.right = Eye()
        self.right.set_color(0, 0, 1)
        self.right.set_location(self.head.getX() + 0.5, self.head.getY() + 0.5, self.head.getZ() + 1.5)
        self.right.set_size(0.5, 0.5, 0.5)

    def set_size(self, xs, ys, zs):
        self.head.set_size(xs, ys, zs)
        constant = 0.6666666667
        self.left.set_size(xs * constant, ys * constant, zs * constant)
        self.right.set_size(xs * constant, ys * constant, zs * constant)

    def set_location(self, x, y, z):
        self.head.set_location(x, y, z)
        self.left.set_location(self.head.getX() + 0.5, self.head.getY() + 0.5, self.head.getZ() + 1.5)
        self.right.set_location(self.head.getX() + 1, self.head.getY() + 0.5, self.head.getZ() + 1)

    def set_rotate(self, angle, dx, dy, dz):
        self.head.set_rotate( angle, dx, dy, dz )
        self.left.set_rotate( angle, dx, dy, dz )
        self.right.set_rotate( angle, dx, dy, dz )

    def set_color(self, r, g, b, index=0):
        if index == 0:
            self.head.set_color( r, g, b )
        else:
            self.left.set_color( r, g, b )
            self.right.set_color( r, g, b )

    def redraw(self):
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
        self.head.set_size( 0.75, 0.75, 0.75 )

        self.build_nose()

    def build_nose(self):
        self.nose = Cone()
        self.nose.set_rotate( 90, 0, 0, 0 )
        self.nose.set_location(self.head.getX(), self.head.getY(), self.head.getZ() + 1)
        self.nose.set_size( 0.5, 0.5, 0.5 )

    def set_size(self, xs, ys, zs):
        self.head.set_size( xs, ys, zs )
        constant = 0.6666666667
        self.nose.set_size(xs * constant, ys * constant, zs * constant)

    def set_location(self, x, y, z):
        self.head.set_location( x, y, z )
        self.nose.set_location( self.head.getX(), self.head.getY(), self.head.getZ() + 0.9 )

    def set_rotate(self, angle, dx, dy, dz):
        self.head.set_rotate( angle, dx, dy, dz )
        self.nose.set_rotate( angle, dx, dy, dz )

    def set_color(self, r, g, b, index=0):
        if index == 0:
            self.head.set_color(r, g, b)
        else:
            self.nose.set_color(r, g, b)

    def redraw(self):
        self.head.redraw()
        self.nose.redraw()

class Clown(Shape3D):
    """docstring for Clown"""
    def __init__(self):
        super(Clown, self).__init__()
        self.head = Head()
        self.head.set_color(0.46, 0.65, 1.0)
        self.head.set_location(0, 0, 0)
        self.head.set_size(0.75, 0.75, 0.75)
        self.build_hat()

    def build_hat(self):
        self.hat = Hat()
        self.hat.set_location(self.head.getX(), self.head.getY(), self.head.getZ())
        self.hat.set_size(0.5, 0.5, 0.5)

    def set_size(self, xs, ys, zs):
        self.head.set_size(xs, ys, zs)
        constant = 0.6666666667
        self.hat.set_size(xs * constant, ys * constant, zs * constant)

    def set_location(self, x, y, z):
        self.head.set_location( x, y, z )
        self.hat.set_location( self.head.getX(), self.head.getY() + 0.75, self.head.getZ() )

    def set_rotate(self, angle, dx, dy, dz):
        self.head.set_rotate(angle, dx, dy, dz)
        self.hat.set_rotate(angle, dx, dy, dz)

    def set_color(self, r, g, b, index=0):
        if index == 0:
            self.head.set_color(r, g, b)
        else:
            self.hat.set_color(r, g, b)

    def redraw(self):
        self.head.redraw()
        self.hat.redraw()
