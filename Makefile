scheduler_abhinav_gupta: main.cpp
	g++ -g -std=c++11 Process.cpp Event.cpp Helper.cpp Schedulers/FCFS.cpp main.cpp -o scheduler_abhinav_gupta
clean:
	rm -f scheduler_abhinav_gupta *~