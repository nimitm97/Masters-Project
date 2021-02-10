VERSION = 1.0
CC = cc

ARCH = $(shell uname -m)
SRCDIR = ./
BUILDDIR = work/build/$(ARCH)/
OBJDIR = work/obj/$(ARCH)/

CFLAGS = -Wall -Werror -std=gnu11 -DVERSION=\"$(VERSION)\"
LDFLAGS = -lm

OBJ = $(addprefix $(OBJDIR), nmea_demo.o nmea0183.o circularbuffer.o )

default: demo_standalone

all: demo_standalone

demo_standalone: $(OBJ)
	mkdir -p $(BUILDDIR)
	$(CC) -o $(BUILDDIR)nmea_demo $(OBJ) $(LDFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY : clean
clean:
	-rm $(OBJDIR)* $(BUILDDIR)*
