CXX ?= g++

CXXFLAGS := -std=c++20 -Wall -Wextra -O2

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
PLOT_DIR := plots

SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

TARGET := $(BUILD_DIR)/interpolation

.PHONY: all clean help run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -I$(INC_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INC_DIR)

$(BUILD_DIR)/main.o: main.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< -I$(INC_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(PLOT_DIR):
	mkdir -p $(PLOT_DIR)
	mkdir -p $(PLOT_DIR)/data
	mkdir -p $(PLOT_DIR)/images

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET) | $(PLOT_DIR)
	@echo "Generating plots..."
	@$(TARGET)
	@gnuplot $(PLOT_DIR)/data/*.gp
	@echo "Plots generated."

help:
	@echo "Usage:"
	@echo "  make         # Build the project"
	@echo "  make run     # Build and run the project, generate plots as PNG files in $(PLOT_DIR)/images"
	@echo "  make clean   # Remove build artifacts, plots, and temporary files"
	@echo "  make help    # Show this help message"
	@echo ""
	@echo "Current settings:"
	@echo "  CXX        = $(CXX)"
	@echo "  CXXFLAGS   = $(CXXFLAGS)"

print-%:
	@echo $* = $($*)
