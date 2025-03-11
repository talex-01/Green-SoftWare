# Definir variáveis
ARRAYSIZE=1000000
NTIMES=10

export ARRSIZE
export NTIMES

# Definir o compilador e as flags
CC=/usr/bin/gcc
CFLAGS=-O2

# Definir os arquivos de origem
SRC_INT=bubblesortI.c
SRC_FLOAT=bubblesortF.c
SRC_DOUBLE=bubblesortD.c
SRC_STRING=bubblesortS.c  # Adicionado para strings

# Definir os arquivos de saída
OUT_INT=bubbleSort_int_run
OUT_FLOAT=bubbleSort_float_run
OUT_DOUBLE=bubbleSort_double_run
OUT_STRING=bubbleSort_string_run  # Adicionado para strings

# Definir o prefixo do nome do arquivo do array
ARRAY_FILE_PREFIX=../array_

# Targets principais

all: compile

# Compilação dos 4 arquivos com os respectivos tipos
compile:
	$(CC) $(CFLAGS) $(SRC_INT) -o $(OUT_INT)
	$(CC) $(CFLAGS) $(SRC_FLOAT) -o $(OUT_FLOAT)
	$(CC) $(CFLAGS) $(SRC_DOUBLE) -o $(OUT_DOUBLE)
	$(CC) $(CFLAGS) $(SRC_STRING) -o $(OUT_STRING)  # Compilação do programa de ordenação para strings

# Medições para cada tipo de dado
measureInt:
	sudo modprobe msr
	sudo ../../../../RAPL/main "./$(OUT_INT) $(ARRAY_FILE_PREFIX)int_$(ARRAYSIZE)_sorted.bin" C bubbleSortInt $(NTIMES)

measureFloat:
	sudo modprobe msr
	sudo ../../../../RAPL/main "./$(OUT_FLOAT) $(ARRAY_FILE_PREFIX)float_$(ARRAYSIZE).bin" C bubbleSortFloat $(NTIMES)

measureDouble:
	sudo modprobe msr
	sudo ../../../../RAPL/main "./$(OUT_DOUBLE) $(ARRAY_FILE_PREFIX)double_$(ARRAYSIZE).bin" C bubbleSortDouble $(NTIMES)

measureString:
	sudo modprobe msr
	sudo ../../../../RAPL/main "./$(OUT_STRING) $(ARRAY_FILE_PREFIX)string_$(ARRAYSIZE).bin" C bubbleSortString $(NTIMES)  # Medição para o algoritmo de string

# Execuções diretas dos programas de sort
runInt:
	./$(OUT_INT) "$(ARRAY_FILE_PREFIX)int_$(ARRAYSIZE)_sorted.bin"

runFloat:
	./$(OUT_FLOAT) $(ARRAY_FILE_PREFIX)float_$(ARRAYSIZE).bin

runDouble:
	./$(OUT_DOUBLE) $(ARRAY_FILE_PREFIX)double_$(ARRAYSIZE).bin

runString:
	./$(OUT_STRING) $(ARRAY_FILE_PREFIX)string_$(ARRAYSIZE).bin # Execução para o algoritmo de string

# Medição de memória para cada tipo de dado
memInt:
	{ /usr/bin/time -v ./$(OUT_INT) $(ARRAY_FILE_PREFIX)int_$(ARRAYSIZE).bin > /dev/null; } 2>&1 | grep "Maximum resident"

memFloat:
	{ /usr/bin/time -v ./$(OUT_FLOAT) $(ARRAY_FILE_PREFIX)float_$(ARRAYSIZE).bin > /dev/null; } 2>&1 | grep "Maximum resident"

memDouble:
	{ /usr/bin/time -v ./$(OUT_DOUBLE) $(ARRAY_FILE_PREFIX)double_$(ARRAYSIZE).bin > /dev/null; } 2>&1 | grep "Maximum resident"

memString:
	{ /usr/bin/time -v ./$(OUT_STRING) $(ARRAY_FILE_PREFIX)string_$(ARRAYSIZE).bin > /dev/null; } 2>&1 | grep "Maximum resident"  # Medição de memória para strings

# Limpeza dos arquivos compilados
clean:
	rm -f $(OUT_INT) $(OUT_FLOAT) $(OUT_DOUBLE) $(OUT_STRING)
