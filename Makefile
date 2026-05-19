NAME = aoe2

CXX = c++
RAYLIB_PATH = ./raylib

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -g -MMD -MP \
	-I$(RAYLIB_PATH)/src \
	-I./Renderer \
	-I./Systems \
	-I./World

BUILD_DIR = build

# ---- Submodule setup marker ----
SUBMODULE_MARKER := .submodules_ok

# ---- Raylib build ----
RAYLIB_BUILD_DIR = $(RAYLIB_PATH)/build
RAYLIB_LIB = $(RAYLIB_BUILD_DIR)/raylib/libraylib.a

# ---- Source files ----
SRCS := $(shell find . \
	-path ./build -prune -o \
	-path ./raylib -prune -o \
	-type f -name "*.cpp" -print)

OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ---- Default target ----
all: $(NAME)

# ---- Ensure submodules exist (runs once) ----
$(SUBMODULE_MARKER):
	git submodule update --init --recursive
	@touch $(SUBMODULE_MARKER)

# ---- Build raylib only if missing ----
$(RAYLIB_LIB): $(SUBMODULE_MARKER)
	@if [ ! -f "$(RAYLIB_LIB)" ]; then \
		echo "Building raylib..."; \
		mkdir -p $(RAYLIB_BUILD_DIR); \
		cmake -S $(RAYLIB_PATH) -B $(RAYLIB_BUILD_DIR); \
		cmake --build $(RAYLIB_BUILD_DIR); \
	else \
		echo "raylib already built"; \
	fi

# ---- Build final binary ----
$(NAME): $(RAYLIB_LIB) $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(RAYLIB_LIB) \
		-lGL -lm -lpthread -ldl -lrt -lX11

# ---- Compile rule ----
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- Cleanup ----
clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(SUBMODULE_MARKER)

# ---- Full dependency rebuild (optional) ----
distclean: fclean
	rm -rf $(RAYLIB_BUILD_DIR)

re: fclean all

# ---- Run valgrind ----
valgrind: $(NAME)
	valgrind \
		--leak-check=full \
		--track-origins=yes \
		--show-leak-kinds=all \
		./$(NAME) $(ARGS)

# ---- Dependencies ----
-include $(DEPS)

.PHONY: all clean fclean re distclean valgrind