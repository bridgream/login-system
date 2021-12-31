all: main

main: src/initialize.cpp src/main.cpp
	$(CXX) -std=c++17 $(CFLAGS) $? $(LDFLAGS) -lsqlite3 -o $@

clean:
	rm main