CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test

#-----------------------------------------------------
llrec-test: llrec-test.cpp llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) llrec-test.cpp llrec.cpp -o $@

stack-test: stack_test.cpp stack.h
	$(CXX) $(CXXFLAGS) stack_test.cpp -o $@

heap-test: heap_test.cpp heap.h
	$(CXX) $(CXXFLAGS) heap_test.cpp -o $@


clean:
	rm -f *.o rh llrec-test stack-test heap-test *~

.PHONY: clean 