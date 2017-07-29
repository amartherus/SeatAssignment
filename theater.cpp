#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//reads the given file
void readFile(vector<string> & requests)
{
  string filename = "sample-input.txt";
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
	  theater[i][j] = 's';
	}
    }

}

//algorithm for seat assignment
void assignSeat(string & request, char theater[][20])
{
  int numPeeps = request[5] - '0';
  cout << request.substr(0, 4) << " ";

  int i;
  char row;
  int j;
  int col;

  //iterate rows
  for(i = 0, row = 'A'; i < 10; i++) 
    {
      //iterate columns
      for(j = 0, col = 1; j < 20; j++)
	{
	  //look for empty seats
	  if(theater[i][j] == 's')
	    {
	      //set seat to filled
	      theater[i][j] = 'x';
	      cout << row << col << ", ";
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

  cout << "Theater is full!!!" << endl;
  
} 

int main()
{
  //read all contents of file into a vector of strings
  vector<string> requests;
  readFile(requests);

  //we need a data structure to hold our 10x20 theater
  char theater[10][20];
  createTheater(theater);

  //assign seats one request at a time
  for(int i = 0; i < requests.size(); i++)
  {
    assignSeat(requests[i], theater);
  }
  return 0;
}
