#include "MusicStream.h"

#include <iostream>

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    /* TODO */
    Profile newUser = Profile(email, username, plan);
    profiles.insertAtTheEnd(newUser);
}

void MusicStream::deleteProfile(const std::string &email) {
    /* TODO */

    for(int i = 0; i < profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            // first remove this profile from it's followers' following lists
            
            for(int j = 0; j< profiles.getNodeAtIndex(i)->data.getFollowers().getSize(); j++){
                
                for (int k =0; k < profiles.getNodeAtIndex(i)->data.getFollowers().getNodeAtIndex(j)->data->getFollowings().getSize(); k++){
                    profiles.getNodeAtIndex(i)->data.getFollowers().getNodeAtIndex(j)->data->getFollowings().removeNode(&(profiles.getNodeAtIndex(i)->data));
                }
            }
            // second, remove this profile from its following' followers lists
            for(int j = 0; j< profiles.getNodeAtIndex(i)->data.getFollowings().getSize(); j++){
                for (int k =0; k < profiles.getNodeAtIndex(i)->data.getFollowings().getNodeAtIndex(j)->data->getFollowers().getSize(); k++){
                    profiles.getNodeAtIndex(i)->data.getFollowings().getNodeAtIndex(j)->data->getFollowers().removeNode(&(profiles.getNodeAtIndex(i)->data));
                }
            }
            // delete profile contents

            //first delete playlists
            for(int l = 0; l < profiles.getNodeAtIndex(i)->data.getPlaylists().getSize(); l++){
                profiles.getNodeAtIndex(i)->data.deletePlaylist(l);
            }
            // secondly, delete followers
            profiles.getNodeAtIndex(i)->data.getFollowers().removeAllNodes();
            
            // third, delete followings
            profiles.getNodeAtIndex(i)->data.getFollowings().removeAllNodes();
            // delete profile from musicStream
            profiles.removeNode(profiles.getNodeAtIndex(i));
            break;
        }
        
    }
}


void MusicStream::addArtist(const std::string &artistName) {
    /* TODO */
    Artist newArtist(artistName);
    artists.insertAtTheEnd(newArtist);
}

void MusicStream::addAlbum(const std::string &albumName, int artistId) {
    /* TODO */
    // create and add album object to the albums linked list
    Album newAlbum(albumName);
    albums.insertAtTheEnd(newAlbum);
    // add this album to the artist's albums list
    for(int i =0; i< artists.getSize(); i++){
        if(artists.getNodeAtIndex(i)->data.getArtistId() == artistId){
            artists.getNodeAtIndex(i)->data.addAlbum(&(albums.getLastNode()->data));
            return;
        }
    }
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId) {
    /* TODO */
    Song newSong(songName, songDuration);
    // first insert new song to the songs linked list
    songs.insertAtTheEnd(newSong);
    // second, insert it into the appropriate album list
    for(int i =0; i< albums.getSize(); i++){
        if(albums.getNodeAtIndex(i)->data.getAlbumId() == albumId){
            albums.getNodeAtIndex(i)->data.addSong(&(songs.getLastNode()->data));
            return;
        }
    }

}

void MusicStream::followProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    int profile1;
    int profile2;
    
    // first find intended profiles
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email1){
            profile1 = i;
        }
        else if(profiles.getNodeAtIndex(i)->data.getEmail() == email2){
            profile2 = i;
        }
    }
    // insert profile2 to profile1's following list
    profiles.getNodeAtIndex(profile1)->data.getFollowings().insertAtTheEnd(&(profiles.getNodeAtIndex(profile2)->data));
    // insert profile1 to profile2's followers list
    profiles.getNodeAtIndex(profile2)->data.getFollowers().insertAtTheEnd(&(profiles.getNodeAtIndex(profile1)->data));
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2) {
    /* TODO */
    int profile1;
    int profile2;
    
    // first find intended profiles
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email1){
            profile1 = i;
        }
        else if(profiles.getNodeAtIndex(i)->data.getEmail() == email2){
            profile2 = i;
        }
    }
    // insert profile2 to profile1's following list
    profiles.getNodeAtIndex(profile1)->data.getFollowings().removeNode(&(profiles.getNodeAtIndex(profile2)->data));
    // insert profile1 to profile2's followers list
    profiles.getNodeAtIndex(profile2)->data.getFollowers().removeNode(&(profiles.getNodeAtIndex(profile1)->data));
}


void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName) {
    /* TODO */
    // find the intended user by checking the email
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            // insert newly created playlist to Playlists list of the user
            profiles.getNodeAtIndex(i)->data.createPlaylist(playlistName);
            break;
        }
    }
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            // delete specified playlist from Playlists list of the user
            profiles.getNodeAtIndex(i)->data.deletePlaylist(playlistId);
            break;
        }
        
    }

}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            for(int j =0; j <songs.getSize();j++){
                if(songs.getNodeAtIndex(j)->data.getSongId() == songId){
                    profiles.getNodeAtIndex(i)->data.addSongToPlaylist(&(songs.getNodeAtIndex(j)->data),playlistId);
                    //profiles.getNodeAtIndex(i)->data.getPlaylist(playlistId)->addSong(&(songs.getNodeAtIndex(j)->data));
                    return;
                }
            }

        }
    }
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            for(int j =0; j <songs.getSize();j++){
                if(songs.getNodeAtIndex(j)->data.getSongId() == songId){
                    profiles.getNodeAtIndex(i)->data.deleteSongFromPlaylist(&(songs.getNodeAtIndex(j)->data),playlistId);
                    return;
                }
            }
        }
    }
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            if(profiles.getNodeAtIndex(i)->data.getPlan() == free_of_charge){
                LinkedList<Song *> listWithAdv;
                listWithAdv = playlist->getSongs();
                listWithAdv.insertAsEveryKthNode(&Song::ADVERTISEMENT_SONG,2);
                return listWithAdv;
            }
            else if(profiles.getNodeAtIndex(i)->data.getPlan() == premium){
                return playlist->getSongs();
            }
        }
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            return profiles.getNodeAtIndex(i)->data.getPlaylist(playlistId);
        }
    }
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            return profiles.getNodeAtIndex(i)->data.getSharedPlaylists();
        }
    }
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            profiles.getNodeAtIndex(i)->data.shufflePlaylist(playlistId,seed);
            break;
        }
    }
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            profiles.getNodeAtIndex(i)->data.sharePlaylist(playlistId);
            break;
        }
    }
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            profiles.getNodeAtIndex(i)->data.unsharePlaylist(playlistId);
            break;
        }
    }
}

void MusicStream::subscribePremium(const std::string &email) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            profiles.getNodeAtIndex(i)->data.setPlan(premium);
            break;
        }
    }
    
}

void MusicStream::unsubscribePremium(const std::string &email) {
    /* TODO */
    for(int i = 0; i< profiles.getSize(); i++){
        if(profiles.getNodeAtIndex(i)->data.getEmail() == email){
            profiles.getNodeAtIndex(i)->data.setPlan(free_of_charge);
            break;
        }
    }
}

void MusicStream::print() const {
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}
