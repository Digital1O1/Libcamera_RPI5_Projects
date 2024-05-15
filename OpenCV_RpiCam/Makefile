CC=g++
CFLAGS=-Wall -Wextra -std=c++17 -I/usr/include/rpicam-apps/core/ -I/usr/include/libcamera/ -I/usr/include/rpicam-apps/

TARGET=OpenCV_RpiCam
SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ -L/usr/lib/aarch64-linux-gnu -L/home/pi/rpicam-apps/build -lcamera-base -lcamera -lpthread -lcamera_app -lboost_program_options 

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
