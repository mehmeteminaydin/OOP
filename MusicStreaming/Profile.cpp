#include "Profile.h"

Profile::Profile(const std::string &email, const std::string &username, SubscriptionPlan plan) {
    this->email = email;
    this->username = username;
    this->plan = plan;
}

const std::string &Profile::getUsername() const {
    return this->username;
}

const std::string &Profile::getEmail() const {
    return this->email;
}

SubscriptionPlan Profile::getPlan() const {
    return this->plan;
}

LinkedList<Playlist> &Profile::getPlaylists() {
    return this->playlists;
}

LinkedList<Profile *> &Profile::getFollowings() {
    return this->following;
}

LinkedList<Profile *> &Profile::getFollowers() {
    return this->followers;
}

void Profile::setPlan(SubscriptionPlan plan) {
    this->plan = plan;
}

void Profile::followProfile(Profile *profile) {
    /* TODO */
    following.insertAtTheEnd(profile);
}

void Profile::unfollowProfile(Profile *profile) {
    /* TODO */
    following.removeNode(profile);
}

void Profile::createPlaylist(const std::string &playlistName) {
    /* TODO */
    Playlist newPlaylist(playlistName);
    playlists.insertAtTheEnd(newPlaylist);
}

// check it again
void Profile::deletePlaylist(int playlistId) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            //remove songs firstly
            this->playlists.getNodeAtIndex(i)->data.getSongs().removeAllNodes();
            // then remove playlist object 
            this->playlists.removeNode(playlists.getNodeAtIndex(i));
            return;
        }
    }
}

void Profile::addSongToPlaylist(Song *song, int playlistId) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            this->playlists.getNodeAtIndex(i)->data.addSong(song);
            return;
        }
    }
}

void Profile::deleteSongFromPlaylist(Song *song, int playlistId) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            this->playlists.getNodeAtIndex(i)->data.dropSong(song);
            return;
        }
    }
}

Playlist *Profile::getPlaylist(int playlistId) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            return &(playlists.getNodeAtIndex(i)->data);
        }
    }
}


LinkedList<Playlist *> Profile::getSharedPlaylists() {
    /* TODO */
    LinkedList<Playlist *> SharedPlayLists;
    for(int i = 0; i < following.getSize(); i++){
        for(int j = 0; j < following.getNodeAtIndex(i)->data->getPlaylists().getSize(); j++){
            if(following.getNodeAtIndex(i)->data->getPlaylists().getNodeAtIndex(j)->data.isShared()){
                SharedPlayLists.insertAtTheEnd(&(following.getNodeAtIndex(i)->data->getPlaylists().getNodeAtIndex(j)->data));
            }
        }
    }
    return SharedPlayLists;
}

void Profile::shufflePlaylist(int playlistId, int seed) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            this->playlists.getNodeAtIndex(i)->data.getSongs().shuffle(seed);
        }
    }
}

void Profile::sharePlaylist(int playlistId) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            this->playlists.getNodeAtIndex(i)->data.setShared(true);
        }
    }
}

void Profile::unsharePlaylist(int playlistId) {
    /* TODO */
    for(int i = 0; i < playlists.getSize(); i++){
        if(playlists.getNodeAtIndex(i)->data.getPlaylistId() == playlistId){
            this->playlists.getNodeAtIndex(i)->data.setShared(false);
        }
    }
}

bool Profile::operator==(const Profile &rhs) const {
    return this->email == rhs.email && this->username == rhs.username && this->plan == rhs.plan;
}

bool Profile::operator!=(const Profile &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Profile &profile) {
    os << "email: " << profile.email << " |";
    os << " username: " << profile.username << " |";
    if (profile.plan == free_of_charge) {
        os << " plan: " << "free_of_charge" << " |";
    } else if (profile.plan == premium) {
        os << " plan: " << "premium" << " |";
    } else {
        os << " plan: " << "undefined" << " |";
    }

    os << " playlists: [";
    Node<Playlist> *firstPlaylistNode = profile.playlists.getFirstNode();
    Node<Playlist> *playlistNode = firstPlaylistNode;
    if (playlistNode) {
        do {
            os << playlistNode->data;
            if (playlistNode->next != firstPlaylistNode) os << ", ";
            playlistNode = playlistNode->next;
        } while (playlistNode != firstPlaylistNode);
    }
    os << "] |";
    os << " following: [";
    Node<Profile *> *firstProfileNode = profile.following.getFirstNode();
    Node<Profile *> *profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "] |";
    os << " followers: [";
    firstProfileNode = profile.followers.getFirstNode();
    profileNode = firstProfileNode;
    if (profileNode) {
        do {
            os << profileNode->data->getEmail();
            if (profileNode->next != firstProfileNode) os << ", ";
            profileNode = profileNode->next;
        } while (profileNode != firstProfileNode);
    }
    os << "]";

    return os;
}
