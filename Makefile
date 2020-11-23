CXX=clang++-9
CXXFLAGS=-std=c++2a 

prefix_table: prefix_table.cpp
	$(CXX) $(CXXFLAGS) prefix_table.cpp	-o prefix_table

prefix_table_opt: prefix_table_opt.cpp
	$(CXX) $(CXXFLAGS) prefix_table_opt.cpp	-o prefix_table_opt

clean:
	rm -f *.o demo prefix_table prefix_table_opt