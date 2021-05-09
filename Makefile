all: compile link

compile:
	g++ -ISFML/include \
	-Ijsonparser/include \
	-c src/main.cpp \
	-c src/MapProperties.cpp \
	-c src/json_reader.cpp \
	-c src/json_value.cpp \
	-c src/json_writer.cpp

link:
	g++ main.o \
	MapProperties.o \
	newer.o \
	json_reader.o \
	json_value.o \
	json_writer.o \
	-o json_reader \
	-o json_value \
	-o json_writer \
	-o MapProperties \
	-o main \
	-LSFML/lib \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system \
	-lsfml-audio