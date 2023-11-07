lugfetch: lugfetch.cpp
	g++ lugfetch.cpp -o lugfetch

run: lugfetch
	./lugfetch

install: lugfetch
	cp ./lugfetch /usr/bin/lugfetch
