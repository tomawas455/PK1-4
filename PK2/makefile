additionalUtilities=src/additionalUtilities.h src/additionalUtilities.c
gameHelpers=src/gameHelpers.h src/gameHelpers.c
initialize=src/initializeGame.h src/initializeGame.c
mainMenu=src/mainMenu.h src/mainMenu.c
playGame=src/playGame.h src/playGame.c

wheel:src/structures.h $(additionalUtilities) $(gameHelpers) $(initialize) $(mainMenu) $(playGame) src/main.c
	gcc -std=c11 -o $@ $^

clean:
	if [ -f wheel ]; then rm wheel;fi;
