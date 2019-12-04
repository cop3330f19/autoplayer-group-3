#include <fstream>
#include <iostream>
#include <string>
#include "Playlist.h"
#include "StringHelper.h"

using namespace std;

struct List{
        string name;
        string filename;
};

void loadPlayList(vector<List>&);
void displayPlaylists(vector<List>& );
void addSong(Playlist&);
void deleteSong(Playlist&);
void changeMode();
void addNewPlaylist(string, vector<List>& );
bool playMenu(Playlist& );

int main()
{
        vector<List> lists;
        int selection;
        int choice;

        loadPlayList(lists);



        cout << endl << "----------WELCOME to the AutoPlayer----------" << endl << endl;

        do{
                cout << "You currently have " << lists.size() << " playlist(s).\n";

                do{
                        cout << "1 - Open an exisiting playlist\n2 - Create new list\n3 - Exit\nSelection: ";
                        cin >> choice;
                }while(choice != 1 && choice != 2 && choice != 3);

            // Opening Existing playlist
            
                if(choice == 1){
                        cout << "Please select a playlist from below: \n";
                        displayPlaylists(lists);
                        do{
                                cout << "Selection: ";
                                cin >> selection;
                                if(selection < 1 || selection > lists.size())
                                        cout << "Invalid selection" << endl;

                        }while(selection < 1 || selection > lists.size());

                        //load Playlist object
                        Playlist p(lists[selection - 1].name);

                        //display play menu
                        while(playMenu(p));

                }
                else if(choice == 2)
                {
                        do{
                                cout << "\n1 - Create new empty list\n2 - Merge 2 exisitng playlists\n3 - Intersect 2 exisinting playlists\nSelection: ";
                                cin >> selection;
                        }while(selection != 1 && selection != 2 && selection !=3);

                        cin.ignore();

                        string playlistName;
                        cout << "\nName of new playlist (cannot contain underscores): ";
                        getline(cin, playlistName);



                        switch(selection){
                                case 1:
                                        {
                                                Playlist p;
                                                p.setName(playlistName);
                                                addNewPlaylist(playlistName, lists);
                                                while(playMenu(p));
                                        }
                                        break;
                                case 2:
                                        {
                                                cout << "\nWhich of the following playlists would you like to merge? " << endl;
                                                displayPlaylists(lists);
                                                int pLists[2];

                                                for(int i =0, j =1; j < 3; j++, i++){
                                                        do{
                                                                cout << "Playlist " << j << ": ";
                                                                cin >> pLists[i];
                                                                if(pLists[i] < 1 || pLists[i] > lists.size())
                                                                        cout << "Invalid selection" << endl;

                                                        }while(pLists[i] < 1 || pLists[i] > lists.size());
                                                }

                                                Playlist p1(lists[pLists[0] - 1].name);
                                                Playlist p2(lists[pLists[1] - 1].name);

                                                Playlist p3 = p1 + p2;

                                                p3.setName(playlistName);
                                                p3.writeToFile(p3);
                                                addNewPlaylist(playlistName, lists);
                                                while(playMenu(p3));
                                        }
                                        break;
                                case 3:
                                        {
                                                cout << "\nWhich of the following playlists would you like to intersect? " << endl;
                                                displayPlaylists(lists);
                                                int pLists[2];

                                                for(int i =0, j =1; j < 3; j++, i++){
                                                        do{
                                                                cout << "Playlist " << j << ": ";
                                                                cin >> pLists[i];
                                                                if(pLists[i] < 1 || pLists[i] > lists.size())
                                                                        cout << "Invalid selection" << endl;

                                                        }while(pLists[i] < 1 || pLists[i] > lists.size());
                                                }

                                                Playlist p1(lists[pLists[0] - 1].name);
                                                Playlist p2(lists[pLists[1] - 1].name);

                                                Playlist p3 = p1.intersect(p2, playlistName);

                                                addNewPlaylist(playlistName, lists);
                                                while(playMenu(p3));
                                        }
                                        break;
                        }
                }

                cout << endl;

        }while(choice != 3);

        return 0;
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
void addSong(Playlist& play_list)
{
  Song s;
  cout << "Song Details \n";
  cin >> s;

  play_list.addSong(s);
}
void deleteSong(Playlist& play_list)
{
        cin.ignore();

        string title, artist;
        cout << "Enter to delete: \n";
        cout << "Title: ";
        getline(cin, title);
        cout << "Artist: ";
        getline(cin, artist);

        Song del_song(title, artist, "", 0, 0);

    if(play_list.deleteSong(del_song))
    {
      cout << "Song successfully deleted\n";
    }
    else
    {
      cout << "No such song exists\n";
    }
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

bool playMenu(Playlist& play_list)
{
  bool good;

  do
  {
    good = true;

    cout << "\nYou are now playing: " << play_list.getName() << "\n"
      << "\tA - Add a song\n"
      << "\tD - Delete a song\n"
      << "\tP - Play a song\n"
      << "\tM - Set the mode\n"
      << "\tS - Show all songs\n"
      << "\tQ - Quit\nSelection: ";

    char choice;
    cin >> choice;

    switch(toupper(choice))
    {
    case 'A':
      addSong(play_list);
      break;

    case 'D':
      deleteSong(play_list);
      break;

    case 'P':
                {
                        cout << "\nNOW PLAYING:\n";
                        play_list.play( );
                }

      break;

    case 'M':
      changeMode();
      break;

    case 'S':
      //play_list.showAll( );
      cout << play_list;
      break;

  case 'Q':
    return false;

    default:
      good = false;
    }
  } while(!good);

  return true;
}