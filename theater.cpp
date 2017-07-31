#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//reads the given file
void readFile(vector<string> & requests, char filename[])
{
  //standard open file stuff
  ifstream fin (filename);
    if (fin.is_open())
      {
	string temp;

	//gets every line in the file
	while (getline(fin, temp))
	  {
	    requests.push_back(temp);
	    //increment vector location
	  }
	fin.close();
      }

    else 
      cout << "Unable to open file";    
}

//this just fills an array of chars with "empty" values
void createTheater(char theater[][20])
{
  for(int i = 0; i < 10; i++)
    {
      for(int j = 0; j < 20; j++)
	{
	  theater[i][j] = 'o';
	}
    }

}

//this just fills an array of chars with "empty" values
void displayTheater(char theater[][20])
{
  for(int i = 0; i < 10; i++)
    {
      for(int j = 0; j < 20; j++)
	{
	  cout << theater[i][j];
	}
      cout << endl;
    }

}

void fillSection(string & request, char theater[][20], int & numPeeps,
		 bool & isFirst, int section)
{
  int i;
  char row;
  int j;
  int col;
  int startCol = (section / 5) * 2;
  int startRow = ((section - 1) % 4) * 5;

  if(numPeeps == 0)
      return;
  
    //iterate rows
  for(i = startCol, row = 'A' + startCol; i < startCol + 2; i++) 
    {
      //iterate columns
      for(j = startRow, col = 1 + startRow; j < startRow + 5; j++)
	{
	  //look for empty seats
	  if(theater[i][j] == 'o')
	    {
	      //set seat to filled
	      theater[i][j] = 'x';

	      if(isFirst)
		{
		  cout << row << col;
		  isFirst = false;
		}
	      else
		cout << ", " << row << col;
	      numPeeps--;
	    }
	  if(numPeeps == 0)
	    {
	      cout << endl;
	      return;
	    }
	  col++;
	} //end inner for loop
      row++;
    } //end outer for loop

}

bool isEnoughSpace(char theater[][20], int section, int numPeeps)
{
  int count = 0;
  int startCol = (section / 5) * 2;
  int startRow = ((section - 1) % 4) * 5;

  for(int i = startCol; i < startCol + 2; i++)
    for(int j = startRow; j < startRow + 5; j++)
      if(theater[i][j] == 'o')
	count++;

  if(numPeeps > count)
    return true;
  else
    return false;
}

//algorithm for seat assignment
void assignSeat(string & request, char theater[][20])
{
  int numPeeps = request[5] - '0';
  int sections[20] = {10, 11, 14, 15, 18, 
			  19, 9, 12, 13, 16, 
			  17, 20, 6, 7, 5, 
			  8, 2, 3, 1, 4};

  cout << request.substr(0, 4) << " ";
  bool isFirst = true;

  int i = 0;
  //find which section to insert to
  while(isEnoughSpace(theater, sections[i], numPeeps) && i < 21)
    {
      i++;
    }

  if(i > 20)
    {
      cout << "Sold out!!!" << endl;
      return;
    }

  //fill seats with section algorithm
  fillSection(request, theater, numPeeps, isFirst, sections[i]);      
  
  if(numPeeps != 0)
    cout << "Sold Out!!!" << endl;

} 

int main(int argc, char*argv[])
{
  //read all contents of file into a vector of strings
  vector<string> requests;
  cerr << argc << endl;

  //if we received a commandline filename, read it
  if(argc > 1)
    readFile(requests, argv[1]);
  else
    {
      cout << "Please give a filename!\n";
      return 0;
    }

  //we need a data structure to hold our 10x20 theater
  char theater[10][20];
  createTheater(theater);

  //assign seats one request at a time
  for(int i = 0; i < requests.size(); i++)
  {
    assignSeat(requests[i], theater);
  }

  /*  //check which seats are filled
  for (int i = 0; i < 10; i++)
    {
      for(int j = 0; j < 20; j++)
	{
	  cout << theater[i][j];
	}
      cout << endl;
      }*/
  return 0;
}
