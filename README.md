# augmentedReality

To run:
	
	g++ -std=c++11 src/*.c src/*.cpp test.cpp -I include/ `pkg-config --libs --cflags opencv` -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
