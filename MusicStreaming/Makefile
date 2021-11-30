CC=g++
CFLAGS=-c -ansi -Wall -pedantic-errors -O0

all: linkedlist musicstream

musicstream: main_musicstream.o album.o artist.o playlist.o profile.o song.o musicstream.o
	$(CC) main_musicstream.o album.o artist.o playlist.o profile.o song.o musicstream.o -o musicstream

linkedlist: main_linkedlist.o
	$(CC) main_linkedlist.o -o linkedlist

main_musicstream.o: main_musicstream.cpp
	$(CC) $(CFLAGS) main_musicstream.cpp -o main_musicstream.o

main_linkedlist.o: main_linkedlist.cpp
	$(CC) $(CFLAGS) main_linkedlist.cpp -o main_linkedlist.o

album.o: Album.cpp Album.h
	$(CC) $(CFLAGS) Album.cpp -o album.o

artist.o: Artist.cpp Artist.h
	$(CC) $(CFLAGS) Artist.cpp -o artist.o

playlist.o: Playlist.cpp Playlist.h
	$(CC) $(CFLAGS) Playlist.cpp -o playlist.o

profile.o: Profile.cpp Profile.h
	$(CC) $(CFLAGS) Profile.cpp -o profile.o

song.o: Song.cpp Song.h
	$(CC) $(CFLAGS) Song.cpp -o song.o

musicstream.o: MusicStream.cpp MusicStream.h Album.cpp Album.h Artist.cpp Artist.h Playlist.cpp Playlist.h Profile.cpp Profile.h Song.cpp Song.h LinkedList.h Node.h
	$(CC) $(CFLAGS) MusicStream.cpp -o musicstream.o

clean:
	rm *o
	rm linkedlist
	rm musicstream
