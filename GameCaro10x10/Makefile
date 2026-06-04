# Makefile cho GameCaro10x10 - bien dich toan bo module C++

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wshadow -Wconversion -O2

# Ten file thuc thi tuy he dieu hanh
ifeq ($(OS),Windows_NT)
    TARGET := main.exe
else
    TARGET := main
endif

BUILDDIR := build

# Thu thap tat ca file .cpp tu cac thu muc
SOURCES := $(wildcard main.cpp) \
           $(wildcard manager/*.cpp) \
           $(wildcard core/*.cpp) \
           $(wildcard player/*.cpp) \
           $(wildcard bot/*.cpp) \
           $(wildcard replay/*.cpp) \
           $(wildcard ui/*.cpp)

OBJECTS := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SOURCES))

.PHONY: all clean rebuild run

# Muc tieu mac dinh: tao file thuc thi
all: $(TARGET)

# Lien ket cac object thanh chuong trinh
$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@

# Bien dich tung file .cpp thanh .o trong thu muc build
$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Chay chuong trinh sau khi build
run: $(TARGET)
	./$(TARGET)

# Xoa thu muc build va file thuc thi
clean:
	rm -rf $(BUILDDIR)
	rm -f main main.exe

# Build lai tu dau
rebuild: clean all
