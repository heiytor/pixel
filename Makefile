CC     := g++
CFLAGS := -Wall -Wextra
CSTD   := -std=c++17

OBJDIR := obj
TARGET := pixel

SRCDIRS := ./src/ ./src/**/
INCDIRS := ./src/ ./libs/
LIBNAME := SDL2 SDL2_image SDL2_ttf SDL2_mixer lua5.4

INCS := $(foreach  D,     $(INCDIRS),    -I$(D))
LIBS := $(foreach  L,     $(LIBNAME),    -l$(L))
SRCS := $(foreach  D,     $(SRCDIRS),    $(wildcard $(D)/*.cpp))
OBJS := $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS := $(patsubst %.cpp, $(OBJDIR)/%.d, $(SRCS))

.PHONY: all build run clean

all: build

-include $(DEPS)
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CSTD) $(INCS) -MMD -c $< -o $@

build: $(OBJS)
	$(CC) $(CFLAGS) $(CSTD) $(INCS) $(LIBS) $^ -o $(TARGET) 

run: build
	./$(TARGET)

clean:
	rm -rvf $(OBJDIR) $(TARGET)
