/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    if(s.size()==0) return 0;
    T top=s.top();
    s.pop();
    T ret=sum(s)+top;
    s.push(top);
    return ret;
    // Your code here
    // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    if(q.size()==0) return;
    // optional: queue<T> q2;
    // seperate the queue into blocks

    int size=q.size();
    unsigned blocknum=0;

    // get num of blks

    while(size>0 ){
        size-=blocknum;
        blocknum++;
    }
    blocknum--;
    // get length of each block
    T **blocks=new T*[blocknum];
    unsigned *sizes=new unsigned[blocknum];
    size=q.size();
    for(unsigned i=1; i<blocknum+1; i++){
        if(i<blocknum){
            size-=i;
            sizes[i-1]=i;
        }
        else sizes[i-1]=size;
    }
    // seperate the queue
    unsigned index=0;
    for(unsigned i=0; i<blocknum; i++){
        blocks[i]=new T[sizes[i]];
        for(unsigned j=0; j<sizes[i]; j++){
            blocks[i][j]=q.front();
            q.pop();
        }
        index+=sizes[i];
    }
    // reverse the order of the blocks if necessary
    for(unsigned i = 0; i < blocknum; i++){
        if(i%2==0) continue;
        T *newBlock = new T[sizes[i]];
        for(unsigned j = 0;j<sizes[i];j++) newBlock[j]=blocks[i][sizes[i]-j-1];
        for(unsigned j = 0;j<sizes[i];j++) blocks[i][sizes[i]-j-1]=0;
        delete[] blocks[i];
        blocks[i]=newBlock;
    }
    // push back to queue
    for(unsigned i = 0; i <blocknum; i++){
        for(unsigned j = 0;j<sizes[i];j++){
            q.push(blocks[i][j]);
            blocks[i][j]=0;
        }
        sizes[i]=0;
        delete[] blocks[i];
    }
    delete[] sizes;
    delete[] blocks;
    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    if(s.empty()) return true;

    T topS=s.top();
    s.pop();
    retval = verifySame(s, q);
    T frontQ=q.front();
    q.pop();
    retval = retval && (topS==frontQ);
    s.push(topS);
    q.push(frontQ);
    return retval;
}

}