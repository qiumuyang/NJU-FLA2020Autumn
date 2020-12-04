CPPS = $(shell find ./ -name "*.cpp" -not -name test.cpp)
CPPTEST = $(shell find ./ -name "*.cpp" -not -name main.cpp)
OBJS = $(CPPS:.cpp=.o)

turing: $(CPPS)
	g++ -o turing $(CPPS)

test: $(CPPTEST)
	g++ -o test $(CPPTEST)
	./test

clean:
	rm -rf $(OBJS) turing test