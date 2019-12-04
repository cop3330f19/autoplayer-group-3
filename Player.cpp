#include <fstream>
#include <iostream>
#include <string>
#include "Playlist.h"
#include "Song.h"
#include "StringHelper.h"

using namespace std;

struct songList
{
  string name;
  string filename;
};

void loadPlayList(Playlist &, vector<songList> &);
void displayPlaylists(vector<songList> &);
void addNewPlaylist(string, vector<songList> &);
bool Menu(Playlist &);
void delete_Song(Playlist &);
void add_Song(Playlist &);
void mode_change();
Playlist obj;
int main()
{
  vector<songList> v_songs;

  loadPlayList(obj, v_songs);
  

  int choice;
  int select;
  string newplaylist;
  cout << "----------WELCOME to the AutoPlayer----------" << endl;
  cout << "You currently have 4 playlist(s)." << endl;

  do
  {
    cout << "1 - Open an exisiting playlist" << endl;
    cout << "2 - Create new list" << endl;
    cout << "3 - Exit" << endl;
    cout << "Selection: ";
    cin >> choice;
  } while (choice != 1 && choice != 2 && choice != 3);

  if (choice == 1)
  {
    cout << "Please select a playlist from below: \n";
    displayPlaylists(v_songs);

    do
    {
      cout << "Selection: ";
      cin >> select;
      if (select < 1 || select > v_songs.size())
        cout << "Invalid selection" << endl;
    } while (select < 1 || select > v_songs.size());
    cout << endl;
    Playlist p1(v_songs[select - 1].name);

    Menu(p1);
  }
  else if (choice == 2)
  {
    do
    {
      cout << "1 - Create new empty list" << endl;
      cout << "2 - Merge 2 exisitng playlists" << endl;
      cout << "3 - Intersect 2 exisinting playlists" << endl;
      cout << "Selection: ";
      cin >> select;
    } while (select != 1 && select != 2 && select != 3);

    cin.ignore();

    cout << "Name of new playlist (cannot contain underscores): ";
    getline(cin, newplaylist);
  }

  switch (select)
  {
  case 1:
  {
    Playlist p;
    p.setPName(newplaylist);
  //  addNewPlaylist(newplaylist, v_songs);
    Menu(p);
  }
  break;
  case 2:
  {
    cout << "\nWhich of the following playlists would you like to merge? " << endl;
    displayPlaylists(v_songs);
    int list[2];

    for (int i = 0, j = 1; j < 3; j++, i++)
    {
      do
      {
        cout << "Playlist " << j << ": ";
        cin >> list[i];
        if (list[i] < 1 || list[i] > v_songs.size())
          cout << "Invalid selection" << endl;

      } while (list[i] < 1 || list[i] > v_songs.size());
    }

    Playlist p1(v_songs[list[0] - 1].name);
    Playlist p2(v_songs[list[1] - 1].name);

    Playlist p3 = p1 + p2;

    p3.setPName(newplaylist);
    //(NEEDS TO BE FIXED) p3.writeToFile(p3, *******?);
    addNewPlaylist(newplaylist, v_songs);
    while (Menu(p3))
      ;
  }
  break;
  case 3:
  {
    cout << "\nWhich of the following playlists would you like to intersect? " << endl;
    displayPlaylists(v_songs);
    int pLists[2];

    for (int i = 0, j = 1; j < 3; j++, i++)
    {
      do
      {
        cout << "Playlist " << j << ": ";
        cin >> pLists[i];
        if (pLists[i] < 1 || pLists[i] > v_songs.size())
          cout << "Invalid selection" << endl;

      } while (pLists[i] < 1 || pLists[i] > v_songs.size());
    }

    Playlist p1(v_songs[pLists[0] - 1].name);
    Playlist p2(v_songs[pLists[1] - 1].name);

    //(NEEDS TO BE FIXED) Playlist p3 = p1.intersect(p2, *****?);

    addNewPlaylist(newplaylist, v_songs);
    //while(Menu(p3));
  }
  break;
  }

  cout << endl;

  while (choice != 3)
    ;

  return 0;
}

void displayPlaylists(vector<songList> &v_songs)
{
  for (int i = 0, j = 1; i < v_songs.size(); i++, j++)
    cout << j << " " << v_songs[i].name << endl;
}

void loadPlayList(Playlist &objTemp, vector<songList> &v_songs)
{

  ifstream in;
  in.open("Playlist.list");
  string filename;
  if (in)
  {

    while (in >> filename)
    {

      songList l = {StringHelper::utos(filename), filename};
      v_songs.push_back(l);
    }
      
  }
  else
  {
    cout << "Could not open Playlist.list" << endl;
  }
  in.close();
}

bool Menu(Playlist &playlist)
{
  bool option;
  char choice;

  do
  {
    option = true;

    cout << "You are now playing: " << playlist.getPName() << endl;
    cout << "A - Add a song" << endl;
    cout << "D - Delete a song" << endl;
    cout << "P - Play a song" << endl;
    cout << "M - Set the mode" << endl;
    cout << "S - Show all songs" << endl;
    cout << "Q - Quit\nSelection: " << endl;

    cin >> choice;

    switch (toupper(choice))
    {
    case 'A':
      add_Song(playlist);
      break;

    case 'D':
      delete_Song(playlist);
      break;
    case 'P':
    {
      cout << endl;
      cout << "NOW PLAYING:" << endl;
      obj.play();
    }

    break;

    case 'M':
      mode_change();
      break;

    case 'S':
    {
      std::vector<Song> temp = playlist.getSong();

      for (int i = 0; i < temp.size(); i++)
        cout << temp[i] << endl;
    }

    break;

    default:
      choice = false;
    }
  } while (choice != 'Q' && choice != 'q');
  return true;
}
void addNewPlaylist(string playlistName, vector<songList> &v_song)
{
  songList list = {playlistName, StringHelper::stou(playlistName)};
  v_song.push_back(list);
  ofstream out;
  out.open("Playlist.list", ios::app);
  out << StringHelper::stou(playlistName) << endl;
  out.close();
}
void add_Song(Playlist &playlist)
{
  cin.ignore();
  Song s;
  cin >> s;
  string name = playlist.getPName();
  name + ".playlist";
  name = StringHelper::stou(name);

  playlist.addSong(s);
  ofstream out;

  out.open(name.c_str(), ofstream::app);
  out << s;
}
void delete_Song(Playlist &playlist)
{
  cin.ignore();
  //bool good;
  //good = false;
  string title, artist;
  cout << "Enter to delete: " << endl;
  cout << "Title: ";
  getline(cin, title);
  cout << "Artist: ";
  getline(cin, artist);

  Song delete_s(title, artist, "", 0, 0);
  playlist.deleteSong(delete_s);

  string name = playlist.getPName();
  name + ".playlist";
  name = StringHelper::stou(name);

  ofstream out;

  out.open(name.c_str());

  playlist.getSong();
  std::vector<Song> temp = playlist.getSong();

  for (int i = 0; i < temp.size(); i++)
    out << temp[i] << endl;

  /*if(obj.deleteSong(delete_s))
    good = true;
    if(true){
      cout << "Song successfully deleted" << endl;
    }
    else
    {
      cout << "No such song exists" << endl;
    }*/
}

void mode_change()
{
  bool good;

  do
  {
    good = true;

    cout << "Enter mode: " << endl;
    cout << "N - Normal" << endl;
    cout << "R - Repeat" << endl;
    cout << "L - Loop\nSelection: " << endl;
    char option;
    cin >> option;

    switch (toupper(option))
    {
    case 'N':
      Playlist::mode(0);
      break;
    case 'R':
      Playlist::mode(1);
      break;
    case 'L':
      Playlist::mode(2);
      break;
    default:
      good = false;
    }
  } while (!good);
}