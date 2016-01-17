all: pu_weight



% : %.C
	g++ -Wall  `root-config --cflags ` $? -o  $@ -I`root-config --incdir` `root-config --libs`
	



