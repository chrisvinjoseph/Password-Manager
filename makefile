output: driver.o encryptor.o decryptor.o hash.o misc.o pass_manager.o
	 g++ driver.o encryptor.o decryptor.o hash.o misc.o pass_manager.o -lcrypto++ -o passmanager

driver.o: driver.cpp
	g++ -c driver.cpp -lcrypto++

encryptor.o: encryptor.cpp headers/encryptor.hpp
	g++ -c encryptor.cpp -lcrypto++

decryptor.o: decryptor.cpp headers/decryptor.hpp
	g++ -c decryptor.cpp -lcrypto++

hash.o: hash.cpp headers/hash.hpp
	g++ -c hash.cpp -lcrypto++

misc.o: misc.cpp headers/misc.hpp
	g++ -c misc.cpp -lcrypto++

pass_manager.o: pass_manager.cpp headers/pass_manager.hpp
	g++ -c pass_manager.cpp -lcrypto++

clean:
	rm *.o passmanager
