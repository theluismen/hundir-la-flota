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
	$(CC) $(OBJS) -o $(TARGET)

## COMPILAR LOS ARCHIVOS FUENTE ##
./obj/%.o: ./src/%.c
	$(CC) $(CCFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@ rm -vf ./obj/*.o $(TARGET)

run: $(TARGET)
	@ ./$(TARGET)
