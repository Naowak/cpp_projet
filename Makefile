TARGET=calculator

SOURCES= utils.cpp ExprToken.cpp expr.cpp seqExpr.cpp

OBJECTS=$(SOURCES:.cpp=.o)

CC=g++
CXXFLAGS+= -std=c++11 -g

$(TARGET):  $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lm

.cpp.o:
	$(CC) $(CXXFLAGS) -c $<

clean:
	rm -f $(TARGET)  $(OBJECTS) *~

utils.o: utils.h ExprToken.h 
ExprToken.o: utils.h ExprToken.h  
expr.o: expr.h ExprToken.h utils.h 
seqExpr.o: seqExpr.h expr.h ExprToken.h utils.h
