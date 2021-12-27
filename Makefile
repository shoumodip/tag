CXXFLAGS=-Wall -Wextra -std=c++11 -pedantic `pkg-config --cflags taglib`
LIBS=`pkg-config --libs taglib`

tag: tag.cpp
	$(CXX) $(CXXFLAGS) -o tag tag.cpp $(LIBS)
