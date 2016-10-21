# homework_nthPrime
用于查找第N个素数，0&lt;N&lt;=1e8
编译环境 Win7 + MinGW5.3.0 32bit

实现思路如下：
查找第N个素数不需要列出1~N所有的素数，可以用素数计数公式来限定范围搜索；

在n>=6时，有n ln n + n ln ln n - n < p(n) < n ln n + n ln ln n,p(n)是第n个素数
然后对这一范围内的每个（奇）数x， 用Meissel—Lehmer公式计算pi(x)，定位到pi(x) = n的最小整数，即为所求数

在算法中需要多次调用素数表和欧拉函数表，因此用p(n)的上限值计算相应的表，以便反复调用
