all: analysetrees_pu



% : %.C
	g++ -Wall  `root-config --cflags ` $? -o  $@ -I`root-config --incdir` `root-config --libs`
	



