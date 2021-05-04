# General Info
PACKAGE = neusctom
VERSION = 1
DATE    = $(shell date "+%b%Y")

# Build info
EXE         = $(PACKAGE)
CDEBUG      = -O0
CXXFLAGS    = $(CDEBUG) -c -g -Wno-reorder -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb $(CFLAGS_PLATFORM) # -Wall -Wextra
LDFLAGS     = -lmenu -lncurses $(LDFLAGS_PLATFORM)
INCLUDESDIR = -I"src/"

# Project source files
CXXFILES = $(shell find src -type f -name '*.cpp')
OBJECTS  = $(CXXFILES:.cpp=.o)


# Verbose mode check:
#V = 1;
ifdef V
MUTE =
VTAG = -v
else
MUTE = @
endif

# Make targets
all:compile doc
	# Build successful!

compile: $(EXE) 
	# Build successful!

$(EXE): $(OBJECTS) $(ENGINE_OBJECTS) $(COMMANDER_OBJECTS)
	# Linking...
	$(MUTE)$(CXX) $(OBJECTS) $(ENGINE_OBJECTS) $(COMMANDER_OBJECTS) -o $(EXE) $(LIBSDIR) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $<...
	$(MUTE)$(CXX) $(CXXFLAGS) $(CDEBUG) $< -c -o $@ $(DEFINES) $(INCLUDESDIR)


run: compile 
	# Running...
	$(MUTE)./$(EXE)

doc:
	# Generating documentation...
	$(MUTE)doxygen Doxyfile

docclean:
	# Cleaning documentation...
	-$(MUTE)rm $(VTAG) -rf doc

clean: docclean
	# Cleaning object files...
	$(MUTE)rm $(VTAG) -f $(OBJECTS)
	$(MUTE)rm $(VTAG) -f $(EXE)

clean-all: clean
	# Cleaning object files...
	$(MUTE)rm $(VTAG) -f $(ENGINE_OBJECTS) $(COMMANDER_OBJECTS)

