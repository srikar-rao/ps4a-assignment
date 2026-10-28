CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra
SFML_CFLAGS ?= $(shell pkg-config --cflags sfml-graphics 2>/dev/null)
SFML_LIBS ?= $(shell pkg-config --libs sfml-graphics 2>/dev/null || printf '%s' '-lsfml-graphics -lsfml-window -lsfml-system')
CPPFLAGS += -Iinclude $(SFML_CFLAGS)
LDLIBS += $(SFML_LIBS)

TARGET := AniPlayer
SRC := src/main.cpp src/KeyFrame.cpp src/Component.cpp src/AniPlayer.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS) $(LDLIBS)

run: $(TARGET)
	./$(TARGET) $(ARGS)

lint:
	cpplint --extensions=cpp,hpp src/*.cpp include/*.hpp

clean:
	rm -f $(TARGET)

.PHONY: all run lint clean
