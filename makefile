INCDIR = ext/include # 3rd party includes
LIBDIR = ext/lib     # 3rd party libs
SRCDIR = src         # sources and headers
INTDIR = int         # objects (.o and .d)
OUTBINDIR = bin      # resulting binaries
OUTINCDIR = include  # copy of relevant exported include files to go with binaries


CPPFILES = $(wildcard $(SRCDIR)/a429/*.cpp)
HPPFILES = $(CPPFILES:.cpp=.o)
OBJFILES = $(addprefix $(INTDIR)/,$(notdir $(CPPFILES:.cpp=.o))) 

CC_FLAGS = -I$(INCDIR) -MMD

all : $(OBJFILES)
	ar rvs $(OUTBINDIR)/libopenarinc.a $(OBJFILES) && cp $(SRCDIR)/a429/*.hpp $(OUTINCDIR)/a429

$(INTDIR)/%.o : $(SRCDIR)/a429/%.cpp 
	g++ -c -o $@ $< $(CC_FLAGS)

#test: 
#	g++ test/sometest.cpp bin/libopenarinc.a -o bin/test -I./include

.PHONY: clean

clean:
	rm -f $(INTDIR)/*.o $(INTDIR)/*.d $(OUTBINDIR)/openarinc


-include $(OBJFILES:.o=.d)
