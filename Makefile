reverse-game:
	g++ -o result main.cpp

run: reverse-game
	./result

clean:
	rm -f result
