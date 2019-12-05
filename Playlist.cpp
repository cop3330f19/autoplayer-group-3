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

/**************************************************************
	 *                          addSong                          *
	 *                                                            *
	 * Passed   : song object                   *
	 * Purpose  : add song to vector                     *
	 * Returns  : nothing.                                          *
	 **************************************************************/

void Playlist::addSong(Song &s1)
{
    listOfSongs.push_back(s1); // Songs pushed back in vector
}

/**************************************************************
	 *                          deleteSong                          *
	 *                                                            *
	 * Passed   : song object                   *
	 * Purpose  : deletes song from playlist                     *
	 * Returns  : nothing                                         *
	 **************************************************************/

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

/**************************************************************
	 *                          toString                          *
	 *                                                            *
	 * Passed   : nothing                   *
	 * Purpose  : gets list of songs for playlist                     *
	 * Returns  : vector                                          *
	 **************************************************************/

vector<Song> Playlist::getSong()
{
    return listOfSongs;
}

/**************************************************************
	 *                          intersectPlaylist                          *
	 *                                                            *
	 * Passed   : playlist object                  *
	 * Purpose  : sees which songs are similar and returns a new playlist                     *
	 * Returns  : playlist object                                          *
	 **************************************************************/

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

/**************************************************************
	 *                          search                          *
	 *                                                            *
	 * Passed   : vector of songs and song object                   *
	 * Purpose  : Linear search for songs.                    *
	 * Returns  : Boolean value                                          *
	 **************************************************************/

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

/**************************************************************
	 *                          play                          *
	 *                                                            *
	 * Passed   : nothing                   *
	 * Purpose  : Prints song based on modes                   *
	 * Returns  : nothing                                          *
	 **************************************************************/

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

/**************************************************************
	 *                          mode                       *
	 *                                                            *
	 * Passed   : character                   *
	 * Purpose  : changes mode of player                     *
	 * Returns  : nothing                                       *
	 **************************************************************/

void Playlist::mode(char option)
{
    Playlist::option = option;
}

/**************************************************************
	 *                          setPname                          *
	 *                                                            *
	 * Passed   : string                  *
	 * Purpose  : Sets playlist name                     *
	 * Returns  : nothing                                   *
	 **************************************************************/

void Playlist::setPName(string pname)
{
    playlistName = pname;
}
/**************************************************************
	 *                          getPlaylistName                          *
	 *                                                            *
	 * Passed   : nothing                   *
	 * Purpose  : returns playlist name                     *
	 * Returns  : String                                          *
	 **************************************************************/
string Playlist::getPlaylistname()
{
    return playlistName;
}

//Constructors

Playlist::Playlist()
{
    playlistName = "";
}
Playlist::Playlist(string name)
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
