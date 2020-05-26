MODULE_PATH := ./
BIN_PATH := scripts
TARGET := $(BIN_PATH)/scene_detect
INC_PATH := $(MODULE_PATH)/lib

all: $(TARGET)

CCFLAGS :=  -g -std=c++11
CC := g++

INCLUDE_DIRS := \
	-I/usr/local/include/opencv4/ \
	-I $(INC_PATH) \
	-lopencv_core \
	-lpthread \
	-lz\
	-ldl \
	-lcudart \
	-lopencv_highgui\
	-lopencv_videoio\
	-lopencv_cudaarithm \
	-lopencv_cudacodec \
	-lopencv_cudaimgproc \
	-lcuda \

SRCS := ContentDetector.cpp SceneDetect.cpp main.cpp
SRC_DIR := $(MODULE_PATH)/src
SRCS_P := $(patsubst %, $(SRC_DIR)/%, $(SRCS))

$(TARGET) :
	@mkdir -p $(BIN_PATH)
	$(CC) $(SRCS_P) $(INCLUDE_DIRS) -o $(TARGET)  $(CCFLAGS)

clean:
	rm -rf $(TARGET)

