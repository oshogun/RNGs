CPPC = g++
DEBUG_FLAGS = -g -D _DEBUG
CPPFLAGS = -std=c++17 -Iinclude -Wall -Wextra  -Wstrict-aliasing -pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy\
 -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
 -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option\
 -O3 -fopenmp 

 FILES = src/xorshift32.cpp src/xorshift64.cpp src/xorshift128.cpp\
 src/cmwc.cpp src/prime_gen.cpp src/main.cpp

all: release

debug:
	mkdir -p bin
	${CPPC} ${FILES} -o bin/rng ${DEBUG_FLAGS}\
	 ${CPPFLAGS} 

release:
	mkdir -p bin
	${CPPC} ${FILES} -o bin/rng ${CPPFLAGS} 



clean:
	rm bin/*