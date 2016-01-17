# all: analysetrees
all: calculate_sf_JECdown 


% : %.C
	g++ -Wall  `root-config --cflags ` $? -o  $@ -I`root-config --incdir` `root-config --libs`
	



