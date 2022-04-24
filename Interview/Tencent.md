# Tencent



## 4.24 

### 1.

```c++
int main () {
    long long n, m;
    cin >> n >> m;
    
    long long ans = n;
    
    for (int i = 0; i < m; ++i) { // m次更换
        double p;
        cin >> p;

        double add = (double)ans * p / (1.0 - p);
        
        if (add - (long long)add < 1e-6)
            add -= 1;
        
        ans += add;
    }
    
    cout << ans << endl;
    
    
    return 0;
}
```



### 2.

```c++

int main () {
 	int c;
    cin >> c;
    
}
```

