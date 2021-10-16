CC=gcc

BINDIR=bin
ODIR=obj
LDIR =lib
ENTRYPOINT=main

LIBS=$(wildcard $(LDIR)/*.c)

_OBJ = $(patsubst %.c, %.o, $(LIBS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

build: $(OBJ)
	@mkdir -p $(BINDIR)
	@$(CC) -o $(BINDIR)/$(ENTRYPOINT) $(OBJ) $(ODIR)/$(ENTRYPOINT).o

$(ODIR)/$(ENTRYPOINT).o:
	@$(CC) -c -o $@ $(ENTRYPOINT).c

$(OBJ): $(LIBS)
	@mkdir -p $(ODIR)/$(LDIR)
	@$(CC) -c -o $@ $<

print:
	@echo $(OBJ)

.PHONY: clean

clean:
	@rm -f *.o $(ODIR)/*.o $(ODIR)/*/*.o $(BINDIR)/*
