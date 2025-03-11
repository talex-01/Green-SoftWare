NTIMES=10
FIB_NUM=47

export NTIMES

CC=/usr/bin/gcc
CFLAGS= -O0

all: compile

compile: 
	$(CC) $(CFLAGS) fibR.c -o fibR_run
	$(CC) $(CFLAGS) fibI.c -o fibI_run

measureR:
	sudo modprobe msr
	sudo ../../../RAPL/main "./fibR_run $(FIB_NUM)" C fibR $(NTIMES)

measureI:
	sudo modprobe msr
	sudo ../../../RAPL/main "./fibI_run $(FIB_NUM)" C fibI $(NTIMES)

runR:
	./fibR_run $(FIB_NUM)

runI:
	./fibI_run $(FIB_NUM)

memR:
	{ /usr/bin/time -v ./fibR_run $(FIB_NUM) > /dev/null; } 2>&1 | grep "Maximum resident"

memI:
	{ /usr/bin/time -v ./fibI_run $(FIB_NUM) > /dev/null; } 2>&1 | grep "Maximum resident"

clean:
	rm -f fibR_run fibI_run

