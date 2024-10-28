/* Your code here! */
#include <vector>
#include <string>
using namespace std;
class dsets{
    public:
    dsets(const int size);
    void addElements(const int size);
    int find(int elem);
    void setunion(int a, int b);
    private:
    vector<int> set;
};