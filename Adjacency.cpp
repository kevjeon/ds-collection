//============================================================================
// Name        : Adjacency.cpp
// Author      : Seongbeom Jeon
// Description : Adjacency matrix and list implementation
//============================================================================

#include <iostream>
#include <queue>
#include <list>
using namespace std;

/**
 Class for Adjacency Matrix
*/
class AdjMatrix {
protected:
	typedef int* ArrayPrt; //Define an array of int
	ArrayPrt *Matrix; //Array of the above type, 2d array
	int numVertex; //Number of vertices 
public:
	AdjMatrix(); //Default constructor
	AdjMatrix(int n); //Constructor with size defined
	virtual ~AdjMatrix(); //destructor
	AdjMatrix(const AdjMatrix& origin); //copy constructor
	void BFS(AdjMatrix graph, int start); //Breadth First Search
	void DFS(AdjMatrix graph, int start); //Depth First Search
	void DFSProcedure(AdjMatrix graph, int start, bool* Visited, int* SearchNum, int* Parent, int Depth); //Procedural method for DFS
	void addEdge(int x, int y); //Connects vertices x and y
	void display(ostream& os); //Display
	friend ostream& operator<< (ostream& os, AdjMatrix graph); //Ostream operator
	void operator=(const AdjMatrix& original); // = overload
	int getNumVert(); //Return the number of vertices
};


/**
 Class for Adjacency List
*/
class AdjList {
protected:
	list<int>* ListArray; //Array of LinkedList
	int numVertex; //The number of verticies
public:
	AdjList(); //Default constructor
	AdjList(int n); //Constructor with specified number of verticies
	AdjList(const AdjList& origin); //Copy constructor
	virtual ~AdjList(); //Destructor
	void operator=(const AdjList& original);
	void addEdge(int x, int y); //Creates an edge between vertices x and y
	bool isNeighb(int x, int y); //Two edges are neighbors if there is an edge
	void BFS(AdjList graph, int p); //Breadth First Search
	void DFS(AdjList graph, int p); //Depth First Search
	void DFSProcedure(AdjList graph, int start, bool* Visited, int* SearchNum, int* Parent, int Depth); //Procedural method for DFS
	void display(ostream& os); //Display the edges
	friend ostream& operator<<(ostream& os, AdjList graph); //ostream overload
};

/**
 Default constructor for AdjMatrix
*/
AdjMatrix::AdjMatrix() {
	Matrix[0] = new int[0];
	numVertex = 0;
}

/**
 Constructor for AdjMatrix with specified vertices
*/
AdjMatrix::AdjMatrix(int n) {
	numVertex = n;
	Matrix = new ArrayPrt[n];

	//Initalize the matrix
	for (int i = 0; i < n; i++) {
		Matrix[i] = new int[n];
	}
}

/**
 Copy constructor for AdjMatrix
*/
AdjMatrix::AdjMatrix(const AdjMatrix& origin) {
	numVertex = origin.numVertex;
	Matrix = new ArrayPrt[origin.numVertex];

	//Initialize the matrix with origin's size
	for (int i = 0; i < origin.numVertex; i++) {
		Matrix[i] = new int[origin.numVertex];
	}

	//Copy the content of the original matrix into the matrix
	for (int i = 0; i < origin.numVertex; i++) {
		for (int j = 0; j < origin.numVertex; j++) {
			Matrix[i][j] = origin.Matrix[i][j];
		}
	}
}

/**
 Destructor for AdjMatrix
*/
AdjMatrix::~AdjMatrix() {
	if (Matrix != NULL) {
		delete[] Matrix;
		Matrix = NULL;
		numVertex = 0;
	}
}

/**
 Breadth First Search of AdjMatrix
 @param graph
 @param p, the starting node
*/
void AdjMatrix::BFS(AdjMatrix graph, int p) {
	int v;

	//Initalize the parent array
	int* parentArray = new int[graph.getNumVert()];
	parentArray[p] = -1; //p is the root
	queue<int> Q; //Create the queue to work with

	//bool array of visited nodes
	bool* Visited = new bool[graph.getNumVert()];
	for (int i = 0; i < graph.getNumVert(); i++) {
		Visited[i] = false;
	}

	//Array of BFSnums
	int* BFSnums = new int[graph.getNumVert()];
	for (int i = 0; i < graph.getNumVert(); i++) {
		BFSnums[i] = 0;
	}
	int BFSnum = 0;

	Q.push(p);
	Visited[p] = true;

	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		//Increment and fill the value in array
		BFSnum = BFSnum + 1;
		BFSnums[v] = BFSnum;

		//If v and the node is a neighbor and the node has not been visited yet
		//Mark it as visited and its parent becomes v
		for (int i = 0; i < graph.getNumVert(); i++) {
			if (Matrix[v][i] == 1) {
				if (!Visited[i]) {
					parentArray[i] = v;
					Visited[i] = true;
					Q.push(i);
				}
			}
		}


	}

	//Print in parent array format
	for (int i = 0; i < graph.getNumVert(); i++) {
		cout << i << ": " << parentArray[i] << " ";
	}

	

}

/**
 Depth First Search for AdjMatrix
 @param graph
 @param start, the starting node
*/
void AdjMatrix::DFS(AdjMatrix graph, int start) {
	//Initalize parent array, starting node is the root
	int* parentArray = new int[graph.getNumVert()];
	parentArray[start] = -1;

	//All nodes are unvisited right now
	bool* Visited = new bool[graph.getNumVert()];
	for (int i = 0; i < graph.getNumVert(); i++) {
		Visited[i] = false;
	}

	//Initalize SearchNum to 1
	int* SearchNum = new int[graph.getNumVert()];
	for (int i = 0; i < graph.getNumVert(); i++) {
		SearchNum[i] = 1;
	}

	//Call the procedure to visit nodes
	DFSProcedure(graph, start, Visited, SearchNum, parentArray, 1);

	//Print the parent array form of DFS
	for (int i = 0; i < graph.getNumVert(); i++) {
		cout << i << ": " << parentArray[i] << " ";
	}
}

/**
 Procedural method for DFS
*/
void AdjMatrix::DFSProcedure(AdjMatrix graph, int start, bool* Visited, int* SearchNum, int* Parent, int Depth) {
	//The starting node is visited
	Visited[start] = true;
	SearchNum[start] = Depth; //Record the depth of the graph

	//For all neighbors of start
	for (int i = 0; i < graph.getNumVert(); i++) {
		if (Matrix[start][i] == 1) {
			if (!Visited[i]) {
				Visited[i] = true; //Mark as visisted
				Parent[i] = start; //Its parent is the starting node
				DFSProcedure(graph, i, Visited, SearchNum, Parent, Depth + 1);
			}
		}
	}
}

/**
 Display the AdjMatrix in edgelist format
*/
void AdjMatrix::display(ostream& os) {

	for (int i = 0; i < numVertex; i++) {
		for (int j = 0; j < numVertex; j++) {
			if (Matrix[i][j] == 1) {

				os << "(" << i << "," << j << "), ";
			}
		}
	}
}

//Ostream overload for AdjMatrix
ostream& operator<< (ostream& os, AdjMatrix graph) {
	graph.display(os);
	return os;
}

void AdjMatrix::operator=(const AdjMatrix& original) {
	numVertex = original.numVertex;
	Matrix = new ArrayPrt[original.numVertex];

	//Initialie the matrix with origin's size
	for (int i = 0; i < original.numVertex; i++) {
		Matrix[i] = new int[original.numVertex];
	}

	//Copy the content of the original matrix into the matrix
	for (int i = 0; i < original.numVertex; i++) {
		for (int j = 0; j < original.numVertex; j++) {
			Matrix[i][j] = original.Matrix[i][j];
		}
	}
}

void AdjMatrix::addEdge(int x, int y) {
	//Fill the specified section of the matrix with 1
	Matrix[x][y] = 1;
	Matrix[y][x] = 1;
}

int AdjMatrix::getNumVert() {
	return numVertex;
}

/**
 Default constructor for AdjList
*/
AdjList::AdjList() {
	numVertex = 0;
	ListArray = new list<int>[0];
}

/**
 Constructor for AdjList with specified number of nodes
 @param n, the number of nodes
*/
AdjList::AdjList(int n) {
	numVertex = n;
	ListArray = new list<int>[n];

}

/**
Copy constructor for AdjList
*/
AdjList::AdjList(const AdjList& origin) {
	numVertex = origin.numVertex;
	//Initialize new list
	ListArray = new list<int>[origin.numVertex];

	//Copy the original values in the list to the new list
	for (int i = 0; i < origin.numVertex; i++) {
		for (list<int>::iterator it = origin.ListArray[i].begin(); it != origin.ListArray[i].end(); ++it) {
			ListArray[i].push_back(*it);
		}

	}
}

/**
Destructor for AdjList
*/
AdjList::~AdjList() {
	if (ListArray != NULL) {
		delete[] ListArray;
		ListArray = NULL;
	}
	numVertex = 0;
}

void AdjList::operator=(const AdjList& original) {
	numVertex = original.numVertex;
	//Initialize new list
	ListArray = new list<int>[original.numVertex];

	//Copy the original values in the list to the new list
	for (int i = 0; i < original.numVertex; i++) {
		for (list<int>::iterator it = original.ListArray[i].begin(); it != original.ListArray[i].end(); ++it) {
			ListArray[i].push_back(*it);
		}

	}
}

/**
 Adds the edge to AdjList
 @param x,y the Vertices to be connected
*/
void AdjList::addEdge(int x, int y) {
	//Make a new link on specified linked list

	if (x != y) {
		ListArray[x].push_back(y);
		ListArray[x].unique();
		ListArray[y].push_back(x);
		ListArray[y].unique();
		
	}

}

/**
 Method to determine whether two vertices are neighbors
 @return 
*/
bool AdjList::isNeighb(int x, int y) {

	//Iterate through the specified list 
	for (list<int>::iterator it = ListArray[x].begin(); it != ListArray[x].end(); ++it) {
		if (*it == y) { //If there is a y linked, return true
			return true;
		}
	}

	return false; //Otherwise, return false

}

/**
 Returns the parent array format of Breadth first search
  
  @param graph The original graph
  @param p The starting vertex
*/
void AdjList::BFS(AdjList graph, int p) {
	int vertex;
	//Initialize parent array, starting vertex is the root
	int* parentArray = new int[numVertex];
	parentArray[p] = -1;
	queue<int> Q;
	//All vertices are unvisited
	bool* Visited = new bool[numVertex];
	for (int i = 0; i < numVertex; i++) {
		Visited[i] = false;
	}

	Q.push(p);
	Visited[p] = true;

	while (!Q.empty()) {
		vertex = Q.front();
		Q.pop();

		//For all neighbors of the vertex
		for (int i = 0; i < numVertex; i++) {
			if (isNeighb(vertex, i)) {
				//If the vertex is unvisited, mark as visited
				if (!Visited[i]) {
					parentArray[i] = vertex; //Its parent is the vertex
					Visited[i] = true;
					Q.push(i);
				}
			}
		}
	}

	//Print in parent array format
	for (int i = 0; i < numVertex; i++) {
		cout << i << ": " << parentArray[i] << " ";
	}
}

/**
 Depth First Search
 @param graph, the AdjList
 @param p, the starting vertex
*/
void AdjList::DFS(AdjList graph, int p) {
	//Initalize parent array, starting node is the root
	int* parentArray = new int[graph.numVertex];
	parentArray[p] = -1;

	//All nodes are unvisited right now
	bool* Visited = new bool[graph.numVertex];
	for (int i = 0; i < graph.numVertex; i++) {
		Visited[i] = false;
	}

	//Initalize SearchNum to 1
	int* SearchNum = new int[graph.numVertex];
	for (int i = 0; i < graph.numVertex; i++) {
		SearchNum[i] = 1;
	}

	//Call the procedure to visit nodes
	DFSProcedure(graph, p, Visited, SearchNum, parentArray, 1);

	//Print the parent array form of DFS
	for (int i = 0; i < graph.numVertex; i++) {
		cout << i << ": " << parentArray[i] << " ";
	}
}

/**
 Procedural method for DFS
*/
void AdjList::DFSProcedure(AdjList graph, int start, bool* Visited, int* SearchNum, int* Parent, int Depth) {
	//The starting node is visited
	Visited[start] = true;
	SearchNum[start] = Depth; //Record the depth of the graph

	//For all neighbors of start
	for (int i = 0; i < graph.numVertex; i++) {
		if (isNeighb(start, i)) {
			if (!Visited[i]) {
				Visited[i] = true; //Mark as visisted
				Parent[i] = start; //Its parent is the starting node
				DFSProcedure(graph, i, Visited, SearchNum, Parent, Depth + 1);
			}
		}
	}

}

/**
 display the AdjList in edgelist format
*/
void AdjList::display(ostream& os) {
	
	for (int i = 0; i < numVertex; i++) {
		for (list<int>::iterator it = ListArray[i].begin(); it != ListArray[i].end(); ++it) {
			os << "(" << i << "," << *it << "), ";
		}

	}

	

}

ostream& operator<< (ostream& os, AdjList graph) {
	graph.display(os);
	return os;
}

int main() {
	AdjMatrix* MatrixGraph; //Original graph Matrix
	AdjList* ListGraph; //Original graph List

	//For copy constructor
	AdjMatrix* MatGraph2; 
	AdjList* ListGraph2; 

	//For = operator
	AdjMatrix* MatGraph3 = new AdjMatrix(0);
	AdjList* ListGraph3 = new AdjList(0);

	int numVertex, u, v;

	cin >> numVertex;
	MatrixGraph = new AdjMatrix(numVertex);
	ListGraph = new AdjList(numVertex);
	while (!cin.eof()) {
		cin >> u >> v;
		ListGraph->addEdge(u, v);
		MatrixGraph->addEdge(u, v);
	}

	cout << "Original AdjMatrix: " << *MatrixGraph << endl;
	cout << "Original AdjList: " << *ListGraph << endl;

	MatGraph2 = new AdjMatrix(*MatrixGraph);
	ListGraph2 = new AdjList(*ListGraph);

	*MatGraph3 = *MatrixGraph;
	*ListGraph3 = *ListGraph;

	cout << "Copy constructor AdjMatrix: " << *MatGraph2 << endl;
	cout << "Copy constructor AdjList: " << *ListGraph2 << endl;

	cout << "= operator AdjMatrix: " << *MatGraph3 << endl;
	cout << "= operator AdjList: " << *ListGraph3 << endl;
	

	cout << "AdjMatrix BFS starting at 0: " << endl;
	MatrixGraph->BFS(*MatrixGraph, 0);

	cout << endl;

	cout << "AdjList BFS starting at 0: " << endl;
	ListGraph->BFS(*ListGraph, 0);

	cout << endl;

	cout << "AdjMatrix DFS starting at 0: " << endl;
	MatrixGraph->DFS(*MatrixGraph, 0);

	cout << endl;

	cout << "AdjList DFS starting at 0: " << endl;
	ListGraph->DFS(*ListGraph, 0);

	

}

