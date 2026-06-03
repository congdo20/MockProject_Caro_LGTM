# Makefile for GameCaro10x10

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wshadow -Wconversion -O2
LDFLAGS :=

TARGET := main.exe

SRCDIRS := . manager core player bot replay ui
SOURCES := $(wildcard main.cpp) $(wildcard manager/*.cpp) $(wildcard core/*.cpp) $(wildcard player/*.cpp) $(wildcard bot/*.cpp) $(wildcard replay/*.cpp) $(wildcard ui/*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

rebuild: clean all
