standard=-std=c++11
executableName=shooter
sfmlPath=./SFML

additionalUtilities=src/additionalUtilities.h src/additionalUtilities.cpp
gameElementAction=src/gameElementAction.h src/gameElementAction.cpp
labels=src/labels.h src/labels.cpp
menu=src/mainMenu.h src/mainMenu.cpp
enemies=src/enemies.h src/enemies.cpp
bullets=src/bullets.h src/bullets.cpp
player=src/player.h src/player.cpp
dataManager=src/dataManager.h src/dataManager.cpp
collisionsManager=src/collisionsManager.h src/collisionsManager.cpp
enemyData=src/enemyData.h src/enemyData.cpp
sidebar=src/sidebar.h src/sidebar.cpp
spawner=src/spawner.h src/spawner.cpp
bulletsTypesCreator=src/bulletsTypesCreator.h src/bulletsTypesCreator.cpp
powerUps=src/powerUps.h src/powerUps.cpp
powerUpsData=src/powerUpsData.h src/powerUpsData.cpp
gameOver=src/gameOver.h src/gameOver.cpp
game=src/game.h src/game.cpp

$(executableName): src/json.hpp src/main.cpp src/constants.h $(gameElementAction) $(bulletsTypesCreator) $(additionalUtilities) $(labels) $(menu) $(enemies) $(bullets) $(player) $(powerUps) $(powerUpsData) $(enemyData) $(dataManager) $(collisionsManager) $(sidebar) $(spawner) $(gameOver) $(game)
	g++ -std=c++17 -o $@ -I$(sfmlPath)/include -L$(sfmlPath)/lib -lsfml-graphics -lsfml-window -lsfml-system $^
	echo "to run: "'LD_LIBRARY_PATH=$(sfmlPath)/lib ./$(executableName)'

clean:
	rm -r $(executableName)
