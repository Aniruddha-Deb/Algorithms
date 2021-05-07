CPPC = clang++
CPPFLAGS = -std=c++14 -Wall 

%.cpp:
	$(CPPC) $(CPPFLAGS) $@ -o bin/$(notdir $@)

clean:
	rm -rf bin/*
