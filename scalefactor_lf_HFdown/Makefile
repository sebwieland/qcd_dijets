# all: analysetrees
all: calculate_sf_HFdown 


% : %.C
	g++ -Wall  `root-config --cflags ` $? -o  $@ -I`root-config --incdir` `root-config --libs`
	



