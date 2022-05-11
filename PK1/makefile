commandlineParser=src/commandlineParser.h src/commandlineParser.cpp
additional=src/additionalUtilities.h src/additionalUtilities.cpp src/cableContainerManager.h src/cableContainerManager.cpp
builder=src/cableCreator.h src/cableCreator.cpp src/ioAdder.h src/ioAdder.cpp src/gateCreator.h src/gateCreator.cpp src/circuitBuilder.h src/circuitBuilder.cpp
checker=src/circuitChecker.h src/circuitChecker.cpp
calculator=src/circuitCalculator.h src/circuitCalculator.cpp
logic=src/gatesLogic.h src/gatesLogic.cpp
process=src/processCircuit.h src/processCircuit.cpp

tuc:$(commandlineParser) src/structures.h $(additional) $(builder) $(checker) $(calculator) $(logic) $(process) src/main.cpp
	g++ -std=c++11 -g -O3 -o $@ $^

clean:
	if [ -f tuc ];then rm tuc;fi;
