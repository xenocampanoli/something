# Custom Makefile for Preprocessor Generic Sort Algorithm Exercises.

DEBUG = -g
#DEBUG =

HEADERS = /usr/local/include ../env.h itemtype.h sppsorts.h

PPITEMTYPE = -D__INT_ITEMTYPE
#PPITEMTYPE = -D__PERSON_ITEMTYPE

PPLISTTYPE = -D__ARRAYLIST
#PPLISTTYPE = -D__LINKEDLIST

PPMACROS = $(PPITEMTYPE) $(PPLISTTYPE)

SORTTYPES = external heap insertion merge

SORTNAMES = $(patsubst %,%sort,$(SORTTYPES))

SORTOBJECTS = $(patsubst %,%.o,$(SORTNAMES))

SORTTESTS = $(patsubst %,%Tests,$(SORTNAMES))

SORTTESTOBJECTS = $(patsubst %,%.o,$(SORTTESTS))


itemtype.o:	itemtype.c $(HEADERS)
	$(CC) $(DEBUG) $(PPMACROS) -c $(CFLAGS) $< -o $@
	
itemtypeTests.o:  itemtypeTests.c $(HEADERS)
	$(CC) $(DEBUG) $(PPMACROS) -c $(CFLAGS) $< -o $@
	
itemtypeTests: itemtype.o itemtypeTests.o
	$(CC) -o $@ $^ $(CFLAGS) -lcriterion
	
$(SORTOBJECTS): %.o: %.c $(HEADERS)
	$(CC) $(DEBUG) $(PPMACROS) -c $(CFLAGS) $< -o $@

$(SORTTESTOBJECTS): %.o: %.c $(HEADERS)
	$(CC) $(DEBUG) $(PPMACROS) -c $(CFLAGS) $< -o $@

$(SORTTESTS): %Tests: %Tests.o %.o itemtype.o $(SORTOBJECTS)
	$(CC) -fdata-sections -ffunction-sections -o $@ $^ $(CFLAGS) -lcriterion


ssorts.o: ssorts.c $(HEADERS)
	$(CC) $(DEBUG) $(PPMACROS) -c $(CFLAGS) $< -o $@

ssorts: itemtype.o $(SORTOBJECTS) ssorts.o
	$(CC) -o $@ $^ $(CFLAGS)
	

all:  ssorts $(SORTTESTS) itemtypeTests

clean:
	-rm -f mess*
	-rm -f *.o
	-rm -f outdata/*
	-rm -f ssorts itemtypeTests $(SORTTESTS)


