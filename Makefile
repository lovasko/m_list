CC=clang
CFLAGS=-g -fPIC -Isrc -ansi -pedantic -Wall -Wextra -Weverything
LDFLAGS= 
SRC=../src
EXECUTABLE=libmlist.so
OBJECTS=      \
  access.o    \
  elem.o      \
  general.o   \
  index.o     \
  insert.o    \
  remove.o    \
  filter.o    \
  find.o      \
  join.o      \
  map.o       \
  reverse.o   \
  sort.o      \
  zip.o       \
  equal.o     \
  match.o     \
  is_sorted.o \
  is_empty.o

all: libmlist.so

libmlist.so: $(OBJECTS)
	$(CC) -fPIC -o libmlist.so -shared $(OBJECTS) $(LDFLAGS)

clean:
	rm *.o libmlist.so 

access.o: $(SRC)/access.c
	$(CC) $(CFLAGS) -c $(SRC)/access.c -o access.o

elem.o: $(SRC)/elem.c
	$(CC) $(CFLAGS) -c $(SRC)/elem.c -o elem.o

general.o: $(SRC)/general.c
	$(CC) $(CFLAGS) -c $(SRC)/general.c -o general.o

index.o: $(SRC)/index.c
	$(CC) $(CFLAGS) -c $(SRC)/index.c -o index.o

insert.o: $(SRC)/insert.c
	$(CC) $(CFLAGS) -c $(SRC)/insert.c -o insert.o

remove.o: $(SRC)/remove.c
	$(CC) $(CFLAGS) -c $(SRC)/remove.c -o remove.o

filter.o: $(SRC)/algorithm/filter.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/filter.c -o filter.o

find.o: $(SRC)/algorithm/find.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/find.c -o find.o

join.o: $(SRC)/algorithm/join.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/join.c -o join.o

map.o: $(SRC)/algorithm/map.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/map.c -o map.o

reverse.o: $(SRC)/algorithm/reverse.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/reverse.c -o reverse.o

sort.o: $(SRC)/algorithm/sort.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/sort.c -o sort.o

zip.o: $(SRC)/algorithm/zip.c
	$(CC) $(CFLAGS) -c $(SRC)/algorithm/zip.c -o zip.o

equal.o: $(SRC)/predicate/equal.c
	$(CC) $(CFLAGS) -c $(SRC)/predicate/equal.c -o equal.o

match.o: $(SRC)/predicate/match.c
	$(CC) $(CFLAGS) -c $(SRC)/predicate/match.c -o match.o

is_sorted.o: $(SRC)/predicate/is_sorted.c
	$(CC) $(CFLAGS) -c $(SRC)/predicate/is_sorted.c -o is_sorted.o

is_empty.o: $(SRC)/predicate/is_empty.c
	$(CC) $(CFLAGS) -c $(SRC)/predicate/is_empty.c -o is_empty.o

