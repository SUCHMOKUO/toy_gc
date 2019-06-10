#pragma once

#include <stdbool.h>

#define STACK_SIZE 256

typedef enum {
  INT,  // int
  REF   // reference of another object
} Type;

typedef struct _Object {
  Type t;

  union {
    int num;
    struct _Object* ref;
  } data;
  
  struct _Object* next;
  bool marked;
} Object;

typedef struct {
  Object* stack[STACK_SIZE];
  Object** sp;  // 栈顶指针
  Object* mem;  // 分配的内存，以链表形式保存
} VM;

static Object* vm_alloc(VM* vm);
static void vm_free(Object* o);
static void push(VM* vm, Object* o);
static Object* pop(VM* vm);
static int stack_size(VM* vm);
static void mark(Object* o);
static void mark_all(VM* vm);
static void sweep(VM* vm);

VM* new_vm();
Object* new_object(VM* vm, Type t, void* data);
void delete_object(VM* vm, Object* o);
void gc(VM* vm);