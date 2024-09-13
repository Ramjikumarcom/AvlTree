#include <iostream>
using namespace std;

class Node
{
public:
    int data, height;
    Node *left, *right;

    Node(int value)
    {
        data = value;
        height = 1;
        left = right = NULL;
    }
};
int getheight(Node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}
int checkbalanceheight(Node *root)
{
    return (getheight(root->left) - getheight(root->right));
}
Node *RightRotation(Node *root)
{
    Node *child = root->left;
    Node *rightChild = root->right;
    child->right = root;
    root->left = rightChild;
    root->height = 1 + max(getheight(root->left), getheight(root->right));
    child->height = 1 + max(getheight(child->left), getheight(child->right));
    return child;
}
Node *LeftRotation(Node *root)
{
    Node *child = root->right;
    Node *leftchild = child->left;
    child->left = root;
    root->right = leftchild;
    root->height = 1 + max(getheight(root->left), getheight(root->right));
    child->height = 1 + max(getheight(child->left), getheight(child->right));
    return child;
}
Node *insert(Node *root, int data)
{

    if (!root) // root is null
        return new Node(data);
    if (root->data > data) // insert left
    {
        root->left = insert(root->left, data);
    }
    else if (root->data < data) // insert right
    {
        root->right = insert(root->right, data);
    }
    else // duplicate element
    {
        return root;
    }

    // height update;
    root->height = 1 + max(getheight(root->left), getheight(root->right));
    // balance the height
    int balance = checkbalanceheight(root);
    // left left unbalance
    if (balance > 1 && root->left->data > data)
    {
        return RightRotation(root);
    }
    // right right unbalance
    else if (balance < -1 && root->right->data < data)
    {
        return LeftRotation(root);
    }
    // left right unbalencing
    else if (balance > 1 && root->left->data < data)
    {
        root->left = LeftRotation(root->left);
        return RightRotation(root);
    }
    // right left unbalancing
    else if (balance < -1 && root->right->data > data)
    {
        root->right = RightRotation(root->right);
        return LeftRotation(root);
    }
    else
        return root;
}
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->data<<" ";
        inorder(root->right);
    }
}
int main()
{
    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, -10);
    root = insert(root, 5);
    root = insert(root, 50);
    root = insert(root, 4);
    cout << "inorder Traversal" << endl;
    inorder(root);
}
