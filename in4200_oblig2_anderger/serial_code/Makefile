CC = gcc
CFLAGS = -Wall -I../simple-jpeg 
LDFLAGS = -L../simple-jpeg/ -lsimplejpeg

OBJDIR = obj
BINDIR = ..
PROJ = denoise_serial

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean 

all: simple-jpeg $(BINDIR)/$(PROJ) 
 

# $(OBJS): $(SRCS) $(HDRS)
$(BINDIR)/$(PROJ): $(OBJS) 
	$(CC) $(CFLAGS) $^  -o $@ $(LDFLAGS) 

$(OBJDIR)/%.o: %.c serial_functions.h
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ 
	
simple-jpeg:
	$(MAKE) -C ../simple-jpeg

clean: 
	-@rm obj/*.o
	-@rm ../denoise_serial
	$(MAKE) -C ../simple-jpeg clean


