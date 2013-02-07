CXXFLAGS =	 -g -Wall -fmessage-length=0 -std=c++0x  # -O2

OBJS =		NoMaintenanceRemake.o Screen.o Meteor.o aux.o ImageFunctions.o Smoke.o Exp.o SoundFunctions.o Spark.o Bomb.o \
Blast.o WeaponCollection.o SmokeSpark.o Canoner.o Weapon.o Musquash.o Guy.o Blood.o IBomb.o HExp.o \
Miligun.o MiniShot.o Zookaba.o Player.o CarlGustaf.o Missile.o Eagle.o CExp.o Reference.o Tropelet.o Armageddon.o \
Klachnikow.o ChokladZingo.o NukeGrenade.o Fire.o Haubits.o EldFunkar.o EldFunkarProj.o Airokurtz.o Hao.o \
Jolt.o Plasma.o Box.o

TEST = ImageFunctions_test.o

LIBS = -lSDL -lGL -lGLEW

TARGET =	NoMaintenanceRemake

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

%.o: %.h


clean:
	rm -f $(OBJS) $(TARGET)

sdl/SDL_mixer.o:
	echo hej

test: $(TEST)
	$(CXX) -o test $(TEST)
	./test