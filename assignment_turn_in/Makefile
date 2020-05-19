CC=g++
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)
HDRS = $(shell ls *.h)
TARGET = sort

$(TARGET) : $(OBJS)
	  $(CC) $(OBJS) -std=c++1y -lc -O3 -o $@

%.o : %.cpp
	  $(CC) -std=c++1y -O3 -c $<

$(OBJS) : $(HDRS)

all :$(TARGET)

clean :
	  rm -f $(OBJS) $(TARGET) 

