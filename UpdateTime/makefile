IDIR =$(COMMONDIR)
CC=g++
CFLAGS=-I$(IDIR)
CXXFLAGS=-I$(IDIR)

ODIR=./
LDIR =./
COMMONDIR = ../Common
TARGET = UpdateTime

LIBS=-lwiringPi

_DEPS = $(COMMONDIR)/SparkFunSX1509.h $(COMMONDIR)/sx1509_registers.h $(COMMONDIR)/Adafruit_LEDBackpack.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = UpdateTime.o $(COMMONDIR)/SparkFunSX1509.o $(COMMONDIR)/Adafruit_LEDBackpack.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(COMMONDIR)/*.o $(TARGET)