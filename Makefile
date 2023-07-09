## VARIABLES ##
CC 		:= gcc
CCFLAGS	:= -Wall
INCDIR 	:= ./inc/
OBJS 	:= ./obj/main.o \
		   ./obj/common.o \
		   ./obj/generar.o
TARGET 	:= ./bin/hundir-la-flota.out

## CREAR EJECUTABLE ##
$(TARGET): $(OBJS)
	@ echo "[+] - ENLAZANDO EJECUTABLE $@"
	@ $(CC) $(OBJS) -o $(TARGET)

## COMPILAR LOS ARCHIVOS FUENTE ##
./obj/%.o: ./src/%.c
	@ echo "[+] - COMPILANDO ARCHIVO FUENTE $<"
	@ $(CC) $(CCFLAGS) -I$(INCDIR) -c $< -o $@

## LIMPIAR DIRECTORIO DE ARCHIVOS OBJETO Y EL EJECUTABLE  ##
clean:
	@ rm -vf ./obj/*.o $(TARGET)

## EJECUTAR EL PROGRAMA ##
run: $(TARGET)
	@ echo "[+] - EJECUTANDO PROGRAMA $(TARGET)"
	@ echo
	@ ./$(TARGET)
