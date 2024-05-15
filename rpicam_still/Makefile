CC=g++
CFLAGS=-Wall -Wextra -std=c++11

TARGET=rpicam_still
SRC=/home/pi/rpicam-apps/build/apps/rpicam-still.p/rpicam_still.cpp.o
OBJ=$(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ -L/usr/lib/aarch64-linux-gnu -L/home/pi/rpicam-apps/build -lcamera-base -lcamera -lpthread -lcamera_app -lboost_program_options 


.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
# clean:
# 	rm -f $(OBJ) $(TARGET)

# g++ -o rpicam_jpeg /home/pi/rpicam-apps/build/apps/rpicam-jpeg.p/rpicam_jpeg.cpp.o -L/usr/lib/aarch64-linux-gnu -L/home/pi/rpicam-apps/build -lcamera-base -lcamera -lpthread -lcamera_app -lboost_program_options
