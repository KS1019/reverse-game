reversi-game:
	g++ -o result main.cpp

run: reversi-game
	./result

clean:
	rm -f result
