CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -std=c++11 -Ofast -pthread
LDFLAGS= -std=c++11 -Ofast -pthread
LDLIBS=

SRCS=main.cpp includes/*.cpp
OBJS=$(subst .cc,.o,$(SRCS))
CRAP=*.cc, *.o

all: build_debug run clean

build_debug: $(OBJS)
	@echo "==> Compiling"
	$(CXX) $(LDFLAGS) -g -o tool $(OBJS) $(LDLIBS)

build_release: $(OBJS)
	@echo "==> Compiling"
	$(CXX) $(LDFLAGS) -o tool $(OBJS) $(LDLIBS)


run:
	@echo "==> Running"
	@echo ""
	@echo ""
	@./tool
	@echo ""
	@echo ""

release: build_debug clean dist-clean

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	@$(RM) $(CRAP)

dist-clean: clean
	$(RM) *~ .depend

include .depend
