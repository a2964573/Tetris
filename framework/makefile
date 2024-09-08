CXX = g++
CXXFLAGS = -Wall -lssl -lcrypto -g

APPLYDIR = ../build/application
BUILDDIR = ../build/framework
CLASSDIR = ../build/class
INTFCDIR = ../build/interface

OBJS =	$(BUILDDIR)/login.o \
		$(BUILDDIR)/main.o \

CLSS =	$(CLASSDIR)/util.o \
		$(CLASSDIR)/user.o \
		$(CLASSDIR)/crypt.o \
		$(INTFCDIR)/client.o \

TARGET = tetris.exe

all: login main

login: login.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c login.cpp -o $(BUILDDIR)/login.o

main: main.cpp
	@if [ ! -d $(BUILDDIR) ]; then mkdir -p $(BUILDDIR); fi
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(BUILDDIR)/main.o

clean:
	rm -f $(OBJS)

upver:
	rm -f $(APPLYDIR)/$(TARGET)
	$(CXX) $(CXXFLAGS) -o $(APPLYDIR)/$(TARGET) $(CLSS) $(OBJS)

