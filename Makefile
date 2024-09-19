CC := g++
ERRFLAGS := -Wall -Wextra -Wpedantic -Werror
LIBS := -llua5.4
OPT := -O3
CCFLAGS := -std=c++11

OUTPUT := bin
SOURCE_DIR := ./src

SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))
DEPENDS := $(patsubst %.cpp, %.d, $(SOURCES))

.PHONY: all clean package install

all: $(OUTPUT)

clean:
	rm -rf $(OUTPUT) $(OBJECTS) $(DEPENDS)

package: clean
	rm project.7z
	7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on project.7z src Makefile
	
$(OUTPUT): $(OBJECTS)
	$(CC) $(CCFLAGS) $(ERRFLAGS) $(OPT) $^ -o $@ $(LIBS)

-include $(DEPENDS)

%.o: %.c Makefile
	$(CC) $(CCFLAGS) $(ERRFLAGS) $(OPT) -MMD -MP -c $< -o $@ $(LIBS)
