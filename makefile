CXX = g++
CXXFLAGS = -Wall

proj: proj.cpp CipherTool.o Atbash.o Scytale.o Ong.o Cipher.o
	$(CXX) $(CXXFLAGS) proj.cpp CipherTool.o Atbash.o Scytale.o Ong.o Cipher.o -o proj

CipherTool.o: CipherTool.h CipherTool.cpp Atbash.o Scytale.o Ong.o Cipher.o
	$(CXX) $(CXXFLAGS) -c CipherTool.cpp

Atbash.o: Atbash.h Atbash.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Atbash.cpp

Scytale.o: Scytale.h Scytale.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Scytale.cpp

Ong.o: Ong.h Ong.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Ong.cpp

Cipher.o: Cipher.h Cipher.cpp 
	$(CXX) $(CXXFLAGS) -c Cipher.cpp
	
val:
	valgrind ./proj proj_data4.txt

run:
	./proj 

clean:
	rm *~ 
