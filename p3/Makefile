#
# Revised Makefile for C++ OpenGL applications suitable for CS770/870
#   rdb
#   08/29/2013 last edit
#   09/05/2013 Added run option
#              Added wildcard for sources
#   09/12/2013 Added conditionals to account for difference between
#              Mac OS X and Linux
#
# Simply modify the PROG variable to specify the name of your executable
# You may also add entries to MYCPPFLAGS, esp the "std" switch.
#
#---------------------------------------------------------------------

PROG = p3
MYCPPFLAGS = -std=c++11    # a popular compiler option; set if you want

# -------------------- set system-dependent variables ----------------
OS := $(shell uname)

ifeq ($(OS),Darwin)
   CC = clang
   CCC = clang++
   LINKER = clang++
   GL_INC      = -I/Library/Frameworks/GLUI.framework/Headers \
                 -I/System/Library/Frameworks/GLUT.framework/Headers \
                 -I/System/Library/Frameworks/OpenGL.framework/Headers
   GL_LIBS     = -framework OpenGL -framework GLUT -framework GLUI
else
   CC          = gcc 
   CCC         = g++
   LINKER      = g++
   GL_INC      = -I/usr/X11/include/GL
   GL_LIBS     = -lglui -lglut -lGLU -lGL 
endif

# -------------- Common specifications ---------------------------------

MAKEFILE    = Makefile

X_INC       = -I/usr/X11/include

XLIBS       = -L/usr/X11/lib 

LIBS        =  $(XLIBS) $(GL_LIBS) -ljpeg

# -------------- Compiler and Linker flags ---------------
CPPFLAGS    = -Wall $(MYCPPFLAGS) $(GL_INC) $(X_INC) 
#
# If any linker flags are needed, they should be prefixed by "-Wl," 
# This insures that cpp or cc will not confuse these flags with ones
# intended for it.
# 
LDFLAGS     = 

#---------- Application info ------------------------------------------

SRCS = $(wildcard *cpp)

# for every .cpp input, need to produce a .o
OBJS = $(SRCS:.cpp=.o) 

#------------------- dependencies/actions ------------------------
# dependency: need1 need2 ...  
#         action(s)
#
all:	build run

build: compile $(PROG)

compile: $(OBJS) 

new:	clean all

%.o : %.cpp %.h
	$(CCC) -c $(CPPFLAGS) $*.cpp

%.o : %.cpp
	$(CCC) -c $(CPPFLAGS) $*.cpp

$(PROG): $(OBJS) $(COBJS)
	$(LINKER) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROG)

run:
	./$(PROG) Sunrise.jpg

clean:
	rm -f *.o $(PROG)
