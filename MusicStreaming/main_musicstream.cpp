#include <iostream>

#include "MusicStream.h"

int main() {
    MusicStream ms;

    ms.print();

    ms.addProfile("john@doe.com", "john_doe", free_of_charge);

    ms.print();

    ms.addArtist("The Beatles");

    ms.addAlbum("Please Please Me", 1);
    ms.addAlbum("A Hard Day's Night", 1);

    ms.addSong("I Saw Here Standing There", 175, 1);
    ms.addSong("Do You Want to Know a Secret", 116, 1);
    ms.addSong("Things We Said Today", 155, 2);
    ms.addSong("You Can't Do That", 155, 2);

    ms.print();

    return 0;
}
