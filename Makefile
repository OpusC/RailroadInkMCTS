CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -pthread

SRCS = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
MAIN = src/main.cpp
TESTS = $(wildcard tests/*.cpp)

BUILD_DIR = build
TARGET = $(BUILD_DIR)/app
TEST_TARGET = $(BUILD_DIR)/runTests
COVERAGE_TARGET = $(BUILD_DIR)/runTests_coverage
COVERAGE_DIR = $(BUILD_DIR)/coverage

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRCS) $(MAIN) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(SRCS) $(TESTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -O2 -o $@ $^ -lgtest -lgtest_main

$(COVERAGE_TARGET): $(SRCS) $(TESTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) --coverage -o $@ $^ -lgtest -lgtest_main

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET) $(ARGS)

coverage: $(COVERAGE_TARGET)
	mkdir -p $(COVERAGE_DIR)
	./$(COVERAGE_TARGET)
	lcov --capture --directory . --output-file $(COVERAGE_DIR)/coverage.info \
		--exclude '*/tests/*' --exclude '/usr/*'
	genhtml $(COVERAGE_DIR)/coverage.info --output-directory $(COVERAGE_DIR)/html
	@echo "Coverage report: $(COVERAGE_DIR)/html/index.html"

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run test coverage clean

