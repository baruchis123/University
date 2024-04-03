#include <stdlib.h>
#include "RBTree.h"

/**
 *
 * @param compareFunc
 * @param freeFunc
 * @return
 */
RBTree *newRBTree(CompareFunc compareFunc, FreeFunc freeFunc)
{
    RBTree *newTree;
    newTree = (RBTree*) malloc(sizeof(RBTree)); //instance of a RBTree
    if (newTree == NULL) //check if allocation worked
    {
        return NULL;
    }
    // initiate tree fields
    newTree->freeFunc = freeFunc;
    newTree->compFunc = compareFunc;
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}

/**
 * This function is a helper for all basic tree actions, finds a node in the tree.
 * @param node
 * @param data
 * @param tree
 * @return returns said node upon finding, else returns supposed parent
 */
Node * rbTreeFind(Node * pNode, Node *node, const void *data, const RBTree *tree)
{
    // if node not found return parent
    if (node == NULL)
    {
        return pNode;
    }
    // if node is found
    if (tree->compFunc(node->data, data) == 0)
    {
        return node;
    }
    // if the node is smaller than given data, go right
    else if (tree->compFunc(node->data, data) < 0)
    {
        return rbTreeFind(node, node->right, data, tree);
    }
    // if the node is bigger than given data, go left
    else
    {
        return rbTreeFind(node, node->left, data, tree);
    }
}

/**
 *
 * @param tree
 * @param data
 * @return
 */
int RBTreeContains(const RBTree *tree, const void *data)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (data == NULL)
    {
        return 0;
    }
    if (tree->size == 0)
    {
        return 0;
    }
    // find the node in the tree
    Node * node = rbTreeFind(NULL, tree->root, data, tree);
    // if any node was returned with different data, not contained
    if (tree->compFunc(node->data, data) != 0)
    {
        return 0;
    }
    // node contained
    else
    {
        return 1;
    }
}

/**
 * this func creates a pointer to a node on the heap.
 * @return returns a pointer to said node
 */
Node * createNode()
{
    Node *node = (Node *) calloc(sizeof(Node), 1);
    if (node == NULL)
    {
        return NULL;
    }
    node->color = RED;
    return node;
}

/**
 * this func does a right rotation to a given node
 * @param node
 * @param tree
 */
void rightRotation(Node *node, RBTree *tree)
{
    // create a temp pointer to a node
    Node * tempNode = node->left;
    // point node to new parent and parent to new node
    node->left->parent = node->parent;
    // if parent isn't root
    if (node->left->parent != NULL)
    {
        // if parent is smaller hang on right
        if (tree->compFunc(node->left->parent->data, node->left->data) < 0)
        {
            node->left->parent->right = node->left;
        }
        // hang on left
        else
        {
            node->left->parent->left = node->left;
        }
    }
    node->left = node->left->right;
    tempNode->right = node;
    node->parent = tempNode;
    if (node->left != NULL)
    {
        node->left->parent = node;
    }
    if (tempNode->parent == NULL)
    {
        tree->root = tempNode;
    }
}


/**
 * this func does a left rotation to a given node
 * @param node
 * @param tree
 */
void leftRotation(Node *node, RBTree *tree)
{
    // create a temp pointer to a node
    Node * tempNode = node->right;
    // point node to new parent and parent to new node
    node->right->parent = node->parent;
    // if parent isn't root
    if (node->right->parent != NULL)
    {
        // if parent is smaller hang on right
        if (tree->compFunc(node->right->parent->data, node->right->data) < 0)
        {
            node->right->parent->right = node->right;
        }
        // hang on left
        else
        {
            node->right->parent->left = node->right;
        }
    }
    node->right = node->right->left;
    tempNode->left = node;
    node->parent = tempNode;
    if (node->right != NULL)
    {
        node->right->parent = node;
    }
    if (tempNode->parent == NULL)
    {
        tree->root = tempNode;
    }
}

/**
 * this func fixes the tree so that the colors are legit
 * @param node
 * @param tree
 */
void colorTreeIns(Node * node, RBTree *tree)
{
    // if parent is root change to black
    if (node->parent == NULL)
    {
        node->color = BLACK;
        return;
    }
    // if parent node is black do nothing
    if (node->parent->color == BLACK)
    {
        return;
    }
    if (node->parent->color == RED)
    {
        if (node->parent->parent->left != NULL && node->parent->parent->right != NULL) // check if can compare
        {
            // third option
            if (node->parent->parent->left->color == RED && node->parent->parent->right->color == RED)
            {
                node->parent->parent->color = RED;
                node->parent->parent->right->color = BLACK;
                node->parent->parent->left->color = BLACK;
                return colorTreeIns(node->parent->parent, tree);
            }
        }
        Node *gParentNode = node->parent->parent;
        // check if parent isn't root
        if (gParentNode != NULL)
        {
            if (gParentNode->left != NULL && node->parent->right != NULL) // check if i can compare
            {
                if (gParentNode->left == node->parent && node->parent->right == node) // if not a chain
                {
                    leftRotation(node->parent, tree);
                }
            }
            if (gParentNode->right != NULL && node->parent->left != NULL) // check if can compare
            {
                if (gParentNode->right == node->parent && node->parent->left == node) // if not chain
                {
                    rightRotation(node->parent, tree);
                }
            }
            if (gParentNode->left != NULL && gParentNode->left->left != NULL) //check if chain of left children
            {
                if (gParentNode->left == node || gParentNode->left->left == node)
                {
                    rightRotation(gParentNode, tree);
                    gParentNode->parent->color = BLACK;
                    gParentNode->color = RED;
                    return;
                }
            }
             //last option chain of right children
            leftRotation(gParentNode, tree);
            gParentNode->parent->color = BLACK;
            gParentNode->color = RED;
            return;
        }
    }
}

/**
 * This func erases a node and frees its data.
 * @param node- node to be erased
 * @param tree- the parent tree
 */
void eraseNode(Node ** node, RBTree * tree)
{
    tree->freeFunc((*node)->data);
    // if node's parent's aren't NULL remove pointers
    if ((*node)->parent != NULL)
    {
        if ((*node)->parent->right == (*node))
        {
            (*node)->parent->right = NULL;
        }
        else if ((*node)->parent->left == (*node))
        {
            (*node)->parent->left = NULL;
        }
    }
    free((*node));
    (*node) = NULL;
    tree->size -= 1;
}

/**
 * This func is in charge of recoloring the tree if a node was labeled as DB, it handles all the recursive func calls.
 * @param cNode - the erased node's child
 * @param pNode - the erased node's parent
 * @param tree - the tree we are recoloring
 */
void dbHelper(Node *cNode, Node *pNode, RBTree *tree)
{
    Node *sNode = NULL;
    int sFlag = 0;
    if (pNode == NULL) // if C is a root, erase DB and we're done
    {
        return;
    }
    if (pNode->left == cNode)
    {
        sNode = pNode->right;
        sFlag = 1;
    }
    else
    {
        sNode = pNode->left;
    }
    // if S is black and both his sons are black (don't forget to check for NULL)
    if (sNode->color == BLACK && (sNode->left == NULL || sNode->left->color == BLACK) &&
        (sNode->right == NULL || sNode->right->color == BLACK))
    {
        // if P is red, remove DB, change P to black, change s to red
        if (pNode->color == RED)
        {
            pNode->color = BLACK;
            sNode->color = RED;
            return;
        }
        // if P is black, note P as DB, change S to red, note P=C
        else
        {
            sNode->color = RED;
            return dbHelper(pNode, pNode->parent, tree); // go recursive and fix the tree
        }
    }
    // if S is red change S to black and P to red
    if (sNode->color == RED)
    {
        sNode->color = BLACK;
        pNode->color = RED;
        // rotate on P, use flag to recognize direction
        if (sFlag == 0)
        {
            rightRotation(pNode, tree);
        }
        else
        {
            leftRotation(pNode, tree);
        }
        // note vertex with DB still is c and call func recursively
        return dbHelper(cNode, pNode, tree);
    }
    // if S is black and the son who is close to C is red and the other on is black
    if (sNode->color == BLACK && sFlag == 0 && sNode->right != NULL && sNode->right->color == RED &&
        (sNode->left == NULL || sNode->left->color == BLACK))
    {
        // note sc - close and sf - far, change sc to black and S to red
        sNode->right->color = BLACK;
        sNode->color = RED;
        // rotate sc away from DB
        leftRotation(sNode, tree);
        return dbHelper(cNode, pNode, tree);
    }
    if (sNode->color == BLACK && sFlag == 1 && sNode->left != NULL && sNode->left->color == RED &&
        (sNode->right == NULL || sNode->right->color == BLACK))
    {
        // note sc - close and sf - far, change sc to black and S to red
        sNode->left->color = BLACK;
        sNode->color = RED;
        // rotate sc away from DB
        rightRotation(sNode, tree);
        return dbHelper(cNode, pNode, tree);
    }
    // last situation if S is black and the far son from C is red
    if (sNode->color == BLACK && sFlag == 0 && sNode->left != NULL && sNode->left->color == RED)
    {
        // change S's color to P's color and vica versa
        Color temp = 0;
        temp = sNode->color;
        sNode->color = pNode->color;
        pNode->color = temp;
        // rotate towards DB on P , change S's red child to black and remove DB
        rightRotation(pNode, tree);
        sNode->left->color = BLACK;
        return;
    }
    if (sNode->color == BLACK && sFlag == 1 && sNode->right != NULL && sNode->right->color == RED)
    {
        // change S's color to P's color and vica versa
        Color temp = 0;
        temp = sNode->color;
        sNode->color = pNode->color;
        pNode->color = temp;
        // rotate towards DB on P , change S's red child to black and remove DB
        leftRotation(pNode, tree);
        sNode->right->color = BLACK;
        return;
    }
}

/**
 * If the node being erased has a child, that isn't NULL we will note it as cNode, else cNode will be NULL.
 * @param node
 * @return a node (or NULL)
 */
Node * cNodeCheck(Node *node)
{
    Node *cNode =  NULL;
    if (node->left != NULL)
    {
        cNode = node->left;
    }
    else
    {
        cNode =  node->right;
    }
    return cNode;
}

/**
 * This func is in charge of recoloring the the tree after a node was deleted.
 * @param mNode - the node to be deleted
 * @param tree - the tree being recolored
 */
void colorAfterDel(Node *mNode, RBTree *tree)
{
    // in all erases release data!!
    // m is node to be erased, c is child, p is parent, s is sibling
    Node * cNode = cNodeCheck(mNode);
    Node * pNode = mNode->parent;
    // if m is red, both children are leaves (black), so erase
    if (mNode->color == RED)
    {
        eraseNode(&mNode, tree);
    }
    // if m is black
    // if c is red, erase m, connect c to parent, and change c to red
    else if (cNode != NULL && cNode->color == RED)
    {
        // if mNode is root
        if (pNode == NULL)
        {
            eraseNode(&mNode, tree);
            cNode->color = BLACK;
            cNode->parent = NULL;
            tree->root = cNode;
            return;
        }
        int flag = 0;
        if (pNode->left == mNode)
        {
            flag = 1;
        }
        eraseNode(&mNode, tree);
        cNode->parent = pNode;
        if (flag == 1)
        {
            pNode->left = cNode;
        }
        else
        {
            pNode->right = cNode;
        }
        cNode->color = BLACK;
    }
    // you will need to use recursion here, so make sure to code accordingly
    // if m and c are black (only if m is a binary leaf so c is null)
    else
    {
        // erase m and note c as DB
        eraseNode(&mNode, tree);
        dbHelper(cNode, pNode, tree);
    }
}

/**
 * This func finds the successor node and then returns it.
 * @param node - node we want to succeed.
 * @return - the successor node.
 */
Node * successor(Node * node)
{
    // if the node has a right child
    if (node->right != NULL)
    {
        Node * tempNode = node->right;
        while (tempNode->left != NULL)
        {
            tempNode = tempNode->left;
        }
        return tempNode;
    }
    // else go up until there is a right turn (if no right turn our node is the biggest)
    else
    {
       while (node->parent != NULL)
       {
           if (node != node->parent->left)
           {
               node = node->parent;
           }
           else
           {
               break;
           }
       }
        return node->parent;
    }
}

void freeHelper(Node *node, RBTree *tree)
{
    if (node == NULL)
    {
        return;
    }
    Node *rightChild = node->right;
    Node *leftChild = node->left;
    tree->freeFunc(node->data);
    free(node);
    node = NULL;
    freeHelper(leftChild, tree);
    freeHelper(rightChild, tree);
}

/**
 *
 * @param tree
 */
void freeRBTree(RBTree **tree)
{
    Node *node = (*tree)->root;
    freeHelper(node, (*tree));
    free(*tree);
    (*tree) = NULL;
}

/**
 *
 * @param tree
 * @param func
 * @param args
 * @return
 */
int forEachRBTree(const RBTree *tree, forEachFunc func, void *args)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (tree->size == 0)
    {
        return 1;
    }
    Node * node =  tree->root;
    // if tree is empty
    if (node == NULL)
    {
        return 1;
    }
    // find leftmost node
    while (node->left != NULL)
    {
        node = node->left;
    }
    // if func doesn't work return 0.
    if (func(node->data, args) == 0)
    {
        return 0;
    }
    node = successor(node);
    // iterate over all node's in the tree using successor.
    while(node != NULL)
    {
        if (func(node->data, args) == 0)
        {
            return 0;
        }
        node = successor(node);
    }
    return 1;
}

/**
 *
 * @param tree
 * @param data
 * @return
 */
int deleteFromRBTree(RBTree *tree, void *data)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (data == NULL)
    {
        return 0;
    }
    Node * mNode;
    mNode = rbTreeFind(NULL, tree->root, data, tree);
    if (tree->compFunc(mNode->data, data) != 0) // check if exists
    {
        return 0;
    }
    // if node is the root and has no children
    if (mNode == tree->root && mNode->left == NULL && mNode->right == NULL)
    {
        eraseNode(&mNode, tree);
        tree->root = NULL;
        return 1;
    }
    Node * tempNode = NULL;
    // if node has two children
    // call successor
    if (mNode->right != NULL && mNode->left!= NULL)
    {
        tempNode = successor(mNode);
        void * tempData = tempNode->data;
        tempNode->data = mNode->data;
        mNode->data = tempData;
        colorAfterDel(tempNode, tree);
    }
    // now we have one of two ops, m has one child or no children
    // go color tree
    else
    {
        colorAfterDel(mNode, tree);
    }
    return 1;
}


/**
 *
 * @param tree
 * @param data
 * @return
 */

int insertToRBTree(RBTree *tree, void *data)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (data == NULL)
    {
        return 0;
    }
    if (tree->size == 0) // if root
    {
        Node *root = createNode();
        if (root == NULL)
        {
            return 0;
        }
        tree->root = root;
        tree->root->data = data;
        tree->root->color = BLACK;
        tree->size++;
        return 1;
    }
    Node *node = NULL;
    node = rbTreeFind(NULL, tree->root, data, tree); //check if node exists, if not get parent to be
    if (tree->compFunc(node->data, data) == 0) // check if exists
    {
        return 0;
    }
    else if (tree->compFunc(node->data, data) < 0) // data is larger, hang on right
    {
        Node *childNode = createNode();
        if (childNode == NULL) // check if allocation is NULL
        {
            return 0;
        }
        node->right = childNode; // hang node
        childNode->parent = node;
        childNode->data = data;
        tree->size++; // change tree size
        colorTreeIns(childNode, tree); // fix tree
    }
    else if (tree->compFunc(node->data, data) > 0) // if data is smaller, hang on left
    {
        Node *childNode = createNode();
        if (childNode == NULL) // check if allocation is NULL
        {
            return 0;
        }
        node->left = childNode; // hang node
        childNode->parent = node;
        childNode->data = data;
        tree->size++; // change tree size
        colorTreeIns(childNode, tree); // fix tree
    }
    return 1;
}

