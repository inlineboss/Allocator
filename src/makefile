LDFLAGS = -std=c++17 -pthread -g0 -O3 -fpermissive -ftemplate-depth=750

all:
	g++ $(LDFLAGS) -D _GLIBCXX_DEBUG -D _GLIBCXX_DEBUG_PEDANTIC -I . -o bin main.cpp -fconcepts -lgcov