INCLUDEPATH = -I./ext/include
LIBPATH = -L./ext/lib

INTDIR = ./int
OUTDIR = ./bin

.PHONY: clean

clean:
	rm ./int/*.o && rm ./bin/*
