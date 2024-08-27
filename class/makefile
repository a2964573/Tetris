CXX = g++
CXXFLAGS = -Wall -g -shared

BUILDDIR = ..\build

USER_SRC = user.cpp
UTIL_SRC = util.cpp

USER_LIB = $(BUILDDIR)\user.lib
UTIL_LIB = $(BUILDDIR)\util.lib

all: $(USER_LIB) $(UTIL_LIB)

$(USER_LIB): $(USER_SRC)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(USER_LIB) $(USER_SRC)

$(UTIL_LIB): $(UTIL_SRC)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(UTIL_LIB) $(UTIL_SRC)

clean:
	del /Q $(USER_LIB)
	del /Q $(UTIL_LIB)
