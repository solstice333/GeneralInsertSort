CC=gcc
FILES=GeneralInsertSort.c
OUT=a.out

all: build

build: $(FILES)
	$(CC) $(FILES)

clean:
	rm $(OUT)

rebuild: clean build
