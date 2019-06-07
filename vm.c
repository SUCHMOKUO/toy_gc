#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vm.h"

static Object* vm_alloc() {
  Object* o = (Object*) malloc(sizeof(Object));
  printf("create object: %p\n", o);
  return o;
}

static void vm_free(Object* o) {
  printf("\nfreed: %p\n", o);
  bool is_ref = (o->t == REF);
  if (is_ref) {
    printf("object value: %p\n", o->data.ref);
  } else {
    printf("object value: %d\n", o->data.num);    
  }
  free(o);
}

VM* new_vm() {
  VM* vm = (VM*) malloc(sizeof(VM));
  vm->sp = vm->stack;
  vm->mem.size = 0;
  vm->mem.head = NULL;
  vm->mem.tail = NULL;
  return vm;
}

Object* new_object(VM* vm, Type t, void* data) {
  Object* o = vm_alloc();
  o->t = t;
  if (t == REF) {
    o->data.ref = (Object*) data;
  } else {
    o->data.num = *(int*) data;
  }
  push(vm, o);
  add_data(vm, o);
  return o;
}

void delete_object(VM* vm, Object* o) {
  // qwq...I know it's dirty...
  // but I'm too lazy to implement a stack.
  VM* tmp_stack = new_vm();
  Object* cur = NULL;
  while ((cur = pop(vm)) != o) {
    push(tmp_stack, cur);
  }
  while (0 != stack_size(tmp_stack)) {
    push(vm, pop(tmp_stack));
  }
  free(tmp_stack);
  printf("delete object: %p\n", o);
}

void gc(VM* vm) {
  mark_all(vm);
  sweep(vm);
}

static void push(VM* vm, Object* o) {
  if (stack_size(vm) == STACK_SIZE) {
    fprintf(stderr, "stack overflow!");
    exit(-1);
  }
  *vm->sp = o;
  vm->sp++;
}

static Object* pop(VM* vm) {
  if (stack_size(vm) == 0) {
    fprintf(stderr, "stack underflow!");
    exit(-1);
  }
  vm->sp--;
  return *vm->sp;
}

static int stack_size(VM* vm) {
  int size = vm->sp - vm->stack;
  // printf("stack size: %d\n", size);
  return size;
}

static void add_data(VM* vm, Object* o) {
  if (vm->mem.size == 0) {  
    vm->mem.head = vm->mem.tail = o;
  } else {
    vm->mem.tail->next = o;
    vm->mem.tail = o;
  }
  vm->mem.size++;
}

static void mark(Object* o) {
  if (o->marked) return;
  o->marked = true;
  printf("\nmarked: %p\n", o);
  printf("object value: ");
  bool is_ref = (o->t == REF);

  if (is_ref) {
    printf("%p\n", o->data.ref);
  } else {
    printf("%d\n", o->data.num);
  }

  if (is_ref) {
    printf("object is REF, point to %p\n", o->data.ref);
    mark(o->data.ref);
  }
}

static void mark_all(VM* vm) {
  int size = stack_size(vm);
  printf("\nstart mark, current stack size: %d\n", size);
  for (int i = 0; i < size; i++) {
    mark(vm->stack[i]);
  }
}

static void sweep(VM* vm) {
  int data_len = vm->mem.size;
  Object* prev = NULL;
  Object* cur = vm->mem.head;
  Object* free_target = NULL;
  while (data_len-- > 0) {
    if (cur->marked) {
      cur->marked = false;
      prev = cur;
      cur = cur->next;
    } else {
      free_target = cur;
      cur = cur->next;
      if (prev != NULL) {
        prev->next = free_target->next;
      } else {
        vm->mem.head = free_target->next;
      }
      vm->mem.size--;
      vm_free(free_target);
    }
  }
}