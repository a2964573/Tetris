CXX = g++
CXXFLAGS = -Wall -g -shared

BUILDDIR = ..\..\build

SOURCE = login.h login.cpp

TARGET = $(BUILDDIR)\login.lib

$(TARGET): $(SOURCE)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	del /Q $(TARGET)
