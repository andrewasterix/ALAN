CFLAGS ?= -Wall -std=c++14
.PHONY: es1 es2 es3 clean zip

labo: 
	g++ $(CFLAGS) labo.cpp
	./a.out

clean:
	rm -f *.out
	rm -f *.zip

zip: clean
	zip -r $(N).zip *