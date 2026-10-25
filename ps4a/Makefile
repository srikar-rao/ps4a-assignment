CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude -I/opt/homebrew/include
LDFLAGS := -L/opt/homebrew/lib
LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system
TARGET := AniPlayer
SRC := src/main.cpp src/KeyFrame.cpp src/Component.cpp src/AniPlayer.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET) $(ARGS)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
