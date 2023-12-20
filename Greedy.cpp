#include <bits/stdc++.h>

//N Meetings in a room
int maxMeetings(int start[], int end[], int n)
{
    vector<pair<int,int>> v;
    for(int i=0;i<n;i++) v.push_back({end[i],start[i]});
    
    sort(v.begin(),v.end());
    
    int meetCount = 0;
    int meetEnd = -1;
    
    for(int i=0;i<n;i++) {
        if(v[i].second > meetEnd) {
            meetCount++;
            meetEnd = v[i].first;
        }
    }
    return meetCount;
}

//
