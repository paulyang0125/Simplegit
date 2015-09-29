CUNIT := -L/home/ff/cs61c/cunit/install/lib -I/home/ff/cs61c/cunit/install/include -lcunit

simplegit: main.c simplegit.c util.c simplegit.h util.h
	gcc -g -std=c99 main.c simplegit.c util.c -o simplegit

simplegit-unittest: main.c simplegit.c cunittests.c util.c simplegit.h util.h cunittests.h
	gcc -g -DTESTING -std=c99 main.c simplegit.c cunittests.c util.c -o simplegit-unittest $(CUNIT)

clean:
	rm -rf simplegit autotest test simplegit-unittest

check: simplegit
ifndef INSTMANPATH
	$(error You need to run 'make check' on an instructional machine, such as hive*.cs.berkeley.edu)
endif
	python2.7 tester.pyc simplegit.c
