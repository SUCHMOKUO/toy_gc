#include <stdio.h>
#include <stdlib.h>

#include "vm.h"

int main() {
  VM* vm = new_vm();

  // 创建整数类型对象 a.
  int a_data = 10;
  Object* a = new_object(vm, INT, &a_data);
  // 创建整数类型对象 b.
  int b_data = 20;
  Object* b = new_object(vm, INT, &b_data);
  // 创建引用类型对象 ref1, 其指向对象 a.
  Object* ref1 = new_object(vm, REF, a);
  // 创建引用类型对象 ref2, 其指向对象 ref1.
  Object* ref2 = new_object(vm, REF, ref1);
  
  // 删除对象 a, b 与 ref1.
  // 但由于 a 与 ref1 可通过 ref2 访问到.
  // 因此并不会被 gc 回收.
  // 相对的, 由于 b 无法再被访问到, 所以会被回收.
  delete_object(vm, a);
  delete_object(vm, b);
  delete_object(vm, ref1);
  
  gc(vm);
  
  exit(0);
}