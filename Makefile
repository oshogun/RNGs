CPPC = g++
DEBUG_FLAGS = -g -D _DEBUG
CPPFLAGS = -std=c++17 -Iinclude -Wall -Wextra  -Wstrict-aliasing -pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy\
 -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
 -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option\
 -O3 -fopenmp 

all: xorshift_release

debug: xorshift_debug 

xorshift_debug:
	mkdir -p bin
	${CPPC} src/xorshift32.cpp -o bin/xorshift ${DEBUG_FLAGS}\
	 ${CPPFLAGS} 

xorshift_release:
	mkdir -p bin
	${CPPC} src/xorshift32.cpp -o bin/xorshift ${CPPFLAGS} 



clean:
	rm bin/*