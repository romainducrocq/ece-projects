UNAME := $(shell uname -m)

ifeq ($(UNAME), x86_64)
	LALLEG     := -L/usr/lib/x86_64-linux-gnu -lalleg
endif

ifeq ($(UNAME), i386)
	LALLEG     := -L/usr/lib/i386-linux-gnu -lalleg
endif

ifeq ($(UNAME), i686)
	LALLEG     := -L/usr/lib/i386-linux-gnu -lalleg
endif

CC       := g++
TARGET   := exec
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
CFLAGS   := -std=c++11 -g -Wall -Wextra -fpermissive
LIBS     := -L/usr/lib -lm -lfmod $(LALLEG)
INCLUDE  := -I/usr/include/ -I/usr/include/fmod/
SRC      :=                      \
	$(wildcard *.cpp)              \
	$(wildcard utils/coord.cpp)   #\
	#$(wildcard src/module1/*.cpp) \
	#$(wildcard src/module2/*.cpp)


OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(LIBS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LIBS)

.PHONY: all build debug release clean mrproper

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CFLAGS += -DDEBUG -Werror
debug: all

release: CFLAGS += -O2
release: all

clean:
	@rm -rvf $(OBJ_DIR)

mrproper: clean
	@rm -rvf $(BUILD)
