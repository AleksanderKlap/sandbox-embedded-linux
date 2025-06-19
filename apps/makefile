CC = ~/code/buildroot/output/host/bin/arm-linux-gcc
# CC = ${{ github.workspace }}/toolchain/bin/arm-linux-gcc
# CC = arm-linux-gcc
# CC = ../toolchain/host/bin/arm-linux-gcc
CFLAGS = -Wall -O2 -g -I./src
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

EXECUTABLES = \
    $(BIN_DIR)/camera_mock \
    $(BIN_DIR)/frame_analysis \

all: $(BUILD_DIR) $(BIN_DIR) $(EXECUTABLES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Binaries
$(BIN_DIR)/camera_mock: $(BUILD_DIR)/camera.o $(BUILD_DIR)/test_camera.o
	$(CC) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/frame_analysis: $(BUILD_DIR)/frame_analysis.o $(BUILD_DIR)/test_analysis.o
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/camera.o: $(SRC_DIR)/camera.c $(SRC_DIR)/camera.h $(SRC_DIR)/frame.h $(SRC_DIR)/config.h
$(BUILD_DIR)/frame_analysis.o: $(SRC_DIR)/frame_analysis.c $(SRC_DIR)/frame_analysis.h $(SRC_DIR)/frame.h $(SRC_DIR)/config.h
$(BUILD_DIR)/test_camera.o: $(SRC_DIR)/test_camera.c $(SRC_DIR)/frame.h
$(BUILD_DIR)/test_analysis: $(SRC_DIR)/test_analysis.c $(SRC_DIR)/frame_analysis.h $(SRC_DIR)/frame.h

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean

