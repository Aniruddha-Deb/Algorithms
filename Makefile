CPPC = clang++
CPPFLAGS = -std=c++14 -Wall

SRCDIR = src
BINDIR = bin

%.cpp:
	$(CPPC) $(CPPFLAGS) $(shell find $(SRCDIR) -name $(@)) -o $(BINDIR)/$@

%.py:
	cp $(shell find $(SRCDIR) -name $@) $(BINDIR)/$@
	chmod +x $(BINDIR)/$@
