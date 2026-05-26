game: main.o util.o
	g++ main.o util.o -o game

main.o:
	g++ -c main.cpp

util.o:
	g++ -c util.cpp

run: game
	./game

clean:
	rm main.o util.o game