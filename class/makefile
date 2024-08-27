CXX = g++
CXXFLAGS = -Wall -g -shared

BUILDDIR = ..\build

USER_SRC = user.cpp
UTIL_SRC = util.cpp

USER_DLL = $(BUILDDIR)\user.dll
UTIL_DLL = $(BUILDDIR)\util.dll

all: $(USER_DLL) $(UTIL_DLL)

$(USER_DLL): $(USER_SRC)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(USER_DLL) $(USER_SRC)

$(UTIL_DLL): $(UTIL_SRC)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(UTIL_DLL) $(UTIL_SRC)

clean:
	del /Q $(USER_DLL)
	del /Q $(UTIL_DLL)
