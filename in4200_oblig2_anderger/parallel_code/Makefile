#compiler:
MPICC = mpicc

#compiler flags: 
CFLAGS = -Wall -I../serial_code 

#linker files
LDFLAGS = -lmpi -lm -L../simple-jpeg/ -lsimplejpeg


OBJDIR = obj
#source and object files
SRCS = $(wildcard *.c)
SERIAL_SRCS = $(wildcard ../serial_code/*.c)

OBJS = $(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))

SERIAL_SRCS = ../serial_code
DEPS = $(SERIAL_SRCS)/allocate_image.c $(SERIAL_SRCS)/deallocate_image.c $(SERIAL_SRCS)/convert_image_to_jpeg.c $(SERIAL_SRCS)/convert_jpeg_to_image.c

#executable name
TARGET = ../denoise_parallel

.PHONY: simple-jpeg all clean

#default target
all: simple-jpeg $(TARGET)

simple-jpeg:
	$(MAKE) -C ../simple-jpeg

#rule to build executable
$(TARGET): $(OBJS) $(DEPS)
	$(MPICC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

#rule to compile c source files 
$(OBJDIR)/%.o: %.c parallel_functions.h $(DEPS)
	@mkdir -p obj
	$(MPICC) $(CFLAGS) -c -o $@ $<

#clean rule
clean: 
	@rm -f $(TARGET) $(OBJS)
	$(MAKE) -C ../simple-jpeg clean
