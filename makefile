CXX = g++
CXXFLAGS = -Wall -g

BUILDDIR = build
SUBDIRS  = class framework

OBJS = 	$(BUILDDIR)/Util.o \
		$(BUILDDIR)/User.o \
		$(BUILDDIR)/login.o \
		$(BUILDDIR)/main.o

TARGET = tetris.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(BUILDDIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILDDIR)/main.o

subdirs :
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	rm -f $(BUILDDIR)\*.o
