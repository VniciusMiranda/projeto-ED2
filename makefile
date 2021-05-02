# project directories
IDIR := include/
SDIR := src
ODIR := obj

# compiler specs
CC     := gcc
CFLAGS := -I $(IDIR) 

# executable name
EXECUTABLE := executable/airline-management

# libraries
LIBS := -lncurses -lpthread 

_DEPS := type.h utils.h log.h linked_list.h Airport.h Location.h WeatherCondition.h Database.h hash_map.h
DEPS  := $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ := main.o utils.o log.o linked_list.o Airport.o Location.o WeatherCondition.o Database.o hash_map.o 
OBJ  := $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  
