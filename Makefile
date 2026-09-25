.PHONY: build

build:
	gcc src/*.c -o build/doc -lncursesw
clean:
	rm build/doc
run:
	gcc src/*.c -o build/doc -lncursesw
	build/doc
