EXTINCDIR = ext/include
EXTLIBDIR = ext/lib
SRCDIR = src
INTDIR = int
BINDIR = bin
INCDIR = inc

CPPFILES = $(wildcard $(SRCDIR)/a429/*.cpp)
OBJFILES = $(addprefix $(INTDIR)/,$(notdir $(CPPFILES:.cpp=.o)))

CC_FLAGS = -I$(EXTINCDIR) -MMD

all : $(OBJFILES)
	ar rvs $(BINDIR)/libopenarinc.a $(OBJFILES) && cp $(SRCDIR)/a429/*.hpp $(INCDIR)/a429

$(INTDIR)/%.o : $(SRCDIR)/a429/%.cpp
	g++ -c -o $@ $< $(CC_FLAGS)

test: bin/libopenarinc.a test/test.cpp 
	g++ test/test.cpp bin/libopenarinc.a -o $(BINDIR)/test -I$(INCDIR) -I../boost -w
	./bin/test --random=1 --report_level=short

.PHONY: clean

clean: 
	rm -f $(INTDIR)/*.o $(INTDIR)/*.d $(BINDIR)/libopenarinc.a $(INCDIR)/a429/*.hpp

-include $(OBJFILES:.o=.d)
