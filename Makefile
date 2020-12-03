CPPS = $(shell find ./ -name "*.cpp")
CPPTEST = $(shell find ./ -name "*.cpp" -not -name main.cpp)
OBJS = $(CPPS:.cpp=.o)

turing: $(CPPS)
	g++ -o turing $(CPPS)

test: $(CPPTEST)
	g++ -o test $(CPPTEST)
	./test

run: turing
	./turing palindrome_detector_2tapes.tm

clean:
	rm -rf $(OBJS) turing test