#
# Revised Makefile for C++ OpenGL applications suitable for CS770/870
#   rdb
#   08/29/2013 last edit
#
# Simply modify the list of source files assigned to the SRCS variable

# -------------- Support tool specs ---------------------------------
CC          = gcc
CCC	      = g++
LINKER	   = g++
MAKEFILE    = Makefile

# --------  Compile time search specs for include files -----------------
GL_INC      = -I/usr/X11/include/GL
X_INC       = -I/usr/X11/include

#--------- Library search specs -----------------------------
#
# At the start of the semester, you'll only need the basic GL libraries;
#   Once you've added glui to your system and later jpeglib, you'll need to
#   delete the assignments that make their variables empty.

# basic opengl libraries
GL_LIBS     = -lglut -lGLU -lGL
#
GLUI_LIB    = -lglui
#-------------- after loading glui, delete the line below
GLUI_LIB    =
#------------- delete above line ------------

JPEG_LIB    = -ljpeg
#-------------- after loading jpeg, delete the line below
JPEG_LIB    =
#------------- delete above line ------------

XLIBS       = -L/usr/X11/lib -lXmu -lXext -lX11 -lXi

LIBS	    = $(XLIBS) $(GL_LIBS) $(GLUI_LIB) $(JPEG_LIB) -lm -ldl

# -------------- Compiler and Linker flags ---------------
CPPFLAGS    = -Wall -g $(X_INC) $(GL_INC) $(JPEG_INC)
#
# If any linker flags are needed, they should be prefixed by "-Wl,"
# This insures that cpp or cc will not confuse these flags with ones
# intended for it.
#
LDFLAGS     =

#---------- Application info ------------------------------------------
PROG = p0

SRCS = $(PROG).cpp \
	   Point.cpp \
       Triangle.cpp \
       Quad.cpp \
       Rectangle.cpp \
       Polygon.cpp \
       Shape.cpp

# for every .cpp input, need to produce a .o
OBJS = $(SRCS:.cpp=.o)

# for every .c input (if there are any), need to produce a .o
COBJS = $(SRCS:.c=.o)

# ---------- actions ----------------------------------------------
all:	compile $(PROG)

compile: $(OBJS)

new:	clean all

%.o : %.cpp %.h
	$(CCC) -c $(CPPFLAGS) $*.cpp

$(PROG): $(OBJS) $(COBJS)
	$(LINKER) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

clean:
	rm -f *.o $(PROG)
