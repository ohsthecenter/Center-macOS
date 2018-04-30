#include <iostream>
#include <cstdio>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <functional>
#define MAXSIZE 70
#define MAXN 9999
#define MAXND MAXN / 10
#define INF 99999999
#define MAXEDGE 1000000
#define MAXVERTEX 10
#define EPS 0.00001
#define PI 3.14159265
#define nil NULL
typedef long long ll;
using namespace std;

int n;
int list[MAXSIZE][MAXSIZE], dayPeople[MAXSIZE];
map<int, string> mp;
vector<string> ans[MAXSIZE];

int solve() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > student;
    set<pair<int, int> > day;
    int vis[MAXSIZE], maxDay = -1;
    
    for (int i = 0; i < n; i++) {
        student.push(make_pair(0, i));
    }
    for (int i = 1; i <= n; i++) {
        day.insert(make_pair(dayPeople[i], i));
        vis[i] = 0;
    }
    
    int counter = 0;
    while (counter < n * 2) {
        pair<int, int> cur = student.top();
        int curStu = cur.second;
        student.pop();
                
        for (set<pair<int, int> >::iterator it = day.begin(); it != day.end(); it++) {
            pair<int, int> d = *it;
            if (list[curStu][d.second]) {
                list[curStu][d.second] = 0;
                vis[d.second]++;
                cur.first++;
                ans[d.second].push_back(mp[curStu]);
                maxDay = max(cur.first, maxDay);
                student.push(cur);
                day.erase(it);
                if (vis[d.second] < 2) {
                    d.first--;
                    day.insert(d);
                }
                counter++;
                break;
            }
        }
    }
    
    return maxDay;
}

int main() {
    int m, d, day;
    string name;

    ios::sync_with_stdio(false);
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        cin >> name >> d;
        mp[i] = name;
        while (d--) {
            cin >> day;
            list[i][day] = 1;
            dayPeople[day]++;
        }
    }
    
    int maxDay = solve();
    
    cout << maxDay << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Day " << i << " ";
        cout << ans[i][0] << " " << ans[i][1] << endl;
    }

    return 0;
}
