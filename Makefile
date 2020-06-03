# Makefile inspired by tutorials from David Bernhauer and Ladislav Vagner (FIT CTU)

TARGET = batekto2
CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++17 -DPNG_SETJMP_NOT_SUPPORTED
SANITIZER_FLAG = -g -fsanitize=address
LD = g++

# Operating system name:
UNAME_S := $(shell uname -s)

# Linker for macOS:
ifeq ($(UNAME_S), Darwin)
LD_FLAGS = -Wall -pedantic -Wextra -std=c++17 -lpng -ljpeg
# Linker for other (is meant for Linux):
else
LD_FLAGS = -Wall -pedantic -Wextra -std=c++17 -lpng -ljpeg -lstdc++fs
endif

BUILD_DIR = build
SANITIZER_DIR = sanitize

.PHONY: all
all: compile

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/AnimatorController.o $(BUILD_DIR)/Application.o $(BUILD_DIR)/Command.o $(BUILD_DIR)/Controller.o $(BUILD_DIR)/ConverterController.o $(BUILD_DIR)/EditorController.o $(BUILD_DIR)/Image.o $(BUILD_DIR)/ImageASCII.o $(BUILD_DIR)/ImageJPG.o $(BUILD_DIR)/ImagePNG.o $(BUILD_DIR)/ImageRGB.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/StartController.o
	$(LD) $^ -o $@ $(LD_FLAGS)

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ $(SANITIZER_DIR)/ examples/converted/ sanitizer 2>/dev/null

# Debug:
.PHONY: sanitize
sanitize: sanitizer
	./sanitizer

.PHONY: sanitizer
sanitizer: $(SANITIZER_DIR)/main.o $(SANITIZER_DIR)/AnimatorController.o $(SANITIZER_DIR)/Application.o $(SANITIZER_DIR)/Command.o $(SANITIZER_DIR)/Controller.o $(SANITIZER_DIR)/ConverterController.o $(SANITIZER_DIR)/EditorController.o $(SANITIZER_DIR)/Image.o $(SANITIZER_DIR)/ImageASCII.o $(SANITIZER_DIR)/ImageJPG.o $(SANITIZER_DIR)/ImagePNG.o $(SANITIZER_DIR)/ImageRGB.o $(SANITIZER_DIR)/Interface.o $(SANITIZER_DIR)/StartController.o
	$(LD) $^ -o $@ $(LD_FLAGS) $(SANITIZER_FLAG)

$(SANITIZER_DIR)/%.o: src/%.cpp
	mkdir -p $(SANITIZER_DIR)
	$(CXX) $(CXX_FLAGS) $(SANITIZER_FLAG) $< -c -o $@

# Only on macOS:
ifeq ($(UNAME_S), Darwin)
.PHONY: leaks
leaks: $(TARGET)
	leaks -atExit -- ./$(TARGET)
endif

# Only on Linux:
ifeq ($(UNAME_S), Linux)
.PHONY: valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)
endif




# Dependencies:
AnimatorController.o: src/AnimatorController.cpp \
  src/AnimatorController.hpp src/Controller.hpp src/Command.hpp \
  src/Interface.hpp
AnimatorController.o: src/AnimatorController.hpp src/Controller.hpp \
  src/Command.hpp src/Interface.hpp
Application.o: src/Application.cpp src/Application.hpp src/Interface.hpp \
  src/StartController.hpp src/Controller.hpp src/Command.hpp
Application.o: src/Application.hpp src/Interface.hpp \
  src/StartController.hpp src/Controller.hpp src/Command.hpp
Command.o: src/Command.cpp src/Command.hpp src/Interface.hpp
Command.o: src/Command.hpp src/Interface.hpp
Controller.o: src/Controller.cpp src/Controller.hpp src/Command.hpp \
  src/Interface.hpp
Controller.o: src/Controller.hpp src/Command.hpp src/Interface.hpp
ConverterController.o: src/ConverterController.cpp \
  /usr/local/include/png.h /usr/local/include/pnglibconf.h \
  /usr/local/include/pngconf.h /usr/local/include/jpeglib.h \
  /usr/local/include/jconfig.h /usr/local/include/jmorecfg.h \
  src/ConverterController.hpp src/Controller.hpp src/Command.hpp \
  src/Interface.hpp src/Image.hpp src/ImageASCII.hpp src/ImageRGB.hpp \
  src/ImageJPG.hpp src/ImagePNG.hpp
ConverterController.o: src/ConverterController.hpp src/Controller.hpp \
  src/Command.hpp src/Interface.hpp src/Image.hpp src/ImageASCII.hpp \
  src/ImageRGB.hpp
EditorController.o: src/EditorController.cpp src/EditorController.hpp \
  src/Controller.hpp src/Command.hpp src/Interface.hpp
EditorController.o: src/EditorController.hpp src/Controller.hpp \
  src/Command.hpp src/Interface.hpp
Image.o: src/Image.cpp src/Image.hpp src/ImageASCII.hpp src/ImageRGB.hpp
Image.o: src/Image.hpp src/ImageASCII.hpp src/ImageRGB.hpp
ImageASCII.o: src/ImageASCII.cpp src/ImageASCII.hpp
ImageASCII.o: src/ImageASCII.hpp
ImageJPG.o: src/ImageJPG.cpp src/ImageJPG.hpp src/Image.hpp \
  src/ImageASCII.hpp src/ImageRGB.hpp
ImageJPG.o: src/ImageJPG.hpp src/Image.hpp src/ImageASCII.hpp \
  src/ImageRGB.hpp
ImagePNG.o: src/ImagePNG.cpp /usr/local/include/png.h \
  /usr/local/include/pnglibconf.h /usr/local/include/pngconf.h \
  src/ImagePNG.hpp src/Image.hpp src/ImageASCII.hpp src/ImageRGB.hpp
ImagePNG.o: src/ImagePNG.hpp src/Image.hpp src/ImageASCII.hpp \
  src/ImageRGB.hpp
ImageRGB.o: src/ImageRGB.cpp src/ImageRGB.hpp src/ImageASCII.hpp
ImageRGB.o: src/ImageRGB.hpp src/ImageASCII.hpp
Interface.o: src/Interface.cpp src/Interface.hpp
Interface.o: src/Interface.hpp
StartController.o: src/StartController.cpp src/StartController.hpp \
  src/Controller.hpp src/Command.hpp src/Interface.hpp \
  src/ConverterController.hpp src/Image.hpp src/ImageASCII.hpp \
  src/ImageRGB.hpp src/AnimatorController.hpp src/EditorController.hpp
StartController.o: src/StartController.hpp src/Controller.hpp \
  src/Command.hpp src/Interface.hpp
main.o: src/main.cpp src/Application.hpp src/Interface.hpp \
  src/StartController.hpp src/Controller.hpp src/Command.hpp
