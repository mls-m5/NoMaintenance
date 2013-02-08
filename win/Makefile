#makefil till windowsversionen

CPPFLAGS = -g -std=c++0x -I../ -Ic:/MinGW/include/SDL
CPPFLAGS += -D_GNU_SOURCE=1 -D_REENTRANT
CPPFLAGS += -Iglew-1.9.0/include/ -I./
CPPFLAGS += -DGLEW_STATIC -D_WIN32

#CXXFLAGS =	 -g -Wall -fmessage-length=0 -std=c++0x `pkg-config --cflags freetype2 sdl ftgl` # -O2

OBJS =		NoMaintenanceRemake.o Screen.o Meteor.o common.o ImageFunctions.o Smoke.o Exp.o SoundFunctions.o Spark.o Bomb.o \
Blast.o WeaponCollection.o SmokeSpark.o Canoner.o Weapon.o Musquash.o Guy.o Blood.o IBomb.o HExp.o \
Miligun.o MiniShot.o Zookaba.o Player.o CarlGustaf.o Missile.o Eagle.o CExp.o Reference.o Tropelet.o Armageddon.o \
Klachnikow.o ChokladZingo.o NukeGrenade.o Fire.o Haubits.o EldFunkar.o EldFunkarProj.o Airokurtz.o Hao.o \
Jolt.o Plasma.o Box.o FloatingText.o Nurb.o Blaster.o Minuteman.o NukeMissile.o SpastOLW.o FloppyDisk.o Disk.o \
ZookabaProj.o FireBomb.o GasEel.o M6ton.o SolidLine.o GaussGun.o M7ton.o Grenade.o Phykoser.o Flashbang.o
OBJS += glew.o

LIBS = -L./ -L../ -lmingw32 -lSDLmain -lSDL -mwindows -g -static-libstdc++ -static-libgcc \
-Lglew-1.9.0/bin/ -lftgl -lfreetype -lglew32 -lopengl32 -lglu32
#static-tjossan är för att vissa bibliotek ska skickas med
#lägg till -g för att köra felsökning...

TEST = ImageFunctions_test.o

TARGET =	../NoMaintenanceRemake.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

glew.o: glew.c

glew.c:

%.o: ../%.cpp
	@$(CXX) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

sdl/SDL_mixer.o:
	echo hej

test: $(TEST)
	$(CXX) -o test $(TEST)
	./test