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
LIBS := -lncurses -lcurl -ljson-c 

_DEPS := open_weather.h plane_menu.h AirlineCompany.h airport_menu.h options.h command_line.h idresolver.h colors.h Plane.h https.h type.h utils.h log.h linked_list.h Airport.h Location.h weather.h Database.h hash_map.h
DEPS  := $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ := open_weather.o plane_menu.o AirlineCompany.o airport_menu.o options.o command_line.o idresolver.o colors.o Plane.o https.o main.o utils.o log.o linked_list.o Airport.o Location.o weather.o Database.o hash_map.o 
OBJ  := $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

run:
	./$(EXECUTABLE) run-cl


clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~  
