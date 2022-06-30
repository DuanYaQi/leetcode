const int maxn = 101;
const int mmm = 1e9 + 7;
class Solution {
public:
    void set_primes(int n, vector<bool> &isPrime, vector<int> &Primes) {			// 筛到 n
        isPrime[0] = false;	// 1不是素数
        isPrime[1] = false;	// 1不是素数
        
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) 
                Primes.push_back(i);	// 没筛掉,i成为下一个素数
            
            for (int j = i * 2; j < n; j += i) {	//用Primes[j]筛掉合数Primes[j] * i
                isPrime[j] = false;
            }
        }
        
        return;
    }

    int numPrimeArrangements(int n) {
        vector<bool> isPrime(maxn, true);   // isPrime[i] == 1表示：i是素数 
        vector<int> Primes;	// 素数表        // Primes[i] 表示第i个质数
        long long res = 1;

        set_primes(maxn, isPrime, Primes);
        
        auto iter = lower_bound(Primes.begin(), Primes.end(), n);
        int cnt;

        if (*iter == n) cnt = iter - Primes.begin() + 1;
        else cnt = iter - Primes.begin(); 
        
        int leftCnt = n - cnt;
        
        for (; cnt > 0; cnt -= 1) {
            res = res * cnt % mmm;
        }

        for (; leftCnt > 0; leftCnt -= 1) {
            res = res * leftCnt % mmm;
        }

        return res;
    }
};