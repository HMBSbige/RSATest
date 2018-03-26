# RSA Algorithm
* n = p*q, where p and q are distinct primes.
* phi, φ = (p-1)(q-1)
* e < n such that gcd(e, phi)==1
* d = e**(-1) mod phi.
* c = m**e mod n, 1<m<n.
* m = c**d mod n.

# 使用说明
这只是RSA算法测试，因算法问题生成的密钥长度其实不定，写着2048位可能生成2047位

# 例子
![](https://raw.githubusercontent.com/HMBSbige/RSATest/master/pic/sample.png)

# 编译所需
[gmp大数计算](https://github.com/HMBSbige/gmp)

# 参考资料
http://www.di-mgt.com.au/rsa_alg.html
