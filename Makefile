CC  = g++
LD	= ld
RM 	= rm
ECHO = /bin/echo
PRINTF	= printf
SED	= sed
CP = cp
MV = mv


PROJECT_ROOT=.
SRCDIR = $(PROJECT_ROOT)
OBJDIR = $(PROJECT_ROOT)/obj

LIBS = -I SOIL/src -L ./SOIL/lib/ -lSOIL -lGL -lGLU -lglut -g
TARGET = music-box

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.h)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all setup clean distclean

all: setup ./SOIL/lib/libSOIL.a $(TARGET)

setup:
	@$(ECHO) "Setting up compilation.."
	@mkdir -p obj

./SOIL/lib/libSOIL.a:
	@$(ECHO) "Setting up libSOIL.a"
	@cd ./SOIL/; make
	@$(ECHO) "Done..!!"

$(TARGET): $(OBJS)
	@$(ECHO) "Building executable..."
	@$(CC) -o $@  $(OBJS) $(LIBS)

-include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "Compiling $(notdir $<)\n"
	@$(CC) $(LIBS) -c $< -o $@ -MD

clean:
	@$(ECHO) -n "Cleaning up..."
	@$(RM) -rf $(OBJDIR) *~ $(SRCDIR)/*~
	@$(ECHO) "Done"

distclean:
	@$(ECHO) -n "Cleaning up.."
	@$(RM) -rf $(OBJDIR) *~  $(TARGET)
	@cd ./SOIL/ ; make clean
	@$(ECHO) "Done"
