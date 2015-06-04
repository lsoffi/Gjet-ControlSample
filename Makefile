# $Id: Makefile,v 1.1 2013/01/31 15:31:57 soffi Exp $
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
ROOTGLIBS     = $(shell $(ROOTSYS)/bin/root-config --glibs)

BINFILES =  Analysis.cc 

PROGRAMS = $(patsubst %.cc,%,$(BINFILES))


# --- External configuration ---------------------------------
CC         = g++ -Wno-deprecated
CCFLAGS    =  -g -O3
MFLAGS     = -MM
INCLUDES   =
WORKDIR    = tmp/
LIBDIR     = $(WORKDIR)
OBJDIR=$(WORKDIR)/objects/
# -------------------------------------------------------------

#ROOFITVER = 5.25.02-cms6
#ROOFITDIR = $(ROOTSYS)/../../roofit/$(ROOFITVER)

ROOFIT_INCLUDE := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep INCLUDE= | sed 's|INCLUDE=||')
ROOFIT_LIBDIR := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIBDIR= | sed 's|LIBDIR=||')
ROOFIT_LIBS := $(shell cd $(CMSSW_BASE); scram tool info roofitcore | grep LIB= | sed 's|LIB=||')
ROOFIT_LIBS += $(shell cd $(CMSSW_BASE); scram tool info roofit | grep LIB= | sed 's|LIB=||') 


INCLUDES += -I.  -I.. -I$(ROOTSYS)/include  -I$(ROOFIT_INCLUDE)/
ROOTSYS  ?= ERROR_RootSysIsNotDefined

EXTRALIBS  :=  -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG -lRooFitCore -lRooFit

# CC files excluding the binaries
CCFILES=$(filter-out $(BINFILES),$(wildcard *.cc))

# List of all object files to build
OLIST=$(patsubst %.cc,$(OBJDIR)/%.o,$(CCFILES))

# Implicit rule to compile all classes
$(OBJDIR)/%.o : %.cc
	@echo "Compiling $<"
	@mkdir -p $(OBJDIR)
	@$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDES)


$(PROGRAMS) : $(OLIST)
	@echo "Linking $@"
	@$(CC) $(CCFLAGS)  $(INCLUDES) $(OLIST) \
	$(ROOTLIBS) $(EXTRALIBS) -o $(WORKDIR)/$@   $(patsubst %,%.cc,$@)

default : Finalyzer

all : Finalyzer

clean:
	rm -Rf $(WORKDIR)/*
	@#rm -f $(LIBFILE)
	@rm -Rf *.o

veryclean:
	rm -Rf $(WORKDIR)
