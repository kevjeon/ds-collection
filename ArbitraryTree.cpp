//============================================================================
// Name        : ArbitraryTree.cpp
// Author      : Seongbeom Jeon
// Description : Arbitrary tree implementation using arrays
//============================================================================

#include <iostream>
using namespace std;

class Tree {
protected:
	int* ParentArr; //The parent array where the position of parent is stored
	int Nodes; //Number of nodes in the tree
	int Roots; //The root of the tree
public:
	Tree(); //Default constructor for the Tree
	Tree(int numNodes); //Constructor with specified number of nodes
	Tree(const Tree& origin); //Copy constructor
	virtual ~Tree(); //Destructor
	friend ostream& operator<<(ostream& output, Tree t); 
	int LCA(int x, int y); //Returns the least common ancestor of two given nodes
	int Parent(int i); //Returns the parent of given node
	void Children(int i); //Print the children of given node
	void Siblings(int i); //Print the siblings of given node
	int Root(); //Return the root of the tree
	void setRoot(int rootNode); //Set the root of the tree
	void setParent(int node, int parent); //Set the parent of the select node
	void nodesAtLevel(int i); //Display all nodes on select level
	void display(ostream& output); //Display
	int Level(int i); //Return the level of the given node
	int height(); //Return the height of the tree
	
};

Tree::Tree() {
	//Empty Tree as default
	ParentArr = new int[0];
	Nodes = 0;
}

Tree::Tree(int numNodes) {
	//Number of elements in the array = number of nodes
	ParentArr = new int[numNodes];
	Nodes = numNodes;
}

Tree::Tree(const Tree& Origin) {
	if (&Origin != this) { //Check if it's the same Tree
		Nodes = 0;
		ParentArr = new int[Origin.Nodes];
		Nodes = Origin.Nodes;

		//Iterate through the parent array to copy the elements
		for (int i = 0; i < Nodes; i++) {
			ParentArr[i] = Origin.ParentArr[i];
		}
	}
}

Tree::~Tree() {
	if (ParentArr != NULL) {
		delete[] ParentArr;
		ParentArr = NULL;
		Nodes = 0;
	}
}

int Tree::Parent(int i) {
	return ParentArr[i];
}

void Tree::Children(int i) {
	int counter = 0;
	//Loop through the parent array 
	for (int x = 0; x < Nodes; x++) {
		//If value of int and position is i, then print
		if (ParentArr[x] == i) {
			cout << x << " ";
			counter++;
		}
	}

	cout << endl;
}
void Tree::Siblings(int i) {
	
	//Loop through the parent array to find values with same parent
	for (int x = 0; x < Nodes; x++) {
		//If that value is not itself, print
		if (x != i && ParentArr[x] == ParentArr[i]) {
			cout << x << " ";
		}
		
	}

	cout << endl;
}

int Tree::Root() {
	return Roots;
}

void Tree::setRoot(int rootNode) {
	Roots = rootNode;
}

void Tree::setParent(int node, int parent) {
	ParentArr[node] = parent;
}

void Tree::nodesAtLevel(int i) {
	//Loop through the array, then call the Level() function
	// to print all elements with Level i
	for (int x = 0; x < Nodes; x++) {
		if (Level(x) == i) {
			cout << x << " ";
		}
	}

	cout << endl;
}
void Tree::display(ostream& output) {
	//Loop through the parent array and print each values
	for (int i = 0; i < Nodes; i++) {
		output << i << ": " << ParentArr[i] << " ";
	}
}

ostream& operator<<(ostream& output, Tree t) {
	t.display(output);

	return output;
}

int Tree::LCA(int x, int y) {
	//Initalize a boolean array to store ancestor
	bool* test = new bool[Nodes];
	for (int i = 0; i < Nodes; i++) {
		test[i] = false;
	}
	//Set position of first child as true
	test[x] = true;

	//Set position x to be true if it's not the root
	while (ParentArr[x] != -1) {
		test[x] = true;

		//This allows traversal through entire tree
		x = ParentArr[x];
	}
	//reset
	test[x] = true;

	while (test[y] == false) {
		y = ParentArr[y];
	}

	return y;
}

int Tree::Level(int i) {
	
	//Create an array initialized to -1, the root
	int* test = new int[Nodes];
	for (int x = 0; x < Nodes; x++) {
		test[x] = -1;
	}

	//Level is 1 if the parent is -1
	if (ParentArr[i] == -1) {
		return 1;
	}
	//If this level is not root, return  this + 1
	if (test[ParentArr[i]] != -1) {
		return test[ParentArr[i]] + 1;
	}

	test[ParentArr[i]] = Level(ParentArr[i]);

	return test[ParentArr[i]] + 1;


}

int Tree::height() {
	//Start with 0
	int result = 0;

	//Create a double loop
	for (int i = 0; i < Nodes; i++) {
		int par = i;
		//Height starts at 1, if there is a tree
		int count = 1;

		//increment count if the node is not the root
		//and set the par value as the parent
		//Will stop when the loop reaches the root
		while (ParentArr[par] != -1) {
			count++;
			par = ParentArr[par];
		}

		//Choose whichever height is the greatest from the children
		if (result >= count) {
			result = result;
		}

		else {
			result = count;
		}
	}

	return result;
}


int main() {
	Tree* myTree;
	int	numNodes, node, parent;

	cin >> numNodes;
	myTree = new Tree(numNodes);
	for (int i = 0; i < numNodes; i++) {
		cin >> node >> parent;
		(*myTree).setParent(node, parent);
		if (parent == -1) {
			(*myTree).setRoot(node);
		}
	}
	cout << "The tree that we just read is: " << endl;
	cout << *myTree << endl;

	Tree* newTree = new	Tree(*myTree);
	cout << "The tree that we just copied is: " << endl;
	cout << *newTree << endl;
	cout << "The root of the tree is : " << (*myTree).Root() << endl;

	cout << "The least common ancestor of nodes 3 and 8 is: " << (*newTree).LCA(3, 8) << endl;
	cout << "The least common ancestor of nodes 13 and 8 is: " << (*newTree).LCA(13, 8) << endl;
	cout << "The least common ancestor of nodes 13 and 11 is: " << (*myTree).LCA(13, 11) << endl;

	cout << "The children of node 12 is/are: " << endl;
	(*myTree).Children(12);

	cout << "The children of node 10 is/are: " << endl;
	(*myTree).Children(10);

	cout << "The siblings of node 3 is/are: " << endl;
	(*myTree).Siblings(3);

	cout << "The siblings of node 12 is/are: " << endl;
	(*myTree).Siblings(12);

	cout << "The nodes at level 3 is/are: " << endl;
	(*myTree).nodesAtLevel(3);

	cout << "The height of the tree is: " << (*myTree).height() << endl;

	cout << "The level of node 3 in the tree is: " << (*myTree).Level(3) << endl;
	cout << "The level of node 12 in the tree is: " << (*myTree).Level(12) << endl;

	delete myTree;
	delete newTree;

}