CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = build

SOURCE = main.cpp

TARGET = tetris.exe

$(TARGET): $(SOURCE)
	@if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) -L $(BUILDDIR) -lutil -luser -llogin

clean:
	del /Q $(TARGET)
