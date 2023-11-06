# Nombre del programa
PROGRAM = MCPwB

# Compilador C++
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Fuentes y objetos
SRCS = MCPwB.cpp
OBJS = $(SRCS:.cpp=.o)

# Regla de construcción de objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla de construcción del programa
$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJS)

# Limpiar archivos objeto y ejecutable
clean:
	rm -f $(OBJS) $(PROGRAM)

# Regla de compilación por defecto
all: $(PROGRAM)

# Ejecutar el programa
run: all
	./$(PROGRAM)

.PHONY: clean all run