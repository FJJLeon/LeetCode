#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int main() {
    vector<string> words{"time", "me", "limit"};
    // lambda expression for custom sort
    sort(words.begin(), words.end(), [](const string& s1, const string& s2){
        return s1.size() > s2.size();
    });

    return -1;
}