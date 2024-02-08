CFLAGS ?= -Wall -std=c++14
.PHONY: es1 es2 es3 clean zip

es1: 
	g++ $(CFLAGS) es1.cpp
	./a.out

es2: 
	g++ $(CFLAGS) es2.cpp
	./a.out

es3: 
	g++ $(CFLAGS) es3.cpp
	./a.out

clean:
	rm -f *.out
	rm -f *.zip

zip: clean
	zip -r $(N).zip *