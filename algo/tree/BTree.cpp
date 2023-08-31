#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree() {
        root = NULL;
    }

    Node* getRoot() {
        return root;
    }

    void insert(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;

        if (root == NULL) {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true) {
            if (data < current->data) {
                if (current->left == NULL) {
                    current->left = newNode;
                    break;
                }
                current = current->left;
            }
            else {
                if (current->right == NULL) {
                    current->right = newNode;
                    break;
                }
                current = current->right;
            }
        }
    }

    void inorderTraversal(Node* node) {
        if (node == NULL) {
            return;
        }
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node* node) {
        if (node == NULL) {
            return;
        }
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node* node) {
        if (node == NULL) {
            return;
        }
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }
};

int main() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);

    cout << "Inorder traversal: ";
    tree.inorderTraversal(tree.getRoot());
    cout << endl;

    cout << "Preorder traversal: ";
    tree.preorderTraversal(tree.getRoot());
    cout << endl;

    cout << "Postorder traversal: ";
    tree.postorderTraversal(tree.getRoot());
    cout << endl;

    return 0;
}
