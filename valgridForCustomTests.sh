make

valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/shouldTerminate1.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/shouldTerminate2.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/lastJoinPolicy1.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/mandatesJoinPolicy2.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/mandatesJoinPolicy3.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/EdgeSelectionPolicy1.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/EdgeSelectionPolicy2.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/MandatesSelectionPolicy1.json
valgrind --leak-check=full --show-reachable=yes bin/cRace customTests/MandatesSelectionPolicy2.json


#valgrind --leak-check=full --show-reachable=yes ./bin/cRace ./tests/02.json 