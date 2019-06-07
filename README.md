# 一个堆栈虚拟机的简单GC实现（标记清除）

参考[该文章](http://it.deepinmind.com/gc/2014/03/26/babys-first-garbage-collector.html).

```
make
./main

# output:
create object: 0x55d1e7225a90
create object: 0x55d1e7225ed0
create object: 0x55d1e7225f00
create object: 0x55d1e7225f30
delete object: 0x55d1e7225a90
delete object: 0x55d1e7225ed0
delete object: 0x55d1e7225f00

start mark, current stack size: 1

marked: 0x55d1e7225f30
object value: 0x55d1e7225f00
object is REF, point to 0x55d1e7225f00

marked: 0x55d1e7225f00
object value: 0x55d1e7225a90
object is REF, point to 0x55d1e7225a90

marked: 0x55d1e7225a90
object value: 10

freed: 0x55d1e7225ed0
object value: 20
```