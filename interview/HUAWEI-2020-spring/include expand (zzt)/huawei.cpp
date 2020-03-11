#include<iostream>
#include<sstream>
#include<vector>
#include<map>
#include<stack>
#include<float.h>
#include<assert.h>

using namespace std;

/*
input:
a b;a c;b e;e b;c d;d a
output:
EXPAND:a b e c d
CIRCLE:b e b;a c d a
*/

int main() {
    // input
    string input;
    getline(cin, input);

    // record each input pair (seems meaningless)
    vector<pair<string, string> > inputPair;
    // record 1->N include relation
    map<string, vector<string>> includeMap;
    // flag for file expanded or not
    map<string, bool> expanded;
    
    // process input line to pair vector
    // patch ';' at end
    input.push_back(';');
    // split input by ';'
    int begin = 0, end = 0;
    string a, b;
    stringstream ss;
    while ((end = input.find(';', begin)) != input.npos) {
        ss.clear();
        ss << input.substr(begin, end - begin);
        ss >> a >> b;
        // record input pair <a, b>
        inputPair.push_back(make_pair(a, b));
        // record a->b
        includeMap[a].push_back(b);
        // a, b not expanded
        expanded[a] = false;
        expanded[b] = false;

        begin = end + 1;
    }

    // expand sequence
    vector<string> expandSeq;
    string root = inputPair[0].first;
    // first headfile expanded
    expandSeq.push_back(root);
    expanded[root] = true;
    
    // <file, level>
    typedef pair<string, int> P;
    // stack for DFS
    stack<P> visitStack;
    // push file included by first headfile into DFS stack
    // note reverse, include first expand first
    vector<string> belong = includeMap[root];
    for (int i=belong.size()-1; i>=0; --i) {
        visitStack.push(make_pair(belong[i], 1));
    }

    // stack for current visit path to check circle
    vector<P> levelStack;
    levelStack.push_back(make_pair(root, 0));
    
    // store circle string if exist
    vector<string> circle;

    // DFS
    while (!visitStack.empty()) {
        P p = visitStack.top();
        string file = p.first;
        int level = p.second;
        visitStack.pop();
        // if file already expanded, check circle
        if (expanded[p.first]) {
            int c = 0;
            while (c < levelStack.size()) {
                if (levelStack[c].first == p.first) {
                    // circle exist, construct circle string
                    string out;
                    while (c < levelStack.size()) {
                        out += levelStack[c].first + ' ';
                        ++c;
                    }
                    out += p.first;
                    circle.push_back(out);
                }
                ++c;
            }
            continue;
        }
        // file not expanded
        else {
            // add to expanded sequence
            expandSeq.push_back(file);
            // change expanded flag
            expanded[file] = true;

            // judge file path 
            if (levelStack.rbegin()->second < level) {
                // traverse deeper
                assert(levelStack.rbegin()->second+1 == level);
                levelStack.push_back(p);
            } else {
                // path end, backtrace already
                while (levelStack.rbegin()->second >= level) {
                    levelStack.pop_back();
                }
                levelStack.push_back(p);
            }

            // push file included by current headfile into DFS stack
            belong = includeMap[file];
            for (int i=belong.size()-1; i>=0; --i) {
                visitStack.push(make_pair(belong[i], level+1));
            }
        }
    }

    // output
    cout << "EXPAND:";
    for (string s : expandSeq) {
        cout << s << " ";
    }
    cout << endl;

    if (!circle.empty()) {
        cout << "CIRCLE:";
        for (int i=0; i<circle.size(); ++i) {
            cout << circle[i];
            if (i != circle.size()-1) {
                cout << ";";
            }
        }
    }

    return 0;
}