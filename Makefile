CXXFLAGS = -g -Og -Wall -fmessage-length=0 -std=c++11

CXX = g++ 

OBJS = main.o SimulationControl.o SimulationUI.o TrafficModel.o Platoon.o Car.o
SRCS = main.cpp SimulationControl.cpp SimulationUI.cpp TrafficModel.cpp Platoon.cpp Car.cpp

TARGET = simulator.o

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

debug:
	$(CXX) -g -D_DEBUG -o $(TARGET) test.cpp $(SRCS) -lgtest -lgtest_main
	
clean:
	rm -f $(OBJS) $(TARGET)
