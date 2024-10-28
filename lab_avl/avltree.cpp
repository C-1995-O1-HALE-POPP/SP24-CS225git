/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}
template <class K, class V>
void AVLTree<K, V>::updateH(Node*& t){
    if(t==NULL) return;
    int left=(t->left==NULL)?-1:heightOrNeg1(t->left);
    int right=(t->right==NULL)?-1:heightOrNeg1(t->right);
    t->height = std::max(left,right) + 1;
}
template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t = temp;
    updateH(t);
    updateH(t->left);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp;
    updateH(t);
    updateH(t->right);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(subtree==NULL) return;
    int deltaHeight = heightOrNeg1(subtree->left)-heightOrNeg1(subtree->right);
    if(deltaHeight>=2){
        int deltaHeightSub=heightOrNeg1(subtree->left->left)-heightOrNeg1(subtree->left->right);
        if(deltaHeightSub==1) rotateRight(subtree);
        else if (deltaHeightSub==-1)rotateLeftRight(subtree);
    }else if(deltaHeight<=-2){
        int deltaHeightSub=heightOrNeg1(subtree->right->right)-heightOrNeg1(subtree->right->left);
        if(deltaHeightSub==1) rotateLeft(subtree);
        else if (deltaHeightSub==-1) rotateRightLeft(subtree);
    }
    updateH(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) subtree = new Node(key, value);
    if(key < subtree->key) insert(subtree->left, key, value);
    else if(key > subtree->key) insert(subtree->right, key, value);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            rebalance(subtree);
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* iop=subtree->left;
            while(iop->right!=NULL) iop=iop->right;
            swap(iop,subtree);
            remove(subtree->left, key);
            rebalance(subtree);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->right!=NULL){
                swap(subtree->right,subtree);
                remove(subtree->right, key);
            }else if(subtree->left!=NULL){
                swap(subtree->left,subtree);
                remove(subtree->left, key);
            }
            rebalance(subtree);
        }
        // your code here
    }
}
