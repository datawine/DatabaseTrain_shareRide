#include "GPTree.h"

using namespace std;

int main() {
    Ans ans;
    ans.init();
    ans.read();
    ans.build_tree();
    ans.save();
    return 0;
}