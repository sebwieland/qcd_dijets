all: qcd_loop

% : %.cc
	g++ -Wall -pedantic -g `root-config --cflags ` $? -o  $@ -I`root-config --incdir` `root-config --libs`


