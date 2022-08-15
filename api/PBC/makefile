test: Extract-Partial-Private-Key.c
	gcc -o test Extract-Partial-Private-Key.c setup.c -lpbc -lgmp -lcrypto
clean:
	-rm -rf test pairing_params.txt
#playground: Makefile playground.c
#	gcc playground.c -lpbc -lgmp -o playground