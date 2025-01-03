#include <stdio.h>
#include <stdlib.h>

// Node structure definition
typedef struct node {
    int data;
    struct node* lchild;
    struct node* rchild;
} node;

// Create a new node with given value
node* newNode(int x) {
    node* Node = (node*)malloc(sizeof(node));
    Node->data = x;
    Node->lchild = NULL;
    Node->rchild = NULL;
    return Node;
}

// Search function returns 1 if found, 0 if not found
int search(node* root, int x) {
    if(root == NULL) {
        printf("search failed\n");
        return 0;
    }
    if(x == root->data) {
        printf("Found: %d\n", root->data);
        return 1;
    } else if(x < root->data) {
        return search(root->lchild, x);
    } else {
        return search(root->rchild, x);
    }
}

// Insert a new node into BST
void insert(node** root, int x) {
    if(*root == NULL) {
        *root = newNode(x);
        return;
    }
    if(x == (*root)->data) {
        printf("Value %d already exists\n", x);
        return;
    }
    else if (x < (*root)->data) {
        insert(&((*root)->lchild), x);
    } else {
        insert(&((*root)->rchild), x);
    }
}

// Create BST from array
node* Create(int data[], int n) {
    node* root = NULL;
    for(int i = 0; i < n; i++) {
        insert(&root, data[i]);
    }
    return root;
}

// Find node with maximum value in BST
node* findMax(node* root) {
    while(root->rchild != NULL) {
        root = root->rchild;
    }
    return root;
}

// Find node with minimum value in BST
node* findMin(node* root) {
    while(root->lchild != NULL) {
        root = root->lchild;
    }
    return root;
}

// Delete a node with given value from BST
void deleteNode(node** root, int x) {
    if(*root == NULL) return;
    
    if((*root)->data > x) {
        deleteNode(&((*root)->lchild), x);
    }
    else if((*root)->data < x) {
        deleteNode(&((*root)->rchild), x);
    }
    else { // Found the node to delete
        // Case 1: Leaf node
        if((*root)->lchild == NULL && (*root)->rchild == NULL) {
            free(*root);
            *root = NULL;
        }
        // Case 2: Has left subtree
        else if((*root)->lchild != NULL) {
            node* pre = findMax((*root)->lchild);
            (*root)->data = pre->data;
            deleteNode(&((*root)->lchild), pre->data);
        }
        // Case 3: Has right subtree
        else {
            node* next = findMin((*root)->rchild);
            (*root)->data = next->data;
            deleteNode(&((*root)->rchild), next->data);
        }
    }
}

// Preorder traversal of BST
void preorder_traversal(node* root) {
    if(root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->lchild);
        preorder_traversal(root->rchild);
    }
}

// Free all nodes in BST
void freeTree(node* root) {
    if(root != NULL) {
        freeTree(root->lchild);
        freeTree(root->rchild);
        free(root);
    }
}

int main() {
    // Test data
    int data[] = {5, 3, 7, 1, 4, 6, 8};
    int n = sizeof(data) / sizeof(data[0]);
    
    // Create BST
    node* root = Create(data, n);
    
    // Test preorder traversal
    printf("Preorder traversal: ");
    preorder_traversal(root);
    printf("\n");
    
    // Test search function
    printf("Search for 4: ");
    search(root, 4);
    printf("Search for 9: ");
    search(root, 9);
    
    // Test insertion
    printf("Insert 9\n");
    insert(&root, 9);
    printf("Preorder traversal after insertion: ");
    preorder_traversal(root);
    printf("\n");
    
    // Test deletion
    printf("Delete 3\n");
    deleteNode(&root, 3);
    printf("Preorder traversal after deletion: ");
    preorder_traversal(root);
    printf("\n");
 
    freeTree(root);
    
    return 0;
}