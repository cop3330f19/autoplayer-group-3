//Name of the file: Player.cpp
//Group number and member names: Jeffrey Washington, Roderick Harris, Shatoria Poole
//Date last edited: 12/4/2019
//Purpose of the program: Player that plays songs from user created playlist, create new playlist, merge playlist, and intersect them.

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include "Song.h"
#include "Playlist.h"
#include "StringHelper.h"

using namespace std;

//Constructors
Song::Song()
{
    title = "";
    artist = "";
    album = "";
    length = 0;
    year = 0;
}

Song::Song(string title, string artist, string album, int length, int year)
{
    set(title, artist, album, length, year);
}

void Song::set(string title, string artist, string album, int length, int year)
{
    this->title = title;
    this->artist = artist;
    this->album = album;
    this->length = length;
    this->year = year;
}

ostream &operator<<(ostream &os, const Song &song)
{
    os << song.title << " " << song.artist << " " << song.album << " " << song.year << " " << song.length; // output to console
    return os;
}
ofstream &operator<<(ofstream &os, const Song &song)
{
    os << song.title << "," << song.artist << "," << song.album << "," << song.year << "," << song.length; //output to file
    return os;
}

fstream &operator>>(fstream &is, Song &song)
{ //input from file
    string placeholder;

    getline(is, song.title, ',');
    getline(is, song.artist, ',');
    getline(is, song.album, ',');
    getline(is, placeholder, ',');
    song.year = atoi(placeholder.c_str());
    getline(is, placeholder);
    song.length = atoi(placeholder.c_str());

    return is;
}

istream &operator>>(istream &is, Song &song)
{

    //is.ignore();
    cout << "Song Details \n";
    cout << "Title: \n";
    getline(is, song.title);
    cout << "Artist: \n";
    getline(is, song.artist);
    cout << "Album: \n";
    getline(is, song.album);
    cout << "Year: \n";
    is >> song.year;
    cout << "Length (in seconds): \n";
    is >> song.length;
    return is;
}

bool operator==(const Song &lhs, const Song &rhs)
{
    return (lhs.title == rhs.title && lhs.artist == rhs.artist); // compare two song objects for equality
}
