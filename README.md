# 一个堆栈虚拟机的简单 GC 实现（标记清除）

参考[该文章](http://it.deepinmind.com/gc/2014/03/26/babys-first-garbage-collector.html).

```
make
./main

# output:
create object: 0x55ec5b1fea90
create object: 0x55ec5b1feed0
create object: 0x55ec5b1fef00
create object: 0x55ec5b1fef30
delete object: 0x55ec5b1fea90
delete object: 0x55ec5b1feed0
delete object: 0x55ec5b1fef00

start gc, current stack size: 1

marked: 0x55ec5b1fef30
object value: 0x55ec5b1fef00
object is REF, point to 0x55ec5b1fef00

marked: 0x55ec5b1fef00
object value: 0x55ec5b1fea90
object is REF, point to 0x55ec5b1fea90

marked: 0x55ec5b1fea90
object value: 10

freed: 0x55ec5b1feed0
object value: 20
```