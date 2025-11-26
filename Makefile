CXX = g++
CXXFLAGS = -std=c++17 -I include
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = MiniDesign.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

clean:
	del src\*.o
	del MiniDesign.exe
