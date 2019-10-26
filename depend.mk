main.o: main.cpp easybj.h config.h player.h shoe.h hand.h
shoe.o: shoe.cpp shoe.h config.h
strategy.o: strategy.cpp
config.o: config.cpp config.h player.h shoe.h
player.o: player.cpp player.h hand.h easybj.h shoe.h config.h
hand.o: hand.cpp shoe.h easybj.h player.h hand.h
easybj.o: easybj.cpp shoe.h easybj.h player.h hand.h
