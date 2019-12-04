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

char Playlist::option = 'N';

void Playlist::addSong(Song &s1)
{

    lsong.push_back(s1);
}

void Playlist::deleteSong(Song &deletesong)
{

    bool valid;
    valid = false;
    for (int i = 0; i < lsong.size(); i++)
    { //Start of for loop
        if (lsong[i] == deletesong)
        {
            valid = true;
            lsong.erase(lsong.begin() + i);
        }
    } // End the loop
}

std::vector<Song> Playlist::getSong()
{
    return lsong;
}

void Playlist::intersect(Playlist &p2)
{

    Playlist result;
    bool valid;
    vector<Song> temp = p2.getSong();

    valid = false;

    for (int i = 0; i < lsong.size(); i++)
    {
        for (int j = 0; j < temp.size(); j++)
        {
            if (lsong[i] == temp[j] && search(result.getSong(), lsong[i]))

                valid = true;

            result.addSong(lsong[i]);
        }
    }
    //return result;
}

bool Playlist::search(vector<Song> b, Song &g)
{
    bool valid;

    valid = false;
    for (int i = 0; i < b.size(); i++)
        if (b[i] == g)
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

    for (int i = 0; i < temp.size(); i++)
    {

        valid = true;

        merge.addSong(temp[i]);
    }
    return Playlist(merge);
}

void Playlist::play()
{

    if (option == 'N' || option == 'n')
    {
        currentsong++;
        if (currentsong > lsong.size())
            cout << lsong[currentsong] << endl;
        else
            cout << "There are no more songs to play in the plalist.";
    }
    else if (option == 'R' || option == 'r')
    {
        cout << lsong[currentsong] << endl;
    }
    else if (option == 'L' || option == 'l')
    {
        currentsong++;
        if (currentsong > lsong.size())
            currentsong = 0;
        cout << lsong[currentsong] << endl;
    }
}

void Playlist::mode(char option)
{
    Playlist::option = option;
}

void Playlist::setPName(std::string pname)
{
    p_name = pname;
}
std::string Playlist::getPName()
{
    return p_name;
}
Playlist::Playlist()
{
    p_name = "";
}
Playlist::Playlist(std::string name)
{
    setPName(name);
    string play_listname = name + ".playlist";
    play_listname = StringHelper::stou(play_listname);

    ifstream in;
    in.open(play_listname.c_str());
    Song s;
    int k = 0;
    if (in)
    {
        while (in)
        {
            in >> s;
            cout << s << endl;
            lsong.push_back(s);
        }
    }
}
