// Trevor Lastelick

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <string>
using std::istringstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::fstream;

int counter = 0;

vector<int> parseInts(string str);

int createProcess(vector<vector <int> > vec);
void printProcess(int process);
int createResourceTypes(vector<vector <int > > vec);
void printResourceTypes(int resourceTypes);
vector <vector <int> > createAllocationMatrix(vector<vector <int> > vec);
void printAllocationMatrix(vector<vector <int> > vec);
vector<vector <int> > createMaxMatrix(vector<vector <int> > vec);
void printMaxMatrix(vector<vector <int> > vec);
vector<vector <int> > createNeedMatrix(vector<vector <int> > allocation, vector<vector <int> > max);
void printNeedMatrix(vector<vector <int> > vec);
vector<int> createAvailableVector(vector<vector <int> > vec);
void printAvailableVector(vector<int> vec);
bool computeSafeState(vector<vector <int> > allocation, vector<vector <int> > need, vector<int> available);
vector<int> createRequestVector(vector<vector <int> > vec);
void printRequestVector(vector<int> requestVector);
void computeRequest(vector<int> available, vector<int> request, vector<vector <int> > allocation, vector<vector<int> > need);


using namespace std;

int main ()
{
    vector<int> smallVec;
    vector<vector<int> > bigVec;
    string str = "";
   
    int process = 0;
    int resourceTypes = 0; 
    vector<vector <int> > allocationMatrix;
    vector<vector <int> > maxMatrix;
    vector<vector <int> > needMatrix;
    vector<int> availableVector;
    bool safe = false;
    vector<int> requestVector;

        fstream file;
        file.open("matrix.txt");
        
        
        
        while (file)
        {
            getline(file, str, '\n');         // Get a line from the file.
            smallVec = parseInts(str);       // Tokenize all the ints from that line. 
            bigVec.push_back(smallVec);      // Add each token to a vector.

            // Stop last line from being copied twice.
            if( file.eof() ) 
            break; 
        }

            process = createProcess(bigVec);
            resourceTypes = createResourceTypes(bigVec);
            allocationMatrix = createAllocationMatrix(bigVec);
            maxMatrix = createMaxMatrix(bigVec);
            needMatrix = createNeedMatrix(allocationMatrix, maxMatrix);
            availableVector = createAvailableVector(bigVec);
            safe = computeSafeState(allocationMatrix, needMatrix, availableVector);
            requestVector = createRequestVector(bigVec);

            printProcess(process);
            printResourceTypes(resourceTypes);
            printAllocationMatrix(allocationMatrix);
            printMaxMatrix(maxMatrix);
            printNeedMatrix(needMatrix);
            printAvailableVector(availableVector);
            
            if (safe)
              cout << "THE SYSTEM IS IN A SAFE STATE\n\n\n";
            else
              cout << "THE SYSTEM IS NOT IN A SAFE STATE\n\n\n";
            
            printRequestVector(requestVector);
            computeRequest(availableVector, requestVector, allocationMatrix, needMatrix);

            /*
            // Print the matrix 
            cout << "Testing allocation matrix:!!" << endl;
            for (int i=0; i< bigVec.size(); i++)
            {
                cout << i << ": ";
                for (int j=0; j<bigVec[i].size(); j++)
                    cout << bigVec[i][j] << " ";
            
                cout << endl;
            }
            */

        


    return 0;
}

vector<int> parseInts(string str)
{
   vector<int> d;                 // vector of integers.
   

   istringstream ss(str);          // stringstream, initialize with str

   string temp;   

   while ( ss >> temp )           // loop while a string can be extracted from ss
   {
       istringstream st(temp);     // another stringstream, contains just one 'word'

       while ( st  )              // loop while status of stringstream is good
       {
           int i;
           if (st >> i)           // try to read an integer 
               d.push_back(i);    // success, store it
           else
           {
               st.clear();        // failed, so reset status flags
               st.get();          // read and discard a single char
           }
        }               
   }
   
   return d;                      // return result
}

int createProcess(vector<vector <int> > vec)
{
    int process = 0;

    process = vec[0][0];

    return process;

}

void printProcess(int process)
{
    cout << "There are " << process << " processes in the system.\n\n\n";
}

int createResourceTypes(vector<vector <int > > vec)
{
    int resourceTypes = 0;

    resourceTypes = vec[2][0];

    return resourceTypes;
}

void printResourceTypes(int resourceTypes)
{
    cout << "There are " << resourceTypes << " resource types.\n\n\n";
}

vector <vector <int> > createAllocationMatrix(vector<vector <int> > vec)
{
    vector<vector <int> > allocationMatrix;

    for (int i=4; i<9; i++)
        allocationMatrix.push_back(vec[i]);

    return allocationMatrix;
}

void printAllocationMatrix(vector<vector <int> > vec)
{
    counter = 0;
    cout << "The Allocation Matrix is..." << endl << endl;
    cout << "   " << "A " << "B " << "C " << "D" << endl << endl;

    for (int i=0; i<vec.size(); i++)
    {
        cout << i << ": ";

        for (int j=0; j<vec[i].size(); j++)
            cout << vec[i][j] << " ";

        cout << endl << endl;
    } 

    cout << endl << endl;

}

vector<vector <int> > createMaxMatrix(vector<vector <int> > vec)
{
    vector<vector <int> > maxMatrix;

    for (int i=10; i<15; i++)
        maxMatrix.push_back(vec[i]);

    return maxMatrix;
}

void printMaxMatrix(vector<vector <int> > vec)
{
    cout << "The Max Matrix is..." << endl << endl;
    cout << "   " << "A " << "B " << "C " << "D" << endl << endl;
    
    for (int i=0; i<vec.size(); i++)
    {
        cout << i << ": ";

        for (int j=0; j<vec[i].size(); j++)
            cout << vec[i][j] << " ";
            
        cout << endl << endl;
    
    }
    
    cout << endl << endl << endl; 
    
}

vector<vector <int> > createNeedMatrix(vector<vector <int> > allocation, vector<vector <int> > max)
{
    vector<vector <int> > needMatrix;
    vector<int> tempVec;
    int temp = 0;
    
    for (int i=0; i<allocation.size(); i++)
    {
        for (int j=0; j<allocation[i].size(); j++)
            tempVec.push_back(max[i][j] - allocation[i][j]);


        needMatrix.push_back(tempVec);
        tempVec.clear();                  // clear contents of the vector.
    }

    return needMatrix;
}

void printNeedMatrix(vector<vector <int> > vec)
{
    cout << "The Need Matrix is..." << endl << endl;
    cout << "   " << "A " << "B " << "C " << "D" << endl << endl;
    
    for (int i=0; i<vec.size(); i++)
    {
        cout << i << ": ";

        for (int j=0; j<vec[i].size(); j++)
            cout << vec[i][j] << " ";
            
        cout << endl << endl;
    
    }
    
    cout << endl << endl << endl; 
}

vector<int> createAvailableVector(vector<vector <int> > vec)
{
  vector<int> availableVector;

  for (int i=16; i<17; i++)
  {
    for (int j=0; j<vec[i].size(); j++)
      availableVector.push_back(vec[i][j]);
  }
  
  return availableVector;
}

void printAvailableVector(vector<int> vec)
{
  cout << "The Available Vector is..." << endl << endl;
    cout << "A " << "B " << "C " << "D" << endl << endl;
    
    for (int i=0; i<vec.size(); i++)
            cout << vec[i] << " ";
    
    cout << endl << endl << endl; 
}

bool computeSafeState(vector<vector <int> > allocation, vector<vector <int> > need, vector<int> available)
{
  int counter = 0;
  int flag = false;
  int row = 0;
  
  // Cycle through the rows several times.
  while (counter < 16)
  {
  
      // True if an individual row satisfies criteria 
      for (int j=0; j<need[row].size(); j++)
      {
        if (need[row][j] <= available[j])
        { 
          flag = true;
        } 
        else
          flag = false;
          
      cout << endl;
      }
    
    // Add resources allocated back into available
    if (flag == true)
    {

        // Add resources to the available pool.
        for (int j=0; j<allocation[row].size(); j++)
          available.at(j) += allocation[row][j];
          
        // Remove resources from the allocation pool.
        allocation[row].clear();
        
        for (int i=0; i<4; i++)
          allocation[row].push_back(0);
    }
        
        row++;    // Move onto the next row.
        
        // Reset row count
        if (row == 5)
          row = 0;
        
        
        counter++;
  } // end while

    return flag;
  
}

vector<int> createRequestVector(vector<vector <int> > vec)
{
  vector<int> requestVector;
  
  for (int i=18; i<19; i++)
  {
    for (int j=1; j<5; j++)
      requestVector.push_back(vec[i][j]);
  }

  return requestVector;

}

void printRequestVector(vector<int> requestVector)
{
  cout << "The Request Vector is...\n\n\n";
  cout << "  A B C D\n\n";
  cout << "1:";
  
  for (int i=0; i<requestVector.size(); i++)
    cout << requestVector[i] << " ";
    
  cout << endl << endl;
}

void computeRequest (vector<int> available, vector<int> request, vector<vector <int> > allocation, vector<vector<int> > need)
{
  
  vector<int> newAvailable;
  vector<int> newAllocation;
  vector<int> newNeed;
  
  int temp1 = 0;
  int temp2 = 0;
  
  // Available = available - request.
  for (int i=0; i<available.size(); i++)
  {
    temp1 = available[i];
    temp2 = request[i];
    newAvailable.push_back(temp1 - temp2);
  }
  
  // Allocation = allocation + request.
    for (int j=0; j<request.size(); j++)
      {
        temp1 = allocation[0][j];
        temp2 = request[j];
        newAllocation.push_back(temp1 + temp2);
      }
    
  // Need = need - request.
  for (int i=0; i<request.size(); i++)
  {
    temp1 = need[0][i];
    temp2 = request[i];
    newNeed.push_back(temp1 - temp2);
  }
  
  
  // Check if still in a safe state. 
  
  int counter = 0;
  int flag = false;
  int row = 0;
  
  // Cycle through the rows several times.
  
  // True if an individual row satisfies criteria 
      for (int j=0; j<request.size(); j++)
      {
        if (newNeed[j] <= newAvailable[j])
        { 
          flag = true;
        } 
        else
          flag = false;
          
      cout << endl;
      }
    
    if (flag == true)
      cout << "THE REQUEST CAN BE GRANTED\n\n\n";
    
    cout << "The Available Vector is...\n\n";
    cout << "A B C D" << endl;
    for (int i=0; i<request.size();i++)
      cout << newAvailable[i] << " ";
      
}
