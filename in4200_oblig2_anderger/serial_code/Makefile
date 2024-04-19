CC = gcc
CFLAGS = -Wall
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

OBJDIR = obj
BINDIR = ../

SRCS = $(wildcard *.c)
HDRS = $(wildcard *.h)


PROJ = denoise_serial
# OBJS = $(OBJDIR)/serial_main.o
OBJS = serial_main.o

all: simple-jpeg $(PROJ)

#$(PROJ): $(OBJS)
$(PROJ): $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o ../$@
	
simple-jpeg:
	$(MAKE) -C ../simple-jpeg

obj-clean: 
	$(RM) *.o

exec-clean: 
	$(RM) ../$(PROJ)

autosave-clean:
	$(RM) *~

clean: 
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../../example_folder/simple-jpeg clean
