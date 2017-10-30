.SUFFIXES:.cpp .o
PP=g++
CC=gcc

INCLUDES=-Iinclude

LIBS=-lglfw3 -lopengl32 -lglu32 -lgdi32 -lassimp

LINKS=-Llib/GLFW -Llib/assimp

SRCSpp= src\main.cpp\
		src\tool.cpp\
		src\shader.cpp\
		src\camera.cpp\
		src\stb.cpp\
		src\mesh.cpp\
		src\model.cpp\
		src\light.cpp

SRCScc=src\glad.c

OBJS=$(SRCSpp:.cpp=.o) $(SRCScc:.c=.o)

EXE=main

start:$(OBJS)
	$(PP) $(LINKS) -o $(EXE) $(OBJS) $(LIBS)
	@make clean
	@echo ***********Compelete*************
#	$(EXE)
%.o:%.cpp
	$(PP) -o $@ -c $< $(INCLUDES)
%.o:%.c
	$(CC) -o $@ -c $< $(INCLUDES)
clean:
	del $(OBJS)