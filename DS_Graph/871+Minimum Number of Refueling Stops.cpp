class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> pq;
        int fuel = startFuel;
        int dis = 0;
        int cnt = 0;

        for (int i = 0; i < stations.size(); ) {
            dis += fuel;    // 先走
            fuel = 0;
            
            if (dis >= target) {
                return cnt;
            }            
            
            while (i < stations.size() && dis >= stations[i][0]) { // 加油站全部加入队列中
                pq.emplace(stations[i][1]); 
                i++;
            }

            if (fuel == 0) {    // 没油了
                if (pq.size()) {
                    auto cur = pq.top(); pq.pop();
                    fuel += cur;
                    cnt++;      // 加了一次油
                } else {
                    return -1;
                }
            } 
        }


        return -1;
    }
};