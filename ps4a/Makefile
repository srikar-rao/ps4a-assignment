CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system
TARGET := AniPlayer
SRC := src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
