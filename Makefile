CPPS = $(shell find ./ -name "*.cpp" -not -name test.cpp)
CPPTEST = $(shell find ./ -name "*.cpp" -not -name main.cpp)
OBJS = $(CPPS:.cpp=.o)

turing: $(CPPS)
	g++ -o turing $(CPPS)

clean:
	rm -rf $(OBJS) turing