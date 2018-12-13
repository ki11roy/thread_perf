# Thread Performance
Performance of thread vs fork creation:

```
noop ~= max(MHz)           2995.23
std::thread().join()       34175.4     2.92608s
std::thread().detach()     67478.6     1.48195s
fork()                     13962       0.00716228s
```
