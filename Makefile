CXX ?= clang++
CXXFLAGS=-Wall -pedantic -Werror -std=c++11 -pipe
CL=cl
CLFLAGS=/wd4514 /wd4710 /wd4571 /wd4774 /wd4365 /wd4625 /wd4820 /wd4626 /wd5026 /wd5027 /wd4265 /wd4623 /Wall /EHs /FeScotlandYard.exe


linux:
	$(CXX) $(CXXFLAGS) -o ScotlandYard *.cpp

windows: 
	$(CL) *.cpp $(CLFLAGS)
