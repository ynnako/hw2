####################################################################
# Makefile for building the election application
#


#
# Definitions
#
CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = election.o voter.o party.o
RM = rm -f
TARGET = election


#
# Target Section
#
$(TARGET): $(OBJS)
	$(CCLINK) -o $(TARGET) $(OBJS)


#
# File Section
#
election.o: election.c voter.h party.h
party.o: party.c party.h
voter.o: voter.c voter.h


#
# Cleaning
#
clean:
	$(RM) $(TARGET) *.o *.bak *~"#"* core
