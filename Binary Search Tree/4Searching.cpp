// INSERTION IN BST TC : O(logn)
// SEARCHING IN BST -> Best TC : O[logn] , Worst TC skey tree: O(n) , SC recussrively: O(height) , SC iteratively : O(1)
#include <iostream> 
#include <queue>
using namespace std;
// level order traversal for printing treeeeee
class node
{
public:
    int data;
    node *left;
    node *right;
    node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node *insertintoBST(node *root, int d)
{
    // base case
    if (root == NULL)
    {
        root = new node(d);
        return root;
    }

    if (d > root->data)
    {
        root->right = insertintoBST(root->right, d);
    }
    else
    {
        root->left = insertintoBST(root->left, d);
    }
    return root;
}
void takeinput(node *&root)
{
    int data;
    cin >> data;

    while (data != -1)
    {
        root = insertintoBST(root, data);
        cin >> data;
    }
}
void levelordertraversal(node *root)
{
    queue<node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        if (temp == NULL)
        { // enter condition
            cout << endl;
            if (!q.empty())
            { // means there are some element in queue then push NULL for next enter
                q.push(NULL);
            }
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }
    }
}
void inorder(node *&root)
{
    if (root == NULL)
    {
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node *&root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

bool searchrec(node *&root, int d)
{
    if (root == NULL)
    {
        return false; // as its reached to last leaf node still didnt got value
    }

    if (root->data == d)
    {
        return true;
    }

    if (d > root->data)
    {
        return searchrec(root->right, d);
    }
    else
    { // d < root->data
        return searchrec(root->left, d);
    }
}

bool searchiter(node *&root, int d)
{
    node *temp = root;
    while (temp != NULL)
    {
        if (temp->data == d)
        {
            return true;
        }
        if (temp->data < d)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    return false;
}

void postorder(node *&root)
{
    if (root == NULL)
    {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
// 10 8 21 7 27 5 3 -1
int main()
{
    node *root = NULL;
    cout << "enter datas to create BST : " << endl;
    takeinput(root);

    cout << "Printing BST : " << endl;
    levelordertraversal(root);

    int d;
    cout << "Enter the data you want to search : ";
    cin >> d;
    cout << endl;
    bool ans = searchiter(root, d);
    cout << ans;

    cout << endl
         << "Printing Inoerder : " << endl;
    inorder(root);

    cout << endl
         << "Printing Preorder : " << endl;
    preorder(root);

    cout << endl
         << "Printing Postorder : " << endl;
    postorder(root);
    return 0;
}