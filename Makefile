build-run:
	clang++ -std=c++2a ./src/*.cpp -o out -l sqlite3 && ./out

build:
	clang++ -std=c++2a ./src/*.cpp -o out -l sqlite3

run:
	./out