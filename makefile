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
LIBS := -lncurses -lcurl 

_DEPS := AirlineCompany.h airport_menu.h options.h command_line.h idresolver.h colors.h Plane.h https.h type.h utils.h log.h linked_list.h Airport.h Location.h WeatherCondition.h Database.h hash_map.h
DEPS  := $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ := AirlineCompany.o airport_menu.o options.o command_line.o idresolver.o colors.o Plane.o https.o main.o utils.o log.o linked_list.o Airport.o Location.o WeatherCondition.o Database.o hash_map.o 
OBJ  := $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

run:
ifndef $(mode)
	./$(EXECUTABLE) run-cl
else	
	./$(EXECUTABLE) $(mode) 
endif

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  
