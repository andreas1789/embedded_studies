#!/bin/zsh

TARGET = stm32f103c8t6_app

BUILD_DIR = ../gen_app

CPPSOURCES = $(wildcard src/*.cpp)
CPPBASESOURCES = $(wildcard ../base/src/*.cpp)
HEADERS = include/
BASEHEADERS = ../base/include/
ASMSOURCES = $(wildcard src/*.s)
BASEOBJECTS = $(patsubst ../base/src/%.cpp, $(BUILD_DIR)/%.o, $(CPPBASESOURCES))
OBJECTS = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(CPPSOURCES)) $(patsubst src/%.s, $(BUILD_DIR)/%.o, $(ASMSOURCES))
LDFILE = $(wildcard src/*.ld)

CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
LD = arm-none-eabi-ld

CPU = cortex-m3
INSTRUCTION_SET = thumb

CFLAGS = -Os -g -mcpu=$(CPU) -m$(INSTRUCTION_SET)

CXXFLAGS :=$(CFLAGS) -fno-exceptions -fno-rtti 
CXXFLAGS += -nostdlib -fno-tree-loop-distribute-patterns -fdata-sections -ffunction-sections -fno-use-cxa-atexit
CXXFLAGS += -Wall -Wextra -Wundef -Wshadow -Wredundant-decls -Weffc++ -Werror

LDFLAGS	= -T $(LDFILE)
LDFLAGS	+= -Map=$(BUILD_DIR)/$(TARGET).map

build: elf hex bin
	@printf "\nsuccess\n"

flash: build
	@printf "\nflashing the target\n"
	openocd -f config/openocd.cfg

debug: build
	@printf "\nflashing the target in debug mode\n"
	openocd -f config/openocd_debug.cfg

elf: $(OBJECTS) $(BASEOBJECTS)
	@printf "\nlinking the elf file $^\n"
	$(LD) $(LDFLAGS) -o $(BUILD_DIR)/$(TARGET).elf $^ 

bin:
	@printf "\ngenerating binary\n"
	arm-none-eabi-objcopy -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin

hex:
	@printf "\ngenerating hex file\n"
	arm-none-eabi-objcopy -O ihex $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex

$(BUILD_DIR)/%.o:src/%.cpp | $(BUILD_DIR)
	@printf "\ncompiling $<\n"
	$(CXX) -c $(CXXFLAGS) -I $(HEADERS) $< -o $@

$(BUILD_DIR)/%.o:../base/src/%.cpp | $(BUILD_DIR)
	@printf "\ncompiling $<\n"
	$(CXX) -c $(CXXFLAGS) -I $(BASEHEADERS) $< -o $@
	
$(BUILD_DIR)/%.o:src/%.s | $(BUILD_DIR)
	@printf "\ncompiling $<\n"
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BUILD_DIR):
	@printf "\ncreating $(BUILD_DIR) directory $<\n"
	mkdir $@

.PHONY: clean
clean:
	@printf "\nremoving $(BUILD_DIR) directory $<\n"
	rm -f -R $(BUILD_DIR)

.PHONY: objdump
objdump: elf
	arm-none-eabi-objdump -h $(BUILD_DIR)/$(TARGET).elf 
