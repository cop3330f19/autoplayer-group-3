#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

#include "Song.h"
#include "Playlist.h"
#include "StringHelper.h"

using namespace std;

Song::Song()
{
    title = "";
    artist = "";
    album = "";
    length = 0;
    year = 0;
}

Song::Song(std::string title, std::string artist, std::string album, int length, int year)
{
    set(title, artist, album, length, year);
}

void Song::set(std::string title, std::string artist, std::string album, int length, int year)
{
    this->title = title;
    this->artist = artist;
    this->album = album;
    this->length = length;
    this->year = year;
}

std::ostream &operator<<(std::ostream &os, const Song &song)
{
    os << song.title << " " << song.artist << " " << song.album << " " << song.year << " " << song.length << endl;
    return os;
}

std::ofstream &operator<<(std::ofstream &os, const Song &song)
{
    os << song.title << "," << song.artist << "," << song.album << "," << song.year << "," << song.length << endl;
}

std::istream &operator>>(std::istream &is, Song &song)
{
    string title, artist, album;
    int year, length;
    cout << "Song Details \n";
    cout << "Title: \n";
    getline(is, title);
    cout << "Artist: \n";
    getline(is, artist);
    cout << "Album: \n";
    getline(is, album);
    cout << "Year: \n";
    is >> year;
    cout << "Length (in seconds): \n";
    is >> length;
    song.set(title,artist, album, length, year);
    return is;
}

std::ifstream &operator>>(std::ifstream &is, Song &song)
{
    string temp;

    getline(is, temp, ',');
    song.title = temp;
    getline(is, temp, ',');
    song.artist = temp;
    getline(is, temp, ',');
    song.album = temp;
    getline(is, temp, ',');
    song.year = atoi(temp.c_str());
    getline(is, temp);
    song.length = atoi(temp.c_str());
    return is;
}

bool operator == (const Song &lhs, const Song &rhs)
{
    return (lhs.title == rhs.title && lhs.artist == rhs.artist);
}
