int findClosest(vector<string>& words, string word1, string word2) {
    vector<int> w1, w2;
    for (int i = 0; i < words.size(); ++i) {
        if (words[i] == word1) w1.push_back(i);
        if (words[i] == word2) w2.push_back(i);
    }

    int res = 0x3f3f3f3f;
    for (int i = 0; i < w2.size(); ++i) {           // 对每个w2里的元素 在w1里找与其插值最小的下标
        auto first = lower_bound(w1.begin(), w1.end(), w2[i]);

        int dis = distance(w1.begin(), first);      
        //如果为空，则局部最小值是与w1最后一个元素的差值
        if (first == w1.end()) res = min(res, abs(w2[i] - w1[w1.size()-1]));    
        else {
            res = min(res, abs(w2[i] - w1[dis]));
            // 如果dis不是w1首元素，则局部最小值可能是dis，也可能是dis-1
            if (dis != 0) res = min(res, abs(w2[i] - w1[dis-1]));   
        }
    }

    return res;
}