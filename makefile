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

_DEPS := utils.h Table.h Database.h linked_list.h Airport.h Location.h WeatherCondition.h 
DEPS  := $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ := main.o utils.o Database.o Table.o linked_list.o Airport.o Location.o WeatherCondition.o 
OBJ  := $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  
