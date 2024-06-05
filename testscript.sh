#!/bin/bash
printf "*****pgmEcho: ASCII -> ASCII*****\n"
./pgmEcho ./img/testEcho.pgm ./img/testEcho2.pgm
printf "\n"
printf "*****pgmEcho: BINARY -> BINARY*****\n\n"
./pgmEcho ./img/testEchoBin.pgm ./img/testEchoBin2.pgm
printf "\n"
printf "*****pgmComp: ASCII -> ASCII*****\n"
./pgmComp ./img/testEcho.pgm ./img/testEcho2.pgm
printf "\n"
printf "*****pgmComp: BINARY -> BINARY*****\n"
./pgmComp ./img/testEchoBin.pgm ./img/testEchoBin2.pgm
printf "\n"
printf "*****pgmComp: ASCII -> BINARY*****\n"
./pgmComp ./img/testEcho.pgm ./img/testEchoBin.pgm
printf "\n"
printf "*****pgmComp: BINARY -> ASCII*****\n\n"
./pgmComp ./img/testEchoBin.pgm ./img/testEcho.pgm
printf "\n"
printf "*****pgma2b*****\n\n"
./pgma2b ./img/ascii2Bin.pgm ./img/bin1.pgm
printf "\n"
printf "*****pgmb2a*****\n\n"
./pgmb2a ./img/bin2ascii.pgm ./img/asc1.pgm
printf "\n"
printf "*****pgmReduce: Factor = 2*****\n"
./pgmReduce ./img/notRed.pgm 2 ./img/red2.pgm
printf "\n"
printf "*****pgmReduce: Factor = 3*****\n\n"
./pgmReduce ./img/notRed.pgm 3 ./img/red3.pgm
printf "\n"
printf "*****pgmTile: Factor = 2*****\n"
./pgmTile ./img/testTile6.pgm 2 "./img/testTile6_<row>_<column>.pgm"
printf "\n"
printf "*****pgmTile: Factor = 3*****\n"
./pgmTile ./img/testTile9.pgm 3 "./img/testTile9_<row>_<column>.pgm"
printf "\n"
printf "*****pgmTile: Factor = 4*****\n"
./pgmTile ./img/testTile8.pgm 4 "./img/testTile8_<row>_<column>.pgm"
printf "\n"