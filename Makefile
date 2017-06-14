MenuManager : menuManager.c
	g++ menuManager.c -o menuManager -l sqlite3 -lglpk `python-config --ldflags`

all :
	g++ menuManager.c -o menuManager -l sqlite3 -lglpk `python-config --ldflags`

clean :
	rm menuManager
