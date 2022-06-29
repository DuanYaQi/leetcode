//////////////////////////////////////////////////////// 普通hash
class Solution {
private:
    unordered_map<int, string> dataBase;
    unordered_map<string, int> urlToKey;
    int cnt = 0;

public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string res = "http://tinyurl.com/";
        
        if (urlToKey.count(longUrl) > 0) {
            return res + to_string(urlToKey[longUrl]);
        }
        cnt++;
        dataBase[cnt] = longUrl;
        urlToKey[longUrl] = cnt;

        return res + to_string(cnt);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int p = shortUrl.rfind('/') + 1;    // 从字符串右侧开始匹配
        int key = stoi(shortUrl.substr(p, int(shortUrl.size()) - p));

        return dataBase[key];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));






//////////////////////////////////////////////哈希




typedef long long ll;
const ll k1 = 1117;
const ll k2 = 1e9 + 7;

class Solution {
private:
    unordered_map<int, string> dataBase;
    unordered_map<string, int> urlToKey;

public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string res = "http://tinyurl.com/";
        
        if (urlToKey.count(longUrl) > 0) {
            return res + to_string(urlToKey[longUrl]);
        }
        
        ll key = 0, base = 1;
        for (auto c : longUrl) {
            key = (key + c * base) % k2;
            base = (base * k1) % k2;
        }        
        
        while (dataBase.count(key) > 0) {
            key = (key + 1) % k2;
        }

        dataBase[key] = longUrl;
        urlToKey[longUrl] = key;

        return res + to_string(key);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int p = shortUrl.rfind('/') + 1;    // 从字符串右侧开始匹配
        int key = stoi(shortUrl.substr(p, int(shortUrl.size()) - p));

        return dataBase[key];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));