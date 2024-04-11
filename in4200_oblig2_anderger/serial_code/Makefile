CC = gcc
CFLAGS = -Wall
LDFLAGS = -L../../example_folder/simple-jpeg/ -lsimplejpeg

#OBJDIR = obj

PROJ = serial_main
OBJS = serial_main.o

all: simple-jpeg $(PROJ)

$(PROJ): $(OBJS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	
simple-jpeg:
	$(MAKE) -C ../../example_folder/simple-jpeg

obj-clean: 
	$(RM) *.o

exec-clean: 
	$(RM) $(PROJ)

autosave-clean:
	$(RM) *~

clean: 
	$(MAKE) obj-clean
	$(MAKE) exec-clean
	$(MAKE) autosave-clean
	$(MAKE) -C ../../example_folder/simple-jpeg clean
