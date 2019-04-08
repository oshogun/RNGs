CC = gcc
CFLAGS = -v -std=c11 -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes \
    -Wold-style-definition -O3

CPPC = g++
DEBUG_FLAGS = -g -D _DEBUG
CPPFLAGS = -v -std=c++17 -Wall -Wextra  -Wstrict-aliasing -pedantic -fmax-errors=5 -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy\
 -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow \
 -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option\
 -O3



all: xorshift_release caesar otp

debug: xorshift_debug 

caesar:
	${CC} ${CFLAGS} cyphers/caesar.c -o bin/caesar 

otp:
	${CC} ${CFLAGS} cyphers/otp.c -o bin/otp

xorshift_debug:
	${CPPC} xorshift/xorshift.cpp -o bin/xorshift ${DEBUG_FLAGS} ${CPPFLAGS}

xorshift_release:
	${CPPC} xorshift/xorshift.cpp -o bin/xorshift ${CPPFLAGS}

clean:
	rm bin/*