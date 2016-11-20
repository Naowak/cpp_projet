TARGET=calculator

SOURCES= seqExpr.cpp expr.cpp ExprToken.cpp utils.cpp 

OBJECTS=$(SOURCES:.cpp=.o)

CC=g++
CXXFLAGS+= -std=c++11 -g

$(TARGET):  $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -f $(TARGET)  $(OBJECTS) *~

utils.o: utils.h ExprToken.h 
ExprToken.o: ExprToken.h utils.h 
expr.o: expr.h ExprToken.h utils.h 
seqExpr.o: seqExpr.h expr.h ExprToken.h utils.h
