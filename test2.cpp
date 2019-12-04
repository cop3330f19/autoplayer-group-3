#include <fstream>
#include <iostream>
#include <string>
//#include "Playlist.h"
#include "StringHelper.h"

using namespace std;

struct List{
        string name;
        string filename;
};


void loadPlayList(vector<List>&);
void displayPlaylists(vector<List>& );
void changeMode();
void addNewPlaylist(string, vector<List>& );


int main()
{
        vector<List> lists;
        loadPlayList(lists);
        displayPlaylists(lists);
}

void changeMode()
{
  bool good;

  do
  {
    good = true;

    cout << "Enter mode:\n"
      << "\tN - Normal\n"
      << "\tR - Repeat\n"
      << "\tL - Loop\nSelection: ";

    char m;
    cin >> m;

    switch(toupper(m))
    {
      case 'N':
        Playlist::setMode(0);
        break;
      case 'R':
        Playlist::setMode(1);
        break;
          case 'L':
                Playlist::setMode(2);
                break;
      default:
        good = false;
    }
  } while(!good);
}

void addNewPlaylist(string playlistName, vector<List>& list){
        List l = {playlistName, StringHelper::stou(playlistName)};
        list.push_back(l);
        ofstream out;
        out.open("Playlist.list", ios::app);
        out << StringHelper::stou(playlistName) << endl;
        out.close();
}


void displayPlaylists(vector<List>& list){
        for(int i =0, j = 1; i< list.size(); i++, j++)
                cout << j << " " <<  list[i].name << endl;
}
void loadPlayList(vector<List>& list){

        ifstream in;
        in.open("Playlist.list");
        string filename;
        if(in){

                while(in >> filename){

                        List l = {StringHelper::utos(filename),filename};
                        list.push_back(l);
                }

        }
        else{
                cout << "Could not open Playlist.list" << endl;
        }
        in.close();

}