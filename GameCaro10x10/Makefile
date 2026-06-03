# Makefile for GameCaro10x10

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wshadow -Wconversion -O2
LDFLAGS  :=

TARGET   := main.exe
BUILDDIR := build

SOURCES := $(wildcard main.cpp) $(wildcard manager/*.cpp) $(wildcard core/*.cpp) $(wildcard player/*.cpp) $(wildcard bot/*.cpp) $(wildcard replay/*.cpp) $(wildcard ui/*.cpp)
OBJECTS := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: %.cpp
	@if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@if exist "$(BUILDDIR)" rmdir /s /q "$(BUILDDIR)"
	@if exist "$(TARGET)" del /f /q "$(TARGET)"

rebuild: clean all
