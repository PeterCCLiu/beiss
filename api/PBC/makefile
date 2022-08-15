test: Extract-Partial-Private-Key.c
	gcc -o test Extract-Partial-Private-Key.c setup.c -lpbc -lgmp -lcrypto
clean:
	-rm -rf test pairing_params.txt
#playground: Makefile playground.c
#	gcc playground.c -lpbc -lgmp -o playground
adder: adder.c
	clang --target=wasm32 -nostdlib -Wl --no-entry -o adder.wasm adder.c