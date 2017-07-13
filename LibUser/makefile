#############################################################################
#
# Makefile 
#
#===========================================================================

# Excecutable file.
PROGRAM   = usrkit

# Parameters .
CC      = gcc
CFLAGS  = -g -O2 -Wall
RM      = rm -f
COMPILE = $(CC) $(CFLAGS) -c
SRCS	= $(wildcard *.c)
OBJS    = $(addsuffix .o, $(basename $(SRCS)))

# Make goes here.
all: $(PROGRAM)
	@$(RM) $(OBJS)

clean:
	$(RM) $(OBJS) $(PROGRAM)

show:
	@echo 'PROGRAM     :' $(PROGRAM)
	@echo 'SRCS        :' $(wildcard *.c)
	@echo 'OBJS        :' $(OBJS)
	@echo 'LINK.c      :' $(LINK.c)
	
# Object files.
objs:$(OBJS)
$(PROGRAM):$(OBJS)
	$(LINK.c)  $(OBJS)   -o $@
%.o:%.c
	@$(COMPILE) $< -o $@

