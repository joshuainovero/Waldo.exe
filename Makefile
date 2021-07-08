# Use mingw32-make

CC := g++
CFLAGS := -Wall

OBJS := main.o EDassets.o MapProperties.o GameTimer.o StaticObjAnimation.o State.o Engine.o Typewriter.o json_reader.o json_value.o json_writer.o
DOBJS := main.do EDassets.do MapProperties.do GameTimer.do StaticObjAnimation.do State.do Engine.do Typewriter.do json_reader.do json_value.do json_writer.do
ROBJS := main.ro EDassets.ro MapProperties.ro GameTimer.ro StaticObjAnimation.ro State.ro Engine.ro Typewriter.ro json_reader.ro json_value.ro json_writer.ro
CSRC := src
JSRC := src/jsonparser
I-SF-SRC := SFML/include
I-JSON-SRC := jsonparser/include
INCLUDES := -I$(I-SF-SRC) -I$(I-JSON-SRC) 
SFLIB := -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SYS := -mwindows
DEPENDDEBUG := $(SFLIB)
DEPENDRELEASE := $(SFLIB) $(SYS)
ICONSRC := Assets/Icon/AppIcon/iconres.res 

TARGETD := WaldoDebug
TARGETR:= Waldo
OPATH := Build/release
PLINKDEBUG := @echo off && echo. && echo Linking $(OBJS) $(DEPENDDEBUG) $(ICONSRC)
PLINKRELEASE := @echo off && echo. && echo Linking $(OBJS) $(DEPENDRELEASE) $(ICONSRC)

DEBUG: $(TARGETD)

$(TARGETD): $(DOBJS)
	$(PLINKDEBUG) && $(CC) $(CFLAGS) $(OBJS) $(DEPENDDEBUG) $(ICONSRC) -o $(OPATH)/$@

main.do: $(CSRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

EDassets.do: $(CSRC)/EDassets.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

StaticObjAnimation.do: $(CSRC)/StaticObjAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

State.do: $(CSRC)/State.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Engine.do: $(CSRC)/Engine.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

Typewriter.do: $(CSRC)/TypeWriter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

MapProperties.do: $(CSRC)/MapProperties.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

GameTimer.do: $(CSRC)/GameTimer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_reader.do: $(JSRC)/json_reader.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_value.do: $(JSRC)/json_value.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_writer.do: $(JSRC)/json_writer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	


RELEASE: $(TARGETR)

$(TARGETR): $(ROBJS)
	$(PLINKRELEASE) && $(CC) $(CFLAGS) $(OBJS) $(DEPENDRELEASE) $(ICONSRC) -o $(OPATH)/$@

main.ro: $(CSRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

EDassets.ro: $(CSRC)/EDassets.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticObjAnimation.ro: $(CSRC)/StaticObjAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

State.ro: $(CSRC)/State.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Engine.ro: $(CSRC)/Engine.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

Typewriter.ro: $(CSRC)/Typewriter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

MapProperties.ro: $(CSRC)/MapProperties.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

GameTimer.ro: $(CSRC)/GameTimer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_reader.ro: $(JSRC)/json_reader.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_value.ro: $(JSRC)/json_value.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_writer.ro: $(JSRC)/json_writer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	


	
clean:
	@echo off && del *.o

