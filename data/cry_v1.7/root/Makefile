#
# make       = run short test
# make all   = run all tests (including root)
# make runRoot  = compile and run specified test
#
# Doug Wright
# root5 is forced to use (ueno 11.26.2018)

 include ../Makefile.common  #....define compiler and any other common settings
-include ../Makefile.local   #....local definitions for this host (if any)

EXE = testRoot
CXXFLAGS += -I../src

default: testRoot
all: $(EXE)

#....rule to make test executables
test%: test%.C ../lib/libCRY.a
	$(CXX) $(CXXFLAGS) -o $@ $@.cc -L../lib -lCRY
 
#....testRoot is different
testRoot: testRoot.C ../lib/libCRY.a
	$(CXX) $(CXXFLAGS) -I$(ROOTSYS)/include -o $@ $@.C -L../lib -lCRY $(shell root-config --libs)

clean:
	rm -f *.o $(EXE)

#....make sure these executables are not deleted as intermediate files
.PRECIOUS: $(EXE)
