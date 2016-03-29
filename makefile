INCDIR = ext/include
LIBDIR = ext/lib
SRCDIR = src
INTDIR = int
OUTDIR = bin

CPPFILES = $(SRCDIR)/a429/a429base.cpp $(SRCDIR)/a429/a429bcd.cpp $(SRCDIR)/a429/a429bnr.cpp $(SRCDIR)/a429/a429dis.cpp $(SRCDIR)/a429/a429hyb.cpp 

HPPFILES = $(SRCDIR)/a429/a429base.hpp $(SRCDIR)/a429/a429bcd.hpp $(SRCDIR)/a429/a429bnr.hpp $(SRCDIR)/a429/a429dis.hpp $(SRCDIR)/a429/a429hyb.hpp 

OBJFILES = $(INTDIR)/a429base.o $(INTDIR)/a429bcd.o $(INTDIR)/a429bnr.o $(INTDIR)/a429dis.o $(INTDIR)/a429hyb.o 

all : $(OBJFILES)
	g++ -o $(OUTDIR)/output $(OBJFILES)

$(OBJFILES) : $(CPPFILES) $(HPPFILES)
	g++ -c $(CPPFILES) -I$(INCDIR)


.PHONY: clean

clean:
	rm -f $(INTDIR)/*.o && rm $(OUTDIR)/*

