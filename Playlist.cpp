//Name of the file: Player.cpp
//Group number and member names: Jeffrey Washington, Roderick Harris, Shatoria Poole
//Date last edited: 12/4/2019
//Purpose of the program: Player that plays songs from user created playlist, create new playlist, merge playlist, and intersect them.

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Playlist.h"
#include "Song.h"
#include "StringHelper.h"

using namespace std;

char Playlist::option = 'N'; //Normal is the mode for the playlist

void Playlist::addSong(Song &s1)
{
    listOfSongs.push_back(s1); // Songs pushed back in vector
}

void Playlist::deleteSong(Song &deletesong)
{

    bool valid;
    valid = false;
    for (int iterator = 0; iterator < listOfSongs.size(); iterator++)
    {
        if (listOfSongs[iterator] == deletesong)
        {
            valid = true;
            listOfSongs.erase(listOfSongs.begin() + iterator);
        }
    }
}

vector<Song> Playlist::getSong()
{
    return listOfSongs;
}

Playlist Playlist::intersectPlaylist(Playlist &p2)
{

    Playlist result;
    bool valid;
    vector<Song> temp = p2.getSong();

    valid = false;

    for (int iterator = 0; iterator < listOfSongs.size(); iterator++) //Function sees what songs are similar between playlists .
    {                                                                 //and returns a playlist which contains all the similar songs
        for (int forLoopIterator = 0; forLoopIterator < temp.size(); forLoopIterator++)
        {
            if (listOfSongs[iterator] == temp[forLoopIterator] && search(result.getSong(), listOfSongs[iterator]))

                valid = true;

            result.addSong(listOfSongs[iterator]);
        }
    }
    return result;
}

bool Playlist::search(vector<Song> b, Song &g) //Linear search for songs.
{
    bool valid;

    valid = false;
    for (int iterator = 0; iterator < b.size(); iterator++)
        if (b[iterator] == g)
            valid = true;
    return valid;
}

Playlist operator+(Playlist &p1, Playlist &p2)
{
    Playlist merge;
    merge = p1;
    bool valid;
    vector<Song> temp = p2.getSong();

    valid = false;

    for (int iterator = 0; iterator < temp.size(); iterator++)
    {

        valid = true;

        merge.addSong(temp[iterator]);
    }
    return Playlist(merge);
}
Playlist operator+(Playlist &p1, Song &s1)
{
    Playlist a1;
    a1 = p1;
    a1.addSong(s1);
    return Playlist(a1);
}

Playlist operator-(Playlist &p1, Song &s1)
{
    Playlist d1;
    d1 = p1;
    d1.deleteSong(s1);
    return d1;
}

ostream &operator<<(ostream &os, const Playlist &p1)
{
    for (int iterator = 0; iterator < p1.listOfSongs.size(); iterator++)
    {
        os << p1.listOfSongs[iterator];
    }
    return os;
}

void Playlist::play() //Function prints the song based on the modes.
{
    if (option == 'N' || option == 'n')
    {
        currentSongInPlaylist++;
        if (currentSongInPlaylist < listOfSongs.size())
            cout << listOfSongs[currentSongInPlaylist] << endl;
        else

            cout << "There are no more songs to play in the plalist." << endl;
    }
    else if (option == 'R' || option == 'r')
    {
        cout << listOfSongs[currentSongInPlaylist] << endl;
    }
    else if (option == 'L' || option == 'l')
    {
        currentSongInPlaylist++;
        if (currentSongInPlaylist > listOfSongs.size())
            currentSongInPlaylist = 0;
        cout << listOfSongs[currentSongInPlaylist] << endl;
    }
}

void Playlist::mode(char option)
{
    Playlist::option = option;
}

void Playlist::setPName(string pname)
{
    p_name = pname;
}
string Playlist::getPlaylistname()
{
    return p_name;
}
Playlist::Playlist() //base contructor
{
    p_name = "";
}
Playlist::Playlist(string name) //overloaded constructor
{
    setPName(name);
    string play_listname = name + ".playlist";
    play_listname = StringHelper::stou(play_listname);

    fstream in;
    in.open(play_listname.c_str(), ios::in);
    Song s;
    int k = 0;
    while (in >> s)
    {

        listOfSongs.push_back(s);
    }
    in.close();
}
