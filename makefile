INCDIR = ext/include
LIBDIR = ext/lib
SRCDIR = src
INTDIR = int
OUTBINDIR = bin
OUTINCDIR = inc

CPPFILES = $(wildcard $(SRCDIR)/a429/*.cpp)
OBJFILES = $(addprefix $(INTDIR)/,$(notdir $(CPPFILES:.cpp=.o)))

CC_FLAGS = -I$(INCDIR) -MMD

all : $(OBJFILES)
	ar rvs $(OUTBINDIR)/libopenarinc.a $(OBJFILES) && cp $(SRCDIR)/a429/*.hpp $(OUTINCDIR)/a429

$(INTDIR)/%.o : $(SRCDIR)/a429/%.cpp
	g++ -c -o $@ $< $(CC_FLAGS)

test: bin/libopenarinc.a test/test.cpp 
	g++ test/test.cpp bin/libopenarinc.a -o $(OUTBINDIR)/test -I$(OUTINCDIR) -I../boost

.PHONY: clean

clean: 
	rm -f $(INTDIR)/*.o $(INTDIR)/*.d $(OUTBINDIR)/libopenarinc.a $(OUTINCDIR)/a429/*.hpp

-include $(OBJFILES:.o=.d)
