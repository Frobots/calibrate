TARGET = ./rvision

SRCS := $(wildcard ./*.cpp)

OBJS := $(patsubst %cpp,%o,$(SRCS))

CFLG = -g -Wall -I/usr/local/include -Iinc -I./ -std=c++11 -I./include

LDFG = -Wl,--rpath=$(MVCAM_COMMON_RUNENV)/64 -L$(MVCAM_COMMON_RUNENV)/64 -lMvCameraControl,/usr/local/lib -L./ -L/usr/local/lib -L./inc -lrt -lpthread  -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio `pkg-config opencv --cflags --libs `

CXX = g++

$(TARGET) : $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFG)

%.o:%.cpp
	$(CXX) $(CFLG) -c $< -o $@

.PHONY : clean
clean:
	-rm ./*.o
	-rm ./rvision
