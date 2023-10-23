CPPC = g++-13
CPPFLAGS = -std=c++17 -Wl,-ld_classic

SRCDIR = src
BINDIR = bin

%:
	$(CPPC) $(CPPFLAGS) $@.cpp -o $(BINDIR)/$(notdir $@)
