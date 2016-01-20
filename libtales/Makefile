CC=g++
# Compile only
CFLAGS=-std=c++11 -O2 -Wall -c -I$(IDIR)

IDIR=include
SRCDIR=src
ODIR=obj
LDIR=

INCLUDES = #-I/usr/local/include/SDL2 -I/usr/include/freetype2 -I/usr/include/vorbis

LIBS = #-lSDL2 -lfreetype -lvorbisfile

_DEPS = $(wildcard $(IDIR)/*.h) $(wildcard $(IDIR)/editors/*.h) $(wildcard $(IDIR)/exception/*.h) $(wildcard $(IDIR)/gamedata/*.h) $(wildcard $(IDIR)/gamegear/*.h) $(wildcard $(IDIR)/structs/*.h) $(wildcard $(IDIR)/util/*.h) #$(wildcard $(IDIR)/graphics/*.h) $(wildcard $(IDIR)/animation/*.h) $(wildcard $(IDIR)/timing/*.h) $(wildcard $(IDIR)/util/*.h) $(wildcard $(IDIR)/font/*.h) $(wildcard $(IDIR)/sound/*.h) $(wildcard $(IDIR)/resource/*.h) $(wildcard $(IDIR)/input/*.h) $(wildcard $(IDIR)/logic/*.h)
DEPS = $(_DEPS)

_OBJ = $(patsubst %.h,%.o,$(DEPS))
OBJ = $(patsubst $(IDIR)/%,$(ODIR)/%,$(_OBJ))

#$(info $$OBJ is [${OBJ}])

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES) $(LIBS)

libtalesmake: libtalesfull
	ar rcs libtales.a $(OBJ) #&& doxygen Doxyfile
	
#cp -r * /media/9AF06E65F06E4799/copy/libtales/autobak && 

libtalesfull: $(OBJ)

.PHONY: clean

clean:
	rm -f libtales.a $(ODIR)/*.o $(ODIR)/editors/*.o $(ODIR)/exception/*.o $(ODIR)/gamedata/*.o $(ODIR)/gamegear/*.o $(ODIR)/structs/*.o $(ODIR)/util/*.o *~ $(SRCDIR)/*~ $(IDIR)/*~ core #$(ODIR)/animation/*.o $(ODIR)/font/*.o $(ODIR)/graphics/*.o $(ODIR)/input/*.o $(ODIR)/logic/*.o $(ODIR)/resource/*.o $(ODIR)/sound/*.o $(ODIR)/timing/*.o $(ODIR)/util/*.o
