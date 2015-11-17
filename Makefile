CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g -std=c++11
LDLIBS=

SRCS=main.cpp includes/*.cpp
OBJS=$(subst .cc,.o,$(SRCS))
CRAP=*.cc, *.o

all: tool run clean

tool: $(OBJS)
	@echo "==> Compiling"
	$(CXX) $(LDFLAGS) -o tool $(OBJS) $(LDLIBS)
	@echo "==> Running"

run:
	@echo ""
	@echo ""
	@./tool
	@echo ""
	@echo ""

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	@$(RM) $(CRAP)

dist-clean: clean
	$(RM) *~ .depend

include .depend
