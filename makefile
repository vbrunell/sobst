# Victor Brunell
# Self Organizing Binary Search Trees
#
# To compile just type 'make' in the containing directory

sobst: sobst_driver.o
	g++ -std=c++0x -o sobst sobst_driver.o

sobst_driver.o: sobst_driver.cpp
	g++ -std=c++0x -c sobst_driver.cpp

clean:
	rm *.o sobst
