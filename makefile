CXX = g++
CXXFLAGS = -Wall -lssl -lcrypto -g

CLASSODIR=	build/class
INTDCODIR=	build/interface
FRMWKODIR=	build/framework
OBJECDIR =	$(CLASSODIR) \
			$(INTDCODIR) \
			$(FRMWKODIR)
APPLYDIR =	build/application

SUBDIRS  =  class interface framework

OBJS = 	$(CLASSODIR)/util.o \
		$(CLASSODIR)/user.o \
		$(CLASSODIR)/crypt.o \
		$(INTDCODIR)/client.o \
		$(FRMWKODIR)/login.o \
		$(FRMWKODIR)/main.o

TARGET = tetris.exe

all: sub

sub:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	rm -f $(OBJS)

upver:
	rm -f $(TARGET)
	$(CXX) $(CXXFLAGS) -o $(APPLYDIR)/$(TARGET) $(OBJS)

