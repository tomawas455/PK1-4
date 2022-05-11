standard=-std=c++11
executableName=boulder
sfmlPath=./SFML

labels=src/labels.h src/labels.cpp
menu=src/mainMenu.h src/mainMenu.cpp
tiles=src/tiles.h src/tiles.cpp
player=src/player.h src/player.cpp
texturesContainer=src/texturesContainer.h src/texturesContainer.cpp
statusbar=src/statusbar.h src/statusbar.cpp
gameOver=src/gameOver.h src/gameOver.cpp
game=src/game.h src/game.cpp

$(executableName): src/main.cpp src/constants.h $(labels) $(menu) $(tiles) $(player) $(texturesContainer) $(statusbar) $(gameOver) $(game)
	g++ -std=c++11 -I$(sfmlPath)/include -o $@ -L$(sfmlPath)/lib -lsfml-graphics -lsfml-window -lsfml-system $^
	echo "to run: "'LD_LIBRARY_PATH=$(sfmlPath)/lib ./$(executableName)'

clean:
	rm -r $(executableName)
