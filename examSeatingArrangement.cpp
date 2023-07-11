#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

class ClassroomGrid
{
public:
	int gridSize = 0;
	int noOfStudentsSeated = 0;
	int currentRow = 0;
	vector<vector<int> > ClassroomVector;

public:
	ClassroomGrid(int setGridSize, int setnoOfStudentsSeated, int setCurrentRow)
	{
		gridSize = setGridSize;
		noOfStudentsSeated = setnoOfStudentsSeated;
		currentRow = setCurrentRow;
		ClassroomVector.resize(gridSize, vector<int>(gridSize));
	}
};

int CalculateNoOfConflicts(vector<vector<int> > ClassroomVector, int gridSize)
{
	int noOfConflicts = 0;

	int noOfStudents = 0;
	int row = 0;
	int column = 0;

	//Check Row for current column
	for (row = 0; row < gridSize; row++)
	{
		bool teacherOnLeft = false;
		for (column = 0; column < gridSize; column++)
		{
			if (ClassroomVector[row][column] == 1)
			{
				noOfStudents++;
				teacherOnLeft = false;
				if (noOfStudents == 2 && teacherOnLeft == false)
				{
					break;
				}
			}
			else if (ClassroomVector[row][column] == 2)
			{
				teacherOnLeft = true;
				noOfStudents = 0;
			}
		}
		if (noOfStudents >= 2)
		{
			noOfConflicts++;
		}
		noOfStudents = 0;
	}

	//Check for horizontal row
	for (column = 0; column <= gridSize; column++)
	{
		bool teacherOnLeft = false;
		for (row = 0; row < gridSize; row++)
		{
			if (ClassroomVector[row][column] == 1)
			{
				noOfStudents++;
				teacherOnLeft = false;
				if (noOfStudents == 2 && teacherOnLeft == false)
				{
					break;
				}
			}
			else if (ClassroomVector[row][column] == 2)
			{
				teacherOnLeft = true;
				noOfStudents = 0;
			}
		}
		if (noOfStudents >= 2)
		{
			noOfConflicts++;
		}
		noOfStudents = 0;
	}


	//Check Upper Diagonal
	for (int diagonal = 0; diagonal < 2 * gridSize - 1; ++diagonal)
	{
		bool teacherOnLeft = false;
		int noOfElements = 0;

		if (diagonal < gridSize)
		{
			noOfElements = 0;
		}
		else
		{
			noOfElements = diagonal - gridSize + 1;
		}
		for (int j = noOfElements; j <= diagonal - noOfElements; ++j) {

			int diaognalElement = ClassroomVector[j][diagonal - j];

			if (diaognalElement == 1)
			{
				noOfStudents++;
				teacherOnLeft = false;
				if (noOfStudents == 2 && teacherOnLeft == false)
				{
					break;
				}

			}
			else if (diaognalElement == 2)
			{
				teacherOnLeft = true;
				noOfStudents = 0;
			}
		}
		if (noOfStudents >= 2)
		{
			noOfConflicts++;
		}
		noOfStudents = 0;
	}

	//Check down side diagonal
	for (int diagonal = 0; diagonal < 2 * gridSize - 1; ++diagonal)
	{
		int noOfElements = 0;
		bool teacherOnLeft = false;
		if (diagonal < gridSize)
		{
			noOfElements = 0;
		}
		else
		{
			noOfElements = diagonal - gridSize + 1;
		}
		for (int j = noOfElements; j <= diagonal - noOfElements; ++j) {

			int diaognalElement = ClassroomVector[j][(gridSize - 1) - (diagonal - j)];

			if (diaognalElement == 1)
			{
				noOfStudents++;
				teacherOnLeft = false;
				if (noOfStudents == 2 && teacherOnLeft == false)
				{
					break;
				}
			}
			else if (diaognalElement == 2)
			{
				teacherOnLeft = true;
				noOfStudents = 0;
			}
		}
		if (noOfStudents >= 2)
		{
			noOfConflicts++;
		}
		noOfStudents = 0;
	}

	return noOfConflicts;
}

bool CheckSafePosition(vector<vector<int> > ClassroomVector, int row, int column, int gridSize)
{
	if (ClassroomVector[row][column] == 2)
		return false;

	int i, j;
	//Check for current column upward
	for (i = row; i >= 0; i--)
	{
		if (ClassroomVector[i][column] == 1)
		{
			return false;
		}
		else if (ClassroomVector[i][column] == 2)
		{
			break;
		}
	}

	//Check for current column downward
	for (i = row; i < gridSize; i++)
	{
		if (ClassroomVector[i][column] == 1)
		{
			return false;
		}
		else if (ClassroomVector[i][column] == 2)
		{
			break;
		}
	}

	//Check for horizontal row to the left
	for (i = column; i >= 0; i--)
	{
		if (ClassroomVector[row][i] == 1)
		{
			return false;
		}
		else if (ClassroomVector[row][i] == 2)
		{
			break;
		}
	}

	//Check for horizontal row to the right
	for (i = column; i < gridSize; i++)
	{
		if (ClassroomVector[row][i] == 1)
		{
			return false;
		}
		else if (ClassroomVector[row][i] == 2)
		{
			break;
		}
	}

	//Check Upper Diagonal Upside
	for (i = row, j = column; i >= 0 && j >= 0; i--, j--)
	{
		if (ClassroomVector[i][j] == 1)
		{
			return false;
		}
		else if (ClassroomVector[i][j] == 2)
		{
			break;
		}
	}

	//Check Upper Diagonal Downside
	for (i = row, j = column; i < gridSize && j < gridSize; i++, j++)
	{
		if (ClassroomVector[i][j] == 1)
		{
			return false;
		}
		else if (ClassroomVector[i][j] == 2)
		{
			break;
		}
	}

	//Check down side diagonal Upside
	for (i = row, j = column; j < gridSize && i >= 0; i--, j++)
	{
		if (ClassroomVector[i][j] == 1)
		{
			return false;
		}
		else if (ClassroomVector[i][j] == 2)
		{
			break;
		}
	}

	//Check down side diagonal downside
	for (i = row, j = column; i < gridSize && j >= 0; i++, j--)
	{
		if (ClassroomVector[i][j] == 1)
		{
			return false;
		}
		else if (ClassroomVector[i][j] == 2)
		{
			break;
		}
	}
	return true;
}

//Check if goal is found
bool ChecGoalState(ClassroomGrid grid, int noOfStudents)
{
	if (grid.noOfStudentsSeated == noOfStudents)
		return true;
	else
		return false;
}

bool CheckRowForAllteachers(vector<vector<int> > vector, int row, int gridSize)
{
	int teacherCount = 0;
	if ((row < gridSize))
	{
		for (int i = 0; i < gridSize; i++)
		{
			if (vector[row][i] == 2)
				teacherCount++;
		}
	}

	if (gridSize == teacherCount)
	{
		return true;
	}
	return false;
}

ClassroomGrid FindDFSSolution(ClassroomGrid Classroom, int gridSize, int noOfStudents, bool rootNode)
{
	if (ChecGoalState(Classroom, noOfStudents))
	{
		return Classroom;
	}
	else
	{
		for (int row = 0; row < gridSize; row++)
		{
			for (int column = 0; column < gridSize; column++)
			{
				if (CheckSafePosition(Classroom.ClassroomVector, row, column, gridSize))
				{
					Classroom.ClassroomVector[row][column] = 1;
					Classroom.noOfStudentsSeated += 1;
					Classroom.currentRow = row;

					ClassroomGrid finalClassroomGrid = FindDFSSolution(Classroom, gridSize, noOfStudents, rootNode);

					if (finalClassroomGrid.noOfStudentsSeated != 0)
					{
						return finalClassroomGrid;
					}

					if (Classroom.noOfStudentsSeated > 0)
					{
						Classroom.noOfStudentsSeated--;
						if (Classroom.currentRow != 0)
							Classroom.currentRow--;
						Classroom.ClassroomVector[row][column] = 0;
					}
				}
			}
		}
	}
	return ClassroomGrid(0, 0, 0);
}

int main()
{
	queue<ClassroomGrid> ClassroomQueue;
	vector<vector<int> > ff9={{0,0,2,0,0,0,0,0},
                              {0,0,0,0,0,2,0,0},
                              {0,0,0,0,0,0,0,0},
                              {0,0,0,0,2,0,0,0},
                              {0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,2,0,0},
                              {0,0,0,0,0,0,0,0},
                              {0,0,0,2,0,0,0,0},
                             };
    vector<vector<int> > G1={{0,0,0,0,0,0,2,0,0,0,0,0},
                             {0,2,0,0,0,0,0,0,0,2,0,0},
                             {0,0,0,2,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,2,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,2,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,2,0,0,0,0,0,2,0,2,0},
                             {0,0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,2,0,0,0,0,0},
                             {0,0,2,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,2,0},
                            };

    vector<vector<int> > LT3={{0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0},
                              {0,0,0,2,0,2,0,0,0,0,0,0,2,0,0,0},
                              {0,2,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
                              {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
                              {0,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0},
                              {0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
                              {0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0},
                              {0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,0},
                              {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0},
                              {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
                              {2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0},
                              {0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2},
                              {0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0},
                              {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0},
                              {0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
                             };

    vector<vector<int> > ff9full={{1,0,2,1,0,0,0,0},
                                  {0,0,0,0,0,2,1,0},
                                  {0,0,0,0,1,0,0,0},
                                  {0,1,0,0,2,0,0,1},
                                  {0,0,0,0,0,1,0,0},
                                  {0,0,1,0,0,2,0,0},
                                  {0,0,0,0,0,1,0,0},
                                  {0,0,0,2,0,0,0,0},
                                 };

    vector<vector<int> > G1full={{1,0,0,0,0,0,2,1,0,0,0,0},
                                 {0,2,1,0,0,0,0,0,0,2,1,0},
                                 {0,0,0,2,1,0,0,0,0,0,0,0},
                                 {0,1,0,0,0,0,0,0,2,1,0,0},
                                 {0,0,0,0,0,1,0,0,0,0,0,0},
                                 {0,0,0,0,2,0,0,0,1,0,0,0},
                                 {0,0,0,1,0,0,0,0,0,0,0,0},
                                 {0,0,2,0,0,0,0,0,2,0,2,1},
                                 {0,0,0,0,0,0,0,0,1,0,0,0},
                                 {0,0,1,0,0,0,2,0,0,0,1,0},
                                 {0,0,2,0,1,0,0,0,0,0,0,0},
                                 {0,0,0,0,0,0,1,0,0,0,2,0},
                                };

    vector<vector<int> > LT3full={{1,0,0,2,1,0,0,0,0,0,0,0,2,1,0,0},
                                  {0,0,1,0,0,0,0,0,0,0,2,1,0,0,0,0},
                                  {0,0,0,2,0,2,0,1,0,0,0,0,2,0,1,0},
                                  {0,2,0,0,0,1,0,0,0,0,0,0,0,2,0,0},
                                  {0,1,0,0,0,0,0,2,0,0,1,0,0,0,0,0},
                                  {0,0,0,2,0,0,1,0,0,0,0,2,1,0,0,0},
                                  {0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0},
                                  {0,2,0,1,0,0,0,0,2,0,0,0,0,1,0,0},
                                  {0,0,0,2,0,0,0,1,0,0,0,2,0,0,2,0},
                                  {0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1},
                                  {0,1,0,0,2,0,0,0,1,0,0,0,0,0,0,2},
                                  {2,0,0,0,0,1,0,0,2,0,0,0,0,0,1,0},
                                  {0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,2},
                                  {0,0,2,1,0,0,2,0,0,0,0,0,0,0,0,0},
                                  {1,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1},
                                  {0,0,0,0,1,2,0,0,1,0,0,0,0,0,0,0},
                                 };

	string searchType = "DFS";
	int gridSize = 0;
	int noOfStudents = 0;
	bool ifSolutionFound = false;

	//Initialize Class Grid for BFS Search
	vector<vector<int> > bfsClassroomVector;

	//Initialize Class Grid for DFS Search
	ClassroomGrid dfsClassroomGrid = ClassroomGrid(gridSize, noOfStudents, 0);

	cout<<"Enter no of students: ";
	cin>>noOfStudents;

	cout<<"Enter the Algorithm by which you want to find the solution: ";
	cin>>searchType;


	   ClassroomGrid rootClassroomGrid= ClassroomGrid(gridSize, 0, 0);;

	if(noOfStudents<=9)
    {
	   rootClassroomGrid.noOfStudentsSeated = 0;
	   rootClassroomGrid.ClassroomVector = ff9;
	   gridSize=8;
	   cout<<endl<<endl<<"The students will be seated in FF9"<<endl<<endl;

    }

    else if(noOfStudents>=10 && noOfStudents<=16)
    {
       rootClassroomGrid.noOfStudentsSeated = 0;
	   rootClassroomGrid.ClassroomVector = G1;
	   gridSize=12;
	    cout<<endl<<endl<<"The students will be seated in G1"<<endl<<endl;
    }

    else if(noOfStudents>=17 && noOfStudents<=27)
    {
       rootClassroomGrid.noOfStudentsSeated = 0;
	   rootClassroomGrid.ClassroomVector =LT3;
	   gridSize=16;
       cout<<endl<<endl<<"The students will be seated in LT3"<<endl<<endl;
    }

    else if(noOfStudents>=28 && noOfStudents<=36)
    {
        noOfStudents=noOfStudents-27;
        rootClassroomGrid.noOfStudentsSeated = 0;
	    rootClassroomGrid.ClassroomVector = ff9;
	    gridSize=8;
	    cout<<endl<<endl<<"LT3 will be completely filled and the remaining students will be"<<endl<<"seated in FF9"<<endl<<endl;
        cout<<"LT3"<<endl<<endl;
        for (int i = 0; i < 16; i++)
		{
		    cout<<" _ _";
		}

        cout<<endl;
		for (int i = 0; i < 16; i++)
		{
		    cout<<"|";
			for (int j = 0; j < 16; j++)
			{

				{
					cout<< "_"<<LT3full[i][j]<<"_|";
				}


			}
			cout<< endl;
		}

		cout<<endl<<endl<<"Seats to be occupied in LT3 are: "<<endl<<endl;

		cout<<"s[0][0]"<<endl;
		cout<<"s[0][4]"<<endl;
		cout<<"s[0][13]"<<endl;
		cout<<"s[1][2]"<<endl;
		cout<<"s[1][11]"<<endl;
		cout<<"s[2][7]"<<endl;
		cout<<"s[2][14]"<<endl;
		cout<<"s[3][5]"<<endl;
		cout<<"s[4][1]"<<endl;
		cout<<"s[4][10]"<<endl;
		cout<<"s[5][6]"<<endl;
		cout<<"s[5][12]"<<endl;
		cout<<"s[6][9]"<<endl;
		cout<<"s[7][3]"<<endl;
		cout<<"s[7][13]"<<endl;
		cout<<"s[8][7]"<<endl;
		cout<<"s[9][15]"<<endl;
		cout<<"s[10][1]"<<endl;
		cout<<"s[10][8]"<<endl;
		cout<<"s[11][5]"<<endl;
		cout<<"s[11][14]"<<endl;
		cout<<"s[12][7]"<<endl;
		cout<<"s[13][3]"<<endl;
		cout<<"s[14][0]"<<endl;
		cout<<"s[14][15]"<<endl;
		cout<<"s[15][4]"<<endl;
		cout<<"s[15][8]"<<endl;


		cout<<endl<<endl<<"FF9"<<endl;

    }

    else if(noOfStudents>=36 && noOfStudents<=43)
    {
        noOfStudents=noOfStudents-27;
        rootClassroomGrid.noOfStudentsSeated = 0;
	    rootClassroomGrid.ClassroomVector = G1;
	    gridSize=12;

	    cout<<endl<<endl<<"LT3 will be completely filled and the remaining students will be"<<endl<<"seated in G1"<<endl<<endl;
        cout<<"LT3"<<endl<<endl;
        for (int i = 0; i < 16; i++)
		{
		    cout<<" _ _";
		}

        cout<<endl;
		for (int i = 0; i < 16; i++)
		{
		    cout<<"|";
			for (int j = 0; j < 16; j++)
			{

				{
					cout<< "_"<<LT3full[i][j]<<"_|";
				}


			}
			cout<< endl;
		}

		cout<<endl<<endl<<"Seats to be occupied in LT3 are: "<<endl<<endl;

		cout<<"s[0][0]"<<endl;
		cout<<"s[0][4]"<<endl;
		cout<<"s[0][13]"<<endl;
		cout<<"s[1][2]"<<endl;
		cout<<"s[1][11]"<<endl;
		cout<<"s[2][7]"<<endl;
		cout<<"s[2][14]"<<endl;
		cout<<"s[3][5]"<<endl;
		cout<<"s[4][1]"<<endl;
		cout<<"s[4][10]"<<endl;
		cout<<"s[5][6]"<<endl;
		cout<<"s[5][12]"<<endl;
		cout<<"s[6][9]"<<endl;
		cout<<"s[7][3]"<<endl;
		cout<<"s[7][13]"<<endl;
		cout<<"s[8][7]"<<endl;
		cout<<"s[9][15]"<<endl;
		cout<<"s[10][1]"<<endl;
		cout<<"s[10][8]"<<endl;
		cout<<"s[11][5]"<<endl;
		cout<<"s[11][14]"<<endl;
		cout<<"s[12][7]"<<endl;
		cout<<"s[13][3]"<<endl;
		cout<<"s[14][0]"<<endl;
		cout<<"s[14][15]"<<endl;
		cout<<"s[15][4]"<<endl;
		cout<<"s[15][8]"<<endl;


		cout<<endl<<endl<<"G1"<<endl;
    }

    else if(noOfStudents>=44 && noOfStudents<=52)
    {
        noOfStudents=noOfStudents-43;
        rootClassroomGrid.noOfStudentsSeated = 0;
	    rootClassroomGrid.ClassroomVector = ff9;
	    gridSize=8;

	    cout<<endl<<endl<<"LT3 and G1 will be completely filled and the remaining students will be"<<endl<<"seated in FF9"<<endl<<endl;
        cout<<"LT3"<<endl<<endl;
        for (int i = 0; i < 16; i++)
		{
		    cout<<" _ _";
		}

        cout<<endl;
		for (int i = 0; i < 16; i++)
		{
		    cout<<"|";
			for (int j = 0; j < 16; j++)
			{

				{
					cout<< "_"<<LT3full[i][j]<<"_|";
				}


			}
			cout<< endl;
		}

		cout<<endl<<endl<<"Seats to be occupied in LT3 are: "<<endl<<endl;

		cout<<"s[0][0]"<<endl;
		cout<<"s[0][4]"<<endl;
		cout<<"s[0][13]"<<endl;
		cout<<"s[1][2]"<<endl;
		cout<<"s[1][11]"<<endl;
		cout<<"s[2][7]"<<endl;
		cout<<"s[2][14]"<<endl;
		cout<<"s[3][5]"<<endl;
		cout<<"s[4][1]"<<endl;
		cout<<"s[4][10]"<<endl;
		cout<<"s[5][6]"<<endl;
		cout<<"s[5][12]"<<endl;
		cout<<"s[6][9]"<<endl;
		cout<<"s[7][3]"<<endl;
		cout<<"s[7][13]"<<endl;
		cout<<"s[8][7]"<<endl;
		cout<<"s[9][15]"<<endl;
		cout<<"s[10][1]"<<endl;
		cout<<"s[10][8]"<<endl;
		cout<<"s[11][5]"<<endl;
		cout<<"s[11][14]"<<endl;
		cout<<"s[12][7]"<<endl;
		cout<<"s[13][3]"<<endl;
		cout<<"s[14][0]"<<endl;
		cout<<"s[14][15]"<<endl;
		cout<<"s[15][4]"<<endl;
		cout<<"s[15][8]"<<endl;


		cout<<endl<<endl<<"G1"<<endl;
		for (int i = 0; i < 12; i++)
		{
		    cout<<" _ _";
		}

        cout<<endl;
		for (int i = 0; i < 12; i++)
		{
		    cout<<"|";
			for (int j = 0; j < 12; j++)
			{

				{
					cout<< "_"<<G1full[i][j]<<"_|";
				}


			}
			cout<< endl;
		}

        cout<<endl<<endl<<"Seats to be occupied in G1 are: "<<endl<<endl;

		cout<<"s[0][0]"<<endl;
		cout<<"s[0][7]"<<endl;
		cout<<"s[1][2]"<<endl;
		cout<<"s[1][10]"<<endl;
		cout<<"s[2][4]"<<endl;
		cout<<"s[3][1]"<<endl;
		cout<<"s[3][9]"<<endl;
		cout<<"s[4][5]"<<endl;
		cout<<"s[5][8]"<<endl;
		cout<<"s[6][3]"<<endl;
		cout<<"s[7][11]"<<endl;
		cout<<"s[8][8]"<<endl;
		cout<<"s[9][2]"<<endl;
		cout<<"s[9][10]"<<endl;
		cout<<"s[10][4]"<<endl;
		cout<<"s[11][6]"<<endl;

        cout<<endl<<endl<<"FF9"<<endl;

    }

    else if(noOfStudents>52)
    {
        cout<<"Sorry, enough classes are not availaible"<<endl<<endl<<endl;
        return 0;
    }

	if (searchType == "BFS")
	{
		bool studentPlaced = false;
		int noOfUnsafePos = 0;

		bool rootNode = true;
		ClassroomQueue.push(rootClassroomGrid);
		int row = 0;

		while (!ClassroomQueue.empty())
		{
			if (bfsClassroomVector.size() != 0)
			{
				break;
			}

			ClassroomGrid frontClassroomGrid = ClassroomQueue.front();

			if (rootNode)
			{
				if (CheckRowForAllteachers(frontClassroomGrid.ClassroomVector, row, gridSize))
					row = frontClassroomGrid.currentRow + 1;
				else
					row = frontClassroomGrid.currentRow;
			}
			else
			{
				//Check if next row consist of teachers only
				if (CheckRowForAllteachers(frontClassroomGrid.ClassroomVector, row + 1, gridSize))
				{
					row = frontClassroomGrid.currentRow + 2;
				}
				else if (studentPlaced == false)
				{
					row = frontClassroomGrid.currentRow + 2;
				}
				else
				{
					row = frontClassroomGrid.currentRow + 1;
				}
			}

			if (row == gridSize)
			{
				row = 0;
			}
			rootNode = false;

			// Get teacher Position
			bool ifteacherExist = false;
			for (int i = 0; i < gridSize; i++)
			{
				if (frontClassroomGrid.ClassroomVector[row][i] == 2)
				{
					ifteacherExist = true;
					break;
				}
			}

			if (ChecGoalState(frontClassroomGrid, noOfStudents))
			{
				ifSolutionFound = true;
				bfsClassroomVector = frontClassroomGrid.ClassroomVector;
				break;
			}
			else
			{
				ClassroomQueue.pop();
				queue<ClassroomGrid> insideQueue;

				for (int column = 0; column < gridSize; column++) {
					ClassroomGrid pushClassroomGrid = frontClassroomGrid;
					if (CheckSafePosition(pushClassroomGrid.ClassroomVector, row, column, gridSize))
					{
						if (noOfUnsafePos >= 0)
						{
							noOfUnsafePos--;
						}

						pushClassroomGrid.ClassroomVector[row][column] = 1;
						pushClassroomGrid.noOfStudentsSeated += 1;
						studentPlaced = true;
						pushClassroomGrid.currentRow = row;
						ClassroomQueue.push(pushClassroomGrid);

						if (ifteacherExist == true)
						{
							for (int i = column + 1; i < gridSize; i++)
							{
								ClassroomGrid insideClassroomGrid = ClassroomGrid(gridSize, 0, 0);
								insideClassroomGrid = pushClassroomGrid;

								if (CheckSafePosition(insideClassroomGrid.ClassroomVector, row, i, gridSize))
								{
									if (noOfUnsafePos >= 0)
									{
										noOfUnsafePos--;
									}

									insideClassroomGrid.ClassroomVector[row][i] = 1;
									insideClassroomGrid.noOfStudentsSeated += 1;
									studentPlaced = true;
									insideClassroomGrid.currentRow = row;
									insideQueue.push(insideClassroomGrid);
								}
							}
						}
					}
					else
					{
						noOfUnsafePos++;
						if (noOfUnsafePos == gridSize)
						{
							studentPlaced = false;
						}
					}

					for (int i = 0; i < insideQueue.size(); i++)
					{
						ClassroomGrid studentGrid = insideQueue.front();
						insideQueue.pop();
						ClassroomQueue.push(studentGrid);
					}

					if (ChecGoalState(pushClassroomGrid, noOfStudents))
					{
						ifSolutionFound = true;
						bfsClassroomVector = pushClassroomGrid.ClassroomVector;
						break;
					}
				}
			}
		}
	}
	else if (searchType == "DFS")
	{
		dfsClassroomGrid = FindDFSSolution(rootClassroomGrid, gridSize, noOfStudents, true);
		if (dfsClassroomGrid.noOfStudentsSeated == noOfStudents)
		{
			ifSolutionFound = true;
		}
		else
            ifSolutionFound = false;
	}


	//Print the solution

	if (ifSolutionFound)
	{

		for (int i = 0; i < gridSize; i++)
		{
		    cout<<" _ _";
		}

        cout<<endl;
		for (int i = 0; i < gridSize; i++)
		{
		    cout<<"|";
			for (int j = 0; j < gridSize; j++)
			{
				if (searchType == "BFS")
				{
					cout<< "_"<<bfsClassroomVector[i][j]<<"_|";
				}
				else if (searchType == "DFS")
				{
					cout<<"_"<<dfsClassroomGrid.ClassroomVector[i][j]<<"_|";
				}

			}
			cout<< endl;
		}

		cout<<endl<<endl<<"The seats available are: "<<endl<<endl;

		if(searchType=="BFS")
        {
            for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (bfsClassroomVector[i][j]==1)
                    cout<<"s"<<"["<<i<<"]"<<"["<<j<<"]"<<endl;
			}
		}

        }
        else if(searchType=="DFS")
        {
            for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (dfsClassroomGrid.ClassroomVector[i][j]==1)
                    cout<<"s"<<"["<<i<<"]"<<"["<<j<<"]"<<endl;
			}
		}

        }

	}
	else
	{
		cout<< "FAIL" << endl;

	}
	return 0;
}

