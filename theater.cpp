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

void fillPrioritySeats(string & request, char theater[][20], int & numPeeps,
		       bool & isFirst)
{
  int i;
  char row;
  int j;
  int col;
  if(numPeeps == 0)
      return;

  //iterate rows
  for(i = 3, row = 'D'; i < 10; i++) 
    {
      //iterate columns
      for(j = 5, col = 6; j < 15; j++)
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

void fillLeftEdge(string & request, char theater[][20], int & numPeeps,
		  bool & isFirst)
{
  int i;
  char row;
  int j;
  int col;
  
  if(numPeeps == 0)
    return;

    //iterate rows
  for(i = 3, row = 'D'; i < 10; i++) 
    {
      //iterate columns
      for(j = 0, col = 1; j < 5; j++)
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
void fillRightEdge(string & request, char theater[][20], int & numPeeps,
		   bool & isFirst)
{
  int i;
  char row;
  int j;
  int col;

  if(numPeeps == 0)
      return;
  

    //iterate rows
  for(i = 3, row = 'D'; i < 10; i++) 
    {
      //iterate columns
      for(j = 15, col = 16; j < 20; j++)
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

void fillFrontSeats(string & request, char theater[][20], int & numPeeps,
		    bool & isFirst)
{
  int i;
  char row;
  int j;
  int col;
  if(numPeeps == 0)
      return;
  

    //iterate rows
  for(i = 0, row = 'A'; i < 3; i++) 
    {
      //iterate columns
      for(j = 0, col = 1; j < 20; j++)
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

//algorithm for seat assignment
void assignSeat(string & request, char theater[][20])
{
  int numPeeps = request[5] - '0';
  cout << request.substr(0, 4) << " ";
  bool isFirst = true;

  fillPrioritySeats(request, theater, numPeeps, isFirst);
  fillLeftEdge(request, theater, numPeeps, isFirst);
  fillRightEdge(request, theater, numPeeps, isFirst);
  fillFrontSeats(request, theater, numPeeps, isFirst);

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
