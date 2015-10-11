all: qcd_loop

% : %.cpp
	g++ -Wall  $? -o $@ -I`root-config --incdir --libdir`

