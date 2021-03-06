MODULE_PATH := .
BIN_PATH := $(MODULE_PATH)/scripts
TARGET := $(BIN_PATH)/scene_detect
INC_PATH := $(MODULE_PATH)/inc

all: $(TARGET)

CCFLAGS :=  -g -std=c++11
CC := g++

INCLUDE_DIRS :=  -I $(INC_PATH) \
	-I /usr/local/cuda \
	`pkg-config opencv4 --cflags --libs` \
	-lcuda \

SRCS := ContentDetector.cpp SceneDetect.cpp main.cpp
SRC_DIR := $(MODULE_PATH)/src
SRCS_P := $(patsubst %, $(SRC_DIR)/%, $(SRCS))

$(TARGET) :
	@mkdir -p $(BIN_PATH)
	$(CC) $(SRCS_P) $(INCLUDE_DIRS) -o $(TARGET)  $(CCFLAGS)

clean:
	rm -rf $(TARGET)

