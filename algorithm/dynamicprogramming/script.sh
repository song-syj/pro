#! /bin/sh
cat prob.dat|while read line
do
	./a.out $line;
done
