# all: analysetrees
all: calculate_sf_HFup 


% : %.C
	g++ -Wall  `root-config --cflags ` $? -o  $@ -I`root-config --incdir` `root-config --libs`
	



