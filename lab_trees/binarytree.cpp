/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirrorHelper(root);
}

template <typename T>
void BinaryTree<T>::mirrorHelper(Node* node){
    if(node == NULL){
        return;
    }
    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
    mirrorHelper(node->left);
    mirrorHelper(node->right);
}
/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{   
    Node* last = root;
    while(last->left!= NULL) last=last->left;
    return isOrderedHelper(root,last);
}
template <typename T>
bool BinaryTree<T>::isOrderedHelper(const Node* node,const Node* last) const{
    if(node == NULL) return true;
    // left child
    bool left=isOrderedHelper(node->left,last);
    // root
    bool mid=true;
    if (last->elem > node->elem) mid = false;
    last=node;
    //right child
    bool right=isOrderedHelper(node->right,last);

    return left&&mid&&right;
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    vector<T> curr; // the path of current added nodes in current recursion binary
    printPathsHelper(root,curr,paths);
}

template <typename T>
void BinaryTree<T>::printPathsHelper(Node* node, vector<T> curr,vector<vector<T> > &paths) const{
    curr.push_back(node->elem);
    if(node->left==nullptr&&node->right==nullptr) paths.push_back(curr);
    if(node->left!=nullptr) printPathsHelper(node->left,curr,paths);
    if(node->right!=nullptr) printPathsHelper(node->right,curr,paths);
}
/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    int sum = 0;
    sumDistancesHelper(root,sum,-1);
    return sum;
}
template <typename T>
void BinaryTree<T>::sumDistancesHelper(Node* node, int& sum, int depth) const{
    if(node==nullptr) return;
    depth++;
    sum += depth;
    if(node->left!=nullptr) sumDistancesHelper(node->left,sum,depth);
    if(node->right!=nullptr) sumDistancesHelper(node->right,sum,depth);
    
}