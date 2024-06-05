pgmEcho: ./pgmEcho.c ./pgmWrite.c ./initImage.c ./pgmRead.c ./pgmRead.h ./pgmWrite.h ./initImage.h
	gcc -std=c99 ./pgmEcho.c  -o pgmEcho 
pgmComp: ./pgmComp.c ./pgmRead.c ./pgmRead.h ./initImage.h
	gcc -std=c99 ./pgmComp.c -o  pgmComp 
pgma2b:  ./pgma2b.c ./pgmWrite.c ./initImage.c ./pgmRead.c ./pgmRead.h ./pgmWrite.h ./initImage.h
	gcc -std=c99 ./pgma2b.c -o pgma2b 
pgmb2a:  ./pgmb2a.c ./initImage.c ./pgmRead.c ./pgmRead.h ./initImage.h
	gcc -std=c99 ./pgmb2a.c -o pgmb2a 
pgmReduce: ./pgmReduce.c ./initImage.c ./pgmRead.c ./pgmRead.h ./initImage.h
	gcc -std=c99 ./pgmReduce.c -g -o pgmReduce
pgmTile: ./pgmTile.c ./pgmWrite.c ./initImage.c ./pgmRead.c ./pgmRead.h ./pgmWrite.h ./initImage.h ./macros.h ./structs.h
	gcc -std=c99 ./pgmTile.c  -o pgmTile
pgmAssemble: ./pgmAssemble.c ./pgmWrite.c ./initImage.c ./pgmRead.c ./pgmRead.h ./pgmWrite.h ./initImage.h
	gcc -std=c99 ./pgmAssemble.c  -o pgmAssemble 
all: pgmReduce pgmTile pgmEcho pgmComp pgma2b pgmb2a pgmAssemble
clean:
	rm pgmTile pgmReduce pgmEcho pgmComp pgma2b pgmb2a  pgmAssemble


