# CC = ~/code/buildroot/output/host/bin/arm-linux-gcc
# CC = ${{ github.workspace }}/toolchain/bin/arm-linux-gcc
# CC = arm-linux-gcc
CC = ../toolchain/host/bin/arm-linux-gcc
CFLAGS = -Wall -O2 -g -I./src
LDFLAGS = -pthread

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

CAMERA_SRC = $(SRC_DIR)/camera.c
ANALYSIS_SRC = $(SRC_DIR)/frame_analysis.c
TEST_CAMERA_SRC = $(SRC_DIR)/test_camera.c
TEST_ANALYSIS_SRC = $(SRC_DIR)/test_analysis.c

CAMERA_OBJ = $(BUILD_DIR)/camera.o
ANALYSIS_OBJ = $(BUILD_DIR)/frame_analysis.o
TEST_CAMERA_OBJ = $(BUILD_DIR)/test_camera.o
TEST_ANALYSIS_OBJ = $(BUILD_DIR)/test_analysis.o

EXECUTABLES = \
    $(BIN_DIR)/camera_mock \
    $(BIN_DIR)/frame_analysis \
    $(BIN_DIR)/test_camera \
    $(BIN_DIR)/test_analysis

all: $(BUILD_DIR) $(BIN_DIR) $(EXECUTABLES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Binaries
$(BIN_DIR)/camera_mock: $(CAMERA_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/frame_analysis: $(ANALYSIS_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/test_camera: $(TEST_CAMERA_OBJ) $(CAMERA_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/test_analysis: $(TEST_ANALYSIS_OBJ) $(ANALYSIS_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

# Compilation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Explicit dependencies (optional but clear)
$(CAMERA_OBJ): $(SRC_DIR)/camera.c $(SRC_DIR)/camera.h $(SRC_DIR)/frame.h $(SRC_DIR)/config.h
$(ANALYSIS_OBJ): $(SRC_DIR)/frame_analysis.c $(SRC_DIR)/frame_analysis.h $(SRC_DIR)/frame.h $(SRC_DIR)/config.h
$(TEST_CAMERA_OBJ): $(SRC_DIR)/test_camera.c $(SRC_DIR)/camera.h $(SRC_DIR)/frame.h
$(TEST_ANALYSIS_OBJ): $(SRC_DIR)/test_analysis.c $(SRC_DIR)/frame_analysis.h $(SRC_DIR)/frame.h

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
