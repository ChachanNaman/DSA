#include <iostream>
#include <queue>
using namespace std;
// level order traversal for printing tree
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

node *minval(node *root)
{
    node *temp = root;
    while (temp->left != NULL)
    {
        temp = temp->left;
    }
    return temp;
}

node *maxval(node *root)
{
    node *temp = root;
    while (temp->right != NULL)
    {
        temp = temp->right;
    }
    return temp;
}

node *deletefromBST(node *root, int val)
{
    if (root == NULL)
    { // BASE CASE
        return root;
    }
    if (root->data == val)
    {
        // 0 child
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL; // returning null to parent as there were no child
        }

        // 1 child : (left child or right child)
        // left child
        if (root->left != NULL && root->right == NULL)
        {
            node *temp = root->left;
            delete root;
            return temp;
        }

        // right child
        if (root->left == NULL && root->right != NULL)
        {
            node *temp = root->right;
            delete root;
            return temp;
        }

        // 2 childs
        if (root->left != NULL && root->right != NULL)
        {
            // we can do by two ways by going to max value in left subtree of root OR min value in right subtree of root
            int mini = minval(root->right)->data;
            root->data = mini;
            root->right = deletefromBST(root->right , mini);
            return root;
        }
    }
    else if (val < root->data)
    {
        root->left = deletefromBST(root->left, val);
 
    }
    else
    {
        root->right = deletefromBST(root->right, val);
   
    }
return root;
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

int main()
{
    node *root = NULL;
    cout << "enter datas to create BST : " << endl;
    takeinput(root);

    cout << "Printing BST : " << endl;
    levelordertraversal(root);

    cout << "Maximum value from BST : " << maxval(root)->data << endl;
    cout << "Minimum value from BST : " << minval(root)->data << endl;
    

    cout<<"Enter the value you want to delete : ";
    int val;
    cin>>val;
    root = deletefromBST(root , val);
    cout << "Printing BST : " << endl;
    levelordertraversal(root);

    cout << "Maximum value from BST : " << maxval(root)->data << endl;
    cout << "Minimum value from BST : " << minval(root)->data << endl;
    return 0;

}