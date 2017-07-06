MenuManager : menuManager.c
	g++ -std=c++11 menuManager.c -o menuManager -l sqlite3 -lglpk `python-config --ldflags`

all :
	g++ -std=c++11 menuManager.c -o menuManager -l sqlite3 -lglpk `python-config --ldflags`

clean :
	rm menuManager
