# Group Project 2 - AutoPlayer

*Groups remain the same as the last project*
GitHub link https://classroom.github.com/g/3XAeKD9l

***Due: Thursday December 5th, 2019 (12:30 PM).***

## Objective
This assignment will give you practice with:
- composition of objects
- operator overloading
- this pointer
- static and const members
- vectors of objects

## Task
You will be writing a class that represents a playlist of songs.  Your Playlist class will manage a vector of song objects.  The Song class H file is provided for you.
**Do not change any function definitions or implementations provided.**

You will write a class called Playlist implemented in files playlist.h and playlist.cpp.
Your Playlist class will support two basic uses:
- Mangaing the playlist.  This includes adding and deleting songs.
- Playing from the play list.  This includes keeping track of which is the next song to be played and supporting different playing modes (such as normal and repeat).  Obviously we will not actually be playing any music.  "Playing" the song will consist of printing the name.

The driver program Player.cpp will allow you to manage multiple playlists and switch between them.

## Program Details and Requirements:

### Song Class
You must write the implementation of the Song.h file.
Two songs are equal if they have the same title and artist.

### Playlist Class
There is **no size limit** on the playlist, so it should be implemented with a vector. 

Your class must provide the appropriate accessor and mutator functions. Only include mutator functions for members that absolutely need one.

Your class must provide the following member functions:

1. addSong - This function will take a Song object as a parameter and insert it into the play list.
1. deleteSong - This function will take a Song object as a parameter and search the play list for it. If it is found, it should be removed and the function should return true.  If it is not found, a value of false should be returned.  If the play list has multiple copies of one song, you should just delete all copies.
1. intersect - This function will take a Playlist object as a parameter and return a new playlist that is the intersection of the songs in the playlist argument (the playlist passed in by the caller) and the songs contained within the playlist object in which Intersect been called (calling object).  That is, the new playlist  will contain all songs that are common to both playlists (with no duplicates).
1. merge - This function will take a Playlist object as a parameter and return a new playlist that merges the songs in the playlist argument (the playlist passed in by the caller) and the songs contained within the playlist object which metch been called (calling object). This playlist will contain all songs, including duplicates.
1. play - This function will play one song from the play list.  This simply involves printing a message, along with the song name.  The first time the Play function is called, it should play the song at index 0.  Later calls should play other songs depending on the current mode.
1. setMode - This function will change the playing mode of the play list.  Your class will have to keep track of the playing mode and the song that is currently being played.

The three modes are:
|Mode|Meaning|
|---|---|
|NORMAL|After playing this song, the next song to be played is the next sequential song. For example after playing song with index 7, the next song to be played is the song at index 8.  If the last song is played, the next song should be song 0.|
|REPEAT|After playing this song, the next song to be played will still be this song.|
|LOOP| Restart playlist after it ends.|


Your class must also overload the following operators and implement the described functionality accordingly:

1. **Addition operator (+)** 
	The addition operator will have two meanings depending on the arguments supplied by the caller:
	- **adding a song to a playlist (i.e. playlist object + song object)**
		This version will return a new playlist object.  The returned playlist will be a concatenation of all songs in the caller's playlist and the single song.  The single song object will be at the end of the newly created playlist.
	- **adding two playlists (i.e. playlist object + playlist object)**
		This version will also return a new playlist object. The returned playlist will be a concatenation of the two playlist objects passed in by the caller.

1. **Subtraction operator (-)**
	The subtraction operator will have only one meaning:
	- **removing a song(s) from a playlist (i.e. playlist object - song object)**
		This version will return a new playlist object.  The returned playlist will be all songs in the caller's playlist with **any** instances of the song passed in by the caller removed.
1. **Output operator (<<)**
	The output operator will have one meaning:
	- **displaying all song(s) in a playlist**
		This version will print a list of all songs to the console window.
		
          
### Driver Program
Your driver program should allow users to create new named playlist, view all the playlists, merge (intersect) exisiting playlists into a new list, and play a playlist.
A list of all created playlists should be stored in a file "Playlist.list". The songs in each playlist should be stored in a file named to match the list and the file extension ".playlist". This is a CSV format. 
There should be a menu of options. Run the `./playlist` to see the sample. 

#### General Requirements:

- No global variables, other than constants
- All member data of your class must be private
- Use the `const` and `static` qualifier on member functions and parameters wherever it is appropriate.
- When you write source code, it should be readable and well-documented.
- Your Playlist.h file should contain the class declaration only & The playlist.cpp file should contain the member function definitions.

#### Hints:

1. Run the sample code and test all the functionalities. ***Pay attention to the expect output formats.***
1. The description does not include all possible member variables and functions needed.
1. Mode should persist across all playlists.
1. Make your operator overloads friends of your classes.
1. You will need file manipulation functions in both the Playlist class and the Player driver files.
1. Use a vector/array to keep track of all playlists.

## Documentation Requirements:
The documentation must include the follow:
1.	Cover Page (provided; fill in all information; each page should have the same header/footer)
2.	Table of Contents 
3.	Grade Sheet (last pages of document)
4.	Flowchart (1 per function, not including accessors and mutators)
5.	Description of the major inputs, outputs, and processes.
6.	The code
	1.	Well commented code (follow function comments in the code provided, StringHelper.h)
	1.	The top of each file should include:
		1.	Name of the file
		1.	Group number and member names
		1.	Date last edited
		1.	Purpose of the program