default:
	g++ ./main.c ./include/*.c -o Nivanverso.exe -O2 -Wall -Wno-missing-braces -I ./include/ -L ./lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	./build.exe