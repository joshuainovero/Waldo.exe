# Use mingw32-make

CC := g++
CFLAGS := -Wall

# Objects to link
ROOT := main.o Engine.o GameResources.o
STATES := State.o InGame.o MapSelect.o GameMenu.o
ANIMATIONS:= StaticObjAnimation.o StaticCircleAnimation.o StaticPauseAnimation.o
UTILS := EDassets.o GameTimer.o Labels.o TimerLabel.o TypeWriter.o MapProperties.o
JSONPARSER := json_reader.o json_value.o json_writer.o
OBJS := $(ROOT) $(STATES) $(ANIMATIONS) $(UTILS) $(JSONPARSER)

# Debug Targets
DROOT := main.do Engine.do GameResources.do
DSTATES := State.do InGame.do MapSelect.do GameMenu.do
DANIMATIONS:= StaticObjAnimation.do StaticCircleAnimation.do StaticPauseAnimation.do
DUTILS := EDassets.do GameTimer.do Labels.do TimerLabel.do TypeWriter.do MapProperties.do
DJSONPARSER := json_reader.do json_value.do json_writer.do
DOBJS := $(DROOT) $(DSTATES) $(DANIMATIONS) $(DUTILS) $(DJSONPARSER)

# Release Targets
RROOT := main.ro Engine.ro GameResources.ro
RSTATES := State.ro InGame.ro MapSelect.ro GameMenu.ro
RANIMATIONS:= StaticObjAnimation.ro StaticCircleAnimation.ro StaticPauseAnimation.ro
RUTILS := EDassets.ro GameTimer.ro Labels.ro TimerLabel.ro TypeWriter.ro MapProperties.ro
RJSONPARSER := json_reader.ro json_value.ro json_writer.ro
ROBJS := $(RROOT) $(RSTATES) $(RANIMATIONS) $(RUTILS) $(RJSONPARSER)

# Directories and Dependencies
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

# Executable Output
TARGETD := WaldoDebug
TARGETR:= Waldo
OPATH := Build/release
PLINKDEBUG := @echo off && echo. && echo Linking $(OBJS) $(DEPENDDEBUG) $(ICONSRC)
PLINKRELEASE := @echo off && echo. && echo Linking $(OBJS) $(DEPENDRELEASE) $(ICONSRC)

############################################################################################

DEBUG: $(TARGETD)

$(TARGETD): $(DOBJS)
	$(PLINKDEBUG) && $(CC) $(CFLAGS) $(OBJS) $(DEPENDDEBUG) $(ICONSRC) -o $(OPATH)/$@

main.do: $(CSRC)/main.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

EDassets.do: $(CSRC)/EDassets.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

StaticObjAnimation.do: $(CSRC)/StaticObjAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticCircleAnimation.do: $(CSRC)/StaticCircleAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticPauseAnimation.do: $(CSRC)/StaticPauseAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

State.do: $(CSRC)/State.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

GameResources.do: $(CSRC)/GameResources.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

Engine.do: $(CSRC)/Engine.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

InGame.do: $(CSRC)/InGame.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

MapSelect.do: $(CSRC)/MapSelect.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

GameMenu.do: $(CSRC)/GameMenu.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

Labels.do: $(CSRC)/Labels.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

TypeWriter.do: $(CSRC)/TypeWriter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

TimerLabel.do: $(CSRC)/TimerLabel.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

MapProperties.do: $(CSRC)/MapProperties.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

GameTimer.do: $(CSRC)/GameTimer.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

json_reader.do: $(JSRC)/json_reader.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_value.do: $(JSRC)/json_value.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

json_writer.do: $(JSRC)/json_writer.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
	
############################################################################################

RELEASE: $(TARGETR)

$(TARGETR): $(ROBJS)
	$(PLINKRELEASE) && $(CC) $(CFLAGS) $(OBJS) $(DEPENDRELEASE) $(ICONSRC) -o $(OPATH)/$@

main.ro: $(CSRC)/main.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

EDassets.ro: $(CSRC)/EDassets.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticObjAnimation.ro: $(CSRC)/StaticObjAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticCircleAnimation.ro: $(CSRC)/StaticCircleAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

StaticPauseAnimation.ro: $(CSRC)/StaticPauseAnimation.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

State.ro: $(CSRC)/State.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

GameResources.ro: $(CSRC)/GameResources.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

Engine.ro: $(CSRC)/Engine.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

InGame.ro: $(CSRC)/InGame.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

MapSelect.ro: $(CSRC)/MapSelect.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

GameMenu.ro: $(CSRC)/GameMenu.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

Labels.ro: $(CSRC)/Labels.cpp
	$(CC) $(CFLAGS) -D DEBUG $(INCLUDES) -c $<

TypeWriter.ro: $(CSRC)/Typewriter.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

TimerLabel.ro: $(CSRC)/TimerLabel.cpp
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

