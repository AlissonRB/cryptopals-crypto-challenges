CXX = g++
CXXFLAGS = -std=c++11 -Wall
EXECUTABLES = challenge01 challenge02 challenge03 challenge04
SRC_DIR = src

all: $(EXECUTABLES)

%: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -f $(EXECUTABLES)
