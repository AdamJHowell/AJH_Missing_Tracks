/*
Title: Missing Tracks
Author: Adam Howell


This program is designed to read in a text file containing a directory structure and locate missing files.
It is currently hard-coded to search for track 1.
My filename format is as follows:
	<Artist> - <Album> - <Track#> - <Title>
When the program encounters track 2, it looks back one line (stored in a variable) for track 1.


Pseudo-code:

read line into currentLine
scan currentLine for " - 02 - "
if found
	cout << "Found track 2 in first line"
else
	lastLine = currentLine
read line from inFileObject into current line
scan currentLine for " - 02 - "
if found
	scan lastLine for " - 01 - "
	if !found
		cout << "Found track 2 with no track 1", outFileObject << currentLine
*/


#include <iostream>
#include <fstream>
#include <string>


using namespace std;


const string INFILENAME = "tracks.txt";		// Input filename.
const string OUTFILENAME = "outtracks.txt";	// Output filename.


int main()
{
	string currentLine = "";				// Current line contents.
	string lastLine = "";				// Previous line contents.
	int track1Count = 0;				// Counter for how many times a track 1 was found.
	int track2Count = 0;				// Counter for how many times a track 2 was found.
	int missingTracks = 0;				// Counter for how many tracks are missing.

	// Open a file stream based on the output filename.  This file will be overwritten without confirmation!
	ofstream outFile ( OUTFILENAME );

	// If the file stream creation failed...
	if ( outFile.fail() )
	{
		// Announce that the file did not open properly.
		cout << "\nUnable to open the " << OUTFILENAME << " file." << endl;
		// Pause so the user can read the error message on the console.
		system( "PAUSE" );
		// Exit the program with a return value of -1.
		return -1;
	}

	// Open a file stream based on the input filename.
	ifstream trackFile ( INFILENAME );

	// If the file stream creation failed...
	if ( trackFile.fail() )
	{
		// Announce that the file did not open properly.
		cout << "\nUnable to open the " << INFILENAME << " file.\nPlease ensure it is in the same directory as this executable." << endl;
		// Pause so the user can read the error message on the console.
		system( "PAUSE" );
		// Exit the program with a return value of -1.
		return -1;
	}
	else
	{
		// Loop until the end of the file.
		while ( !trackFile.eof() )
		{
			getline( trackFile, currentLine );
			//trackFile >> currentLine;	// This is how I initially tried loading a line from the input file to currentLine.
			// Scan currentLine for " - 02 - ".
			currentLine.find( " - 02 - " );
			// If we find track 2...
			if ( currentLine.find( " - 02 - " ) != string::npos )
			{
				track2Count++;
				// Test code.
				//cout << "Found track 2" << endl;
				// Scan lastLine for " - 01 - ", and if missing...
				if ( lastLine.find( " - 01 - " ) != string::npos )
				{
					// Increment track1Count to show we located a track 1.
					track1Count++;
				}
				else
				{
					// Load the current line into the output file.
					outFile << currentLine << endl;
					// Increment missingTracks to show we located a missing track 1.
					missingTracks++;
				}
			}
			else
			{
				// Prepare to check the next line by loading currentLine into lastLine.
				lastLine = currentLine;
				// Restart this while loop.
				continue;
			}
		}
	}
	// Close the file handles.
	trackFile.close();
	outFile.close();

	// Display the results.
	cout << "Found " << track1Count << " first tracks" << endl;
	cout << "Found " << track2Count << " second tracks" << endl;
	cout << missingTracks << " possible albums with missing first tracks written to " << OUTFILENAME << endl;

	// Pause so we can see the output on the console.
	system( "PAUSE" );

} // End main()
