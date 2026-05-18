NAME = aoe2

CXX = c++
RAYLIB_PATH = ./raylib

CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -g -MMD -MP \
	-I$(RAYLIB_PATH)/src \
	-I./Renderer \
	-I./Systems \
	-I./World 

LDFLAGS = \
	$(RAYLIB_PATH)/build/raylib/libraylib.a \
	-lGL -lm -lpthread -ldl -lrt -lX11
BUILD_DIR = build

# Find all cpp files recursively
SRCS := $(shell find . \
	-path ./build -prune -o \
	-path ./raylib -prune -o \
	-type f -name "*.cpp" -print)

# Convert:
# src/foo.cpp -> build/src/foo.o
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

# Compile rule
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Run:
# make valgrind ARGS="file.txt"
valgrind: $(NAME)
	valgrind \
		--leak-check=full \
		--track-origins=yes \
		--show-leak-kinds=all \
		./$(NAME) $(ARGS)

# Include generated dependency files
-include $(DEPS)

.PHONY: all clean fclean re valgrind