AR=ar
CXX=g++
# Compile only
DEFINES = -DTALES_ENABLE_LIBPNG
CXXFLAGS=-std=gnu++11 -O2 -Wall -llibpng $(DEFINES) -I$(IDIR)

IDIR := include
SRCDIR := src
ODIR := obj
LDIR :=

#_DEPS = $(wildcard $(IDIR)/*.h) $(wildcard $(IDIR)/editors/*.h) $(wildcard $(IDIR)/exception/*.h) $(wildcard $(IDIR)/gamedata/*.h) $(wildcard $(IDIR)/gamegear/*.h) $(wildcard $(IDIR)/structs/*.h) $(wildcard $(IDIR)/util/*.h) #$(wildcard $(IDIR)/graphics/*.h) $(wildcard $(IDIR)/animation/*.h) $(wildcard $(IDIR)/timing/*.h) $(wildcard $(IDIR)/util/*.h) $(wildcard $(IDIR)/font/*.h) $(wildcard $(IDIR)/sound/*.h) $(wildcard $(IDIR)/resource/*.h) $(wildcard $(IDIR)/input/*.h) $(wildcard $(IDIR)/logic/*.h)
#DEPS = $(_DEPS)

SRC := $(wildcard $(SRCDIR)/*/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%,$(ODIR)/%,$(patsubst %.cpp,%.o,$(SRC)))
DEP := $(patsubst %.o,%.d,$(OBJ))
LIB := libtales.a

all: $(LIB)

-include $(DEP)

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(dir $@)
	$(CXX) -c -MMD -MP -MF $(@:.o=.d) -o $@ $< $(CXXFLAGS) $(INCLUDES)

$(LIB): $(OBJ)
	$(AR) rcs $@ $^
	#doxygen Doxyfile

.PHONY: clean

clean:
	rm -f $(LIB)
	rm -rf $(ODIR)
