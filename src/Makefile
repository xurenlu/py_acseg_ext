#when install the cgi, you should set a proper path where you want to intall.

OBJECTS = acseg_util.o acseg_rbtree.o acseg_tree.o mem_collector.o test.o

all:test

$(OBJECTS):acseg_util.h acseg_rbtree.h acseg_tree.h mem_collector.h uchar.h

test: $(OBJECTS)
	gcc -O1 -o test $(OBJECTS)

.PHONY: clean
clean: 
	-rm -rf  test *.o 
