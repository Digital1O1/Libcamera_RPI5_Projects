CC=g++
CFLAGS=-Wall -Wextra -std=c++11 -I/usr/include/rpicam-apps/core/ -I/usr/include/libcamera/ -I/usr/include/rpicam-apps/

TARGET=OpenCV_RpiCam
SRC=main.cpp
#SRC=/home/pi/rpicam-apps/build/apps/rpicam-jpeg.p/rpicam_jpeg.cpp.o
OBJ=$(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ -L/usr/lib/aarch64-linux-gnu -L/home/pi/rpicam-apps/build -lcamera-base -lcamera -lpthread -lcamera_app -lboost_program_options 


# .cpp.o:
# 	$(CC) $(CFLAGS) -c $< -o $@

# Compile rule for .cpp files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)



clean:
	rm -f $(TARGET)
# clean:
# 	rm -f $(OBJ) $(TARGET)

# g++ -o rpicam_jpeg /home/pi/rpicam-apps/build/apps/rpicam-jpeg.p/rpicam_jpeg.cpp.o -L/usr/lib/aarch64-linux-gnu -L/home/pi/rpicam-apps/build -lcamera-base -lcamera -lpthread -lcamera_app -lboost_program_options
