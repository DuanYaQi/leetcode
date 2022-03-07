#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<map>
#include<stack>
#include<sstream>
#include <assert.h>
#include<unordered_set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Chef {
    public:
    	void makeChicken() {
            std::cout << "The chef makes chicken" << std::endl;
        }
    
    	void makeSalad() {
            std::cout << "The chef makes salad" << std::endl;
        }
    
    	void makeSpecialDish() {
            std::cout << "The chef makes SpecialDish" << std::endl;
        }
};

class ItalianChef : public Chef{ // 继承父类 Chef
    public:
        void makePasta(){
            std::cout << "The italianchef makes pasta" << std::endl;
        }
    
    	void makeSpecialDish() { //重载父类函数
            std::cout << "The chef makes new SpecialDish" << std::endl;
        }
};

int main() {
    Chef chef;
    chef.makeChicken();
    //chef.makePasta();	//error
    
    ItalianChef ichef;
    ichef.makeSalad();
    ichef.makePasta();	//success
    ichef.makeSpecialDish();
    return 0;
}
