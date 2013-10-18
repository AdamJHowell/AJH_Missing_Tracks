/*
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


const string INFILENAME = "tracks.txt";
const string OUTFILENAME = "outtracks.txt";


int main()
{
	string lastLine = "";
	string currentLine = "";
	int track1Count = 0;
	int track2Count = 0;
	int missingTracks = 0;


	ofstream outFile ( OUTFILENAME );

	if ( outFile.fail() )
	{
		// Announce that the file did not open properly.
		cout << "\nUnable to open the " << OUTFILENAME << " file." << endl;
		// Pause so the user can read the error message.
		system( "PAUSE" );
		// Exit the program with a return value of -1.
		return -1;
	}

	
	ifstream trackFile ( INFILENAME );

	if ( trackFile.fail() )
	{
		// Announce that the file did not open properly.
		cout << "\nUnable to open the " << INFILENAME << " file.\nPlease ensure it is in the same directory as this executable." << endl;
		// Pause so the user can read the error message.
		system( "PAUSE" );
		// Exit the program with a return value of -1.
		return -1;
	}
	else
	{
		while ( !trackFile.eof() )
		{
			getline( trackFile, currentLine );
			//trackFile >> currentLine;
			// Scan currentLine for " - 02 - ".
			currentLine.find( " - 02 - " );
			// If found...
			if ( currentLine.find( " - 02 - " ) != string::npos )
			{
				track2Count++;
				//cout << "Found track 2" << endl;
				// Scan lastLine for " - 01 - ".
				if (lastLine.find( " - 01 - " ) != string::npos)
				{
					track1Count++;
				}
				else
				{
					outFile << currentLine << endl;
					missingTracks++;
				}
			}
			else
			{
				// Prepare to check the next line.
				lastLine = currentLine;
				// Restart this while loop.
				continue;
			}
		}
	}
	trackFile.close();
	outFile.close();

	cout << "Found " << track1Count << " first tracks" << endl;
	cout << "Found " << track2Count << " second tracks" << endl;
	cout << missingTracks << " possible albums with missing first tracks written to " << OUTFILENAME << endl;

	system( "PAUSE" );
} // End main()
