
#Use GNU compiler
CC = g++ 

all: run

run:
	$(CC) consumer.cpp -o ./consumer
	$(CC) producer.cpp -o ./producer
	gnome-terminal -- bash -c "./producer ALUMINIUM  10 0.1 200 30;exec bash"
	gnome-terminal -- bash -c "./producer COPPER 	 20 0.1 200 15;exec bash"
	

	

