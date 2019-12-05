//Name of the file: Player.cpp
//Group number and member names: Jeffrey Washington, Roderick Harris, Shatoria Poole
//Date last edited: 12/4/2019
//Purpose of the program: Player that plays songs from user created playlist, create new playlist, merge playlist, and intersect them.

//Header files
#include <fstream>
#include <iostream>
#include <string>
#include "Playlist.h"
#include "Song.h"
#include "StringHelper.h"

//Standard name space included
using namespace std;

//Structure to get filenames
struct songDetails
{
  string name;
  string filename;
};
//Function prototypes

void loadPlayList(vector<songDetails> &);
void displayPlaylists(vector<songDetails> &);
void addNewPlaylist(string, vector<songDetails> &);
bool Menu(Playlist &);
void deleteSong(Playlist &);
void addSong(Playlist &);
void mode_change();
Playlist playlistObject;

//Main program
int main()
{
  vector<songDetails> vectorOfSongs; //Vector data member to manipulate data
  loadPlayList(vectorOfSongs);

  Playlist playlistObject;
  int menuChoice;
  int selection;
  string newplaylist;

  //Beginning of program
  cout << "----------WELCOME to the AutoPlayer----------" << endl;
  do
  {
    do
    {
      cout << "1 - Open an exisiting playlist" << endl;
      cout << "2 - Create new list" << endl;
      cout << "3 - Exit" << endl;
      cout << "Selection: ";
      cin >> menuChoice;
    } while (menuChoice != 1 && menuChoice != 2 && menuChoice != 3);

    if (menuChoice == 1)
    {
      cout << "Please select a playlist from below: " << endl;
      displayPlaylists(vectorOfSongs);

      do
      {
        cout << "Selection: ";
        cin >> selection;
        if (selection < 1 || selection > vectorOfSongs.size())
          cout << "Invalid selection" << endl;
      } while (selection < 1 || selection > vectorOfSongs.size());
      cout << endl;
      Playlist p1(vectorOfSongs[selection - 1].name);

      Menu(p1); // calls menu
    }
    else if (menuChoice == 2)
    {
      do
      {
        cout << "1 - Create new empty list" << endl;
        cout << "2 - Merge 2 exisitng playlists" << endl;
        cout << "3 - Intersect 2 exisinting playlists" << endl;
        cout << "Selection: ";
        cin >> selection;
      } while (selection != 1 && selection != 2 && selection != 3);

      cin.ignore();

      cout << "Name of new playlist (cannot contain underscores): ";
      getline(cin, newplaylist);

      switch (selection)
      {
      case 1:
      {
        Playlist p;              //Create playlist playlistObjectect.
        p.setPName(newplaylist); // call set playlist name function
        addNewPlaylist(newplaylist, vectorOfSongs);
        Menu(p); // call menu
      }
      break;
      case 2:
      {
        cout << endl
             << "Which of the following playlists would you like to merge? " << endl;
        displayPlaylists(vectorOfSongs);
        int listOfSongs[2];

        for (int forLoopCounter = 0, j = 1; j < 3; j++, forLoopCounter++)
        {
          do
          {
            cout << "Playlist " << j << ": ";
            cin >> listOfSongs[forLoopCounter];
            if (listOfSongs[forLoopCounter] < 1 || listOfSongs[forLoopCounter] > vectorOfSongs.size())
              cout << "Invalid selection" << endl;

          } while (listOfSongs[forLoopCounter] < 1 || listOfSongs[forLoopCounter] > vectorOfSongs.size());
        }

        Playlist p1(vectorOfSongs[listOfSongs[0] - 1].name);
        Playlist p2(vectorOfSongs[listOfSongs[1] - 1].name);

        Playlist p3 = p1 + p2;

        p3.setPName(newplaylist);
        addNewPlaylist(newplaylist, vectorOfSongs);
        while (Menu(p3))
          ;
      }
      break;
      case 3:
      {
        cout << endl
             << "Which of the following playlists would you like to intersect? " << endl;
        displayPlaylists(vectorOfSongs);
        int listOfSongs[2];

        for (int forLoopCounter = 0, j = 1; j < 3; j++, forLoopCounter++)
        {
          do
          {
            cout << "Playlist " << j << ": ";
            cin >> listOfSongs[forLoopCounter];
            if (listOfSongs[forLoopCounter] < 1 || listOfSongs[forLoopCounter] > vectorOfSongs.size())
              cout << "Invalid selection" << endl;

          } while (listOfSongs[forLoopCounter] < 1 || listOfSongs[forLoopCounter] > vectorOfSongs.size());
        }

        Playlist p1(vectorOfSongs[listOfSongs[0] - 1].name);
        Playlist p2(vectorOfSongs[listOfSongs[1] - 1].name);

        Playlist p3 = p1.intersectPlaylist(p2);

        addNewPlaylist(newplaylist, vectorOfSongs);
        while (Menu(p3))
          ;
      }
      break;
      } // Switch cases end

      cout << endl;
    }
  } while (menuChoice != 3); // entire do loop is finished

  return 0; //terminates program
}

// Displaying playlist
void displayPlaylists(vector<songDetails> &vectorOfSongs)
{
  for (int forLoopCounter = 0, j = 1; forLoopCounter < vectorOfSongs.size(); forLoopCounter++, j++)
    cout << j << " " << vectorOfSongs[forLoopCounter].name << endl;
}
//Loads playlists into vector
void loadPlayList(vector<songDetails> &vectorOfSongs)
{

  ifstream in;
  in.open("Playlist.list");
  string filename;
  if (in)
  {

    while (in >> filename)
    {

      songDetails l = {StringHelper::utos(filename), filename};
      vectorOfSongs.push_back(l);
    }
  }
  else
  {
    cout << "Could not open Playlist.list" << endl;
  }
  in.close();
}
//Menu for the player
bool Menu(Playlist &playlist)
{
  bool menuOption;
  char menuChoice;

  do
  {
    menuOption = true;

    cout << "You are now playing: " << playlist.getPlaylistname() << endl;
    cout << "A - Add a song" << endl;
    cout << "D - Delete a song" << endl;
    cout << "P - Play a song" << endl;
    cout << "M - Set the mode" << endl;
    cout << "S - Show all songs" << endl;
    cout << "Q - Quit" << endl
         << "Selection: " << endl;
    cin >> menuChoice;

    switch (toupper(menuChoice))
    {
    case 'A':
      addSong(playlist);
      break;
    case 'D':
      deleteSong(playlist);
      break;
    case 'P':
    {
      cout << endl;
      cout << "NOW PLAYING:" << endl;
      playlistObject.play();
    }

    break;

    case 'M':
      mode_change();
      break;

    case 'S':
    {
      std::vector<Song> temp = playlist.getSong();

      for (int forLoopCounter = 0; forLoopCounter < temp.size(); forLoopCounter++)
        cout << temp[forLoopCounter] << endl;
    }

    break;
    }
  } while (menuChoice != 'Q' && menuChoice != 'q');
  return true;
}

//Adds a new playlist that can be manipulated
void addNewPlaylist(string playlistName, vector<songDetails> &v_song)
{
  songDetails listOfSongs = {playlistName, StringHelper::stou(playlistName)};
  v_song.push_back(listOfSongs);
  ofstream out;
  out.open("Playlist.list", ios::app);
  out << StringHelper::stou(playlistName) << endl;
  out.close();
}

//Adds a song to chosen playlist by the user.
void addSong(Playlist &playlist)
{
  cin.ignore();
  Song s; // Create song playlistObjectect
  cin >> s;
  string name = playlist.getPlaylistname();
  name + ".playlist";
  name = StringHelper::stou(name);

  playlist.addSong(s);
  ofstream out;

  out.open(name.c_str(), ofstream::app);
  out << s;
}

// Function erases the song from the playlist.
void deleteSong(Playlist &playlist)
{
  cin.ignore();
  string title, artist;
  cout << "Enter to delete: " << endl;
  cout << "Title: ";
  getline(cin, title);
  cout << "Artist: ";
  getline(cin, artist);

  Song delete_s(title, artist, "", 0, 0);
  playlist.deleteSong(delete_s);

  string name = playlist.getPlaylistname();
  name + ".playlist";
  name = StringHelper::stou(name);

  ofstream out;

  out.open(name.c_str());

  playlist.getSong();
  std::vector<Song> temp = playlist.getSong();

  for (int forLoopCounter = 0; forLoopCounter < temp.size(); forLoopCounter++)
    out << temp[forLoopCounter] << endl;
}

//Changes the mode of the playlists which dictates how the songs will paly.
void mode_change()
{
  bool good;

  do
  {
    good = true;

    cout << "Enter mode: " << endl;
    cout << "N - Normal" << endl;
    cout << "R - Repeat" << endl;
    cout << "L - Loop" << endl
         << "Selection: " << endl;
    char menuOption;
    cin >> menuOption;

    switch (toupper(menuOption))
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