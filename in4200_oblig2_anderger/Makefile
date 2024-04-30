.PHONY: all clean

all: serial parallel

clean: serial_clean parallel_clean

serial:
	$(MAKE) -C ./serial_code

serial_clean:
	$(MAKE) -C ./serial_code clean

parallel:
	$(MAKE) -C ./parallel_code 

parallel_clean:
	$(MAKE) -C ./parallel_code clean
