/*
    Juan Perez
    Lac Tran
    04/29/20

 Simple Binary Search Tree Class Write a class for implementing a simple binary search tree capable of storing numbers. The class should have member functions

    void insert(double x)

    bool search(double x)

    void inorder(vector & v )

    The insert function should not use recursion directly or indirectly by calling a recursive function. The search function should work by calling a private recursive member function

    bool search(double x, BtreeNode *t)

    The in order function is passed an initially empty vector v: it fills v with the in order list of numbers stored in the binary search tree. Demonstrate the operation of the class using a suitable driver program.

    Tree Size Solving the Tree Size Problem Modify the binary search tree created in the previous programming challenge to add a member function
     int size()

    that returns the number of items (nodes) stored in the tree. Demonstrate the correctness of the new member function with a suitable driver program.

    Leaf Counter Modify the binary search tree you created in the preceding programming challenges to add a member function
    int leafCount()

     that counts and returns the number of leaf nodes in the tree. Demonstrate that the function works correctly in a suitable driver program.

    Tree Height Modify the binary search tree created in the preceding programming challenges by adding a member function that computes and returns the height of the tree.
    int height()


    The height of the tree is the number of levels it contains. For example, the tree shown in Figure below has three levels. Demonstrate the function with a suitable driver program. Figure below A Binary Tree with Three Levels A binary tree shows a root node with 2 child nodes. Each child node shows one child.

    Tree Width Modify the binary search tree created in the preceding programming challenges by adding a member function that computes the width of the tree.
    int width()

    The width of a tree is the largest number of nodes at the same level. Demonstrate correctness in a suitable driver program.

    Tree Copy Constructor Design and implement a copy constructor for the binary search tree created in the preceding programming challenges.
    Use a driver program to demonstrate correctness.

    Tree Assignment Operator Design and implement an overloaded assignment operator
    for the binary search tree created in the preceding programming challenges.*/
    

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Tree Interface
struct node
{
    double value;
    node* left;
    node* right;
};

// Class Declaration
class BinarySearchTree
{
private:
    node* root;
    int size;
    int leafCount;
    int height;

    void addValue(node*&, double);
    bool contain(node*, double);
    void inorderCopyValues(node*, vector <double>&);
    void locateLeafNode(node* root, int);

public:
    BinarySearchTree();
    void insert(double x);
    bool search(double x);
    void inorder(vector <double>& v);
    int getSize();
    int getLeafCount();
    int getHeight();
};

// Class Implementation
BinarySearchTree::BinarySearchTree()
{
    root = NULL;
    size = 0;
    leafCount = 0;
    height = 0;
}

// Add value method
void BinarySearchTree::addValue(node*& root, double val)
{
    if (root == NULL)
    {
        node* temp = new node;
        temp->value = val;
        temp->left = NULL;
        temp->right = NULL;
        root = temp;

        //update our size
        size++;
    }
    else if (val < root->value)
    {
        addValue(root->left, val);
    }
    else if (val > root->value)
    {
        addValue(root->right, val);
    }
}

// insert method will call the add value method
void BinarySearchTree::insert(double val)
{
    addValue(root, val);
}

// Contain method
bool BinarySearchTree::contain(node* root, double num)
{
    if (root == NULL)
    {
        cout << "The value " << num << " was not found in the tree" << endl;
        return false;
    }
    else if (num == root->value)
    {
        cout << "The value " << num << " was located" << endl;
        return true;
    }
    else if (num < root->value)
    {
        contain(root->left, num);
    }
    else
    {
        contain(root->right, num);
    }
}

// search method will invoke the contain method
bool BinarySearchTree::search(double num)
{
    return contain(root, num);
}

// In order copy values method, as we traverse the tree we will copy the value into the vector this function will be used by the public member method in order
void BinarySearchTree::inorderCopyValues(node* root, vector <double>& list)
{
    if (root == NULL)
    {
        return;
    }

    inorderCopyValues(root->left, list);
    list.push_back(root->value);
    inorderCopyValues(root->right, list);
}

void BinarySearchTree::inorder(vector <double>& list)
{
    inorderCopyValues(root, list);
}


// method to return the total number of nodes
int BinarySearchTree::getSize()
{
    return size;
}

// Method used to locate leaf nodes in our tree
void BinarySearchTree::locateLeafNode(node* root, int currentHeight)
{

    // base case in the case the root is a node which has only one children since the other condition only stops at leaf nodes we also need to set a stop for when a parent points us to NULL
    if (root == NULL)
    {
        return;
    }

    // condition to check if current node has no children
    if (root->left == NULL && root->right == NULL)
    {
        // update our count
        leafCount++;

        // condition to get our maximum height
        // each time we are reaching a leaf node we are counting how many steps it took from the root
        if (currentHeight > height)
        {
            height = currentHeight;
        }

        return;
    }

    // traverses down the tree from left to right
    locateLeafNode(root->left, currentHeight + 1);
    locateLeafNode(root->right, currentHeight + 1);
}

int BinarySearchTree::getLeafCount()
{
    leafCount = 0; // reset to zero in the case this method is called multiple times;
    locateLeafNode(root, 1);
    return leafCount;
}

int BinarySearchTree::getHeight()
{
    height = 0;
    locateLeafNode(root, 1);
    return height;
}


int main()
{
    BinarySearchTree tree;
    vector <double> treeList;
    int num;

    cout << "Enter a set of numbers for the tree list. Enter '0' to stop program." << endl;
    cin >> num;

    while (num != 0)
    {
        tree.insert(num);
        cin >> num;
    }
    cout << endl << "End of Insert." << endl << endl;

    tree.inorder(treeList);

    cout << "Printing our tree list" << endl;
    for (int x = 0; x < treeList.size(); x++)
    {
        cout << treeList[x] << " ";
    }
    cout << endl << endl;

    cout << "The total number of node/s is " << tree.getSize() << endl;
    cout << "The total number of leaf node/s is " << tree.getLeafCount() << endl;
    cout << "The height of our tree is " << tree.getHeight() << endl;

    cout << endl;

    cout << "Enter a number to search in the Node Tree: " << endl;
    cin >> num;

    while (num != 0)
    {
        tree.search(num);
        cout << endl;
        cin >> num;
    }

    cout << endl << "End of Search." << endl << endl;
    return 0;
}