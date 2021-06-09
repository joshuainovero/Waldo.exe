# Use mingw32-make

CC := g++
CFLAGS := -Wall

OBJS := main.o MapProperties.o StaticObjAnimation.o json_reader.o json_value.o json_writer.o
CSRC := src
JSRC := src/jsonparser
I-SF-SRC := SFML/include
I-JSON-SRC := jsonparser/include
INCLUDES := -I$(I-SF-SRC) -I$(I-JSON-SRC) 
SFLIB := -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
WIN := -mwindows
DEPEND := $(SFLIB) $(WIN)
ICONSRC := Assets/Icon/AppIcon/iconres.res 

TARGET := Waldo
OPATH := Build/release

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ $(DEPEND) $(ICONSRC) -o $(OPATH)/$@

main.o: $(CSRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticObjAnimation.o: $(CSRC)/StaticObjAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

MapProperties.o: $(CSRC)/MapProperties.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_reader.o: $(JSRC)/json_reader.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_value.o: $(JSRC)/json_value.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_writer.o: $(JSRC)/json_writer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<


clean:
	@echo off && del *.o

