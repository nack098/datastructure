#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  void *value;
  struct node *next;
  struct node *before;
} Node;

typedef struct linked_list {
  Node *first;
  Node *last;
  int size;
} LinkedList;

LinkedList *linked_list_new() {
  LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
  return list;
}

void linked_list_append(LinkedList *list, void *data) {
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->value = data;
  new_node->next = NULL;
  new_node->before = NULL;
  if (list->first == NULL) {
    list->first = new_node;
  }
  if (list->last != NULL) {
    list->last->next = new_node;
  }
  new_node->before = list->last;
  list->last = new_node;
  ++list->size;
}

Node *traverse(LinkedList *list, int index) {
  if (index >= list->size || index < 0) {
    return NULL;
  }
  Node *current = NULL;
  int i = 0;
  if (list->size - index > list->size / 2) {
    current = list->first;
    while (i != index) {
      current = current->next;
      ++i;
    }
  } else {
    current = list->last;
    while (list->size - i - 1 != index) {
      current = current->before;
      ++i;
    }
  }
  return current;
}

void *linked_list_at(LinkedList *list, int index) {
  return traverse(list, index)->value;
}

void linked_list_insert(LinkedList *list, void *data, int index) {
  Node *position = traverse(list, index);
  if (index >= list->size) {
    position = list->last;
  }
  if (index < 0) {
    position = list->first;
  }
  Node *new_node = (Node *)malloc(sizeof(Node));
  new_node->next = NULL;
  new_node->before = NULL;
  new_node->value = data;
  if (position->next != NULL) {
    new_node->next = position->next;
    position->next->before = new_node;
  }
  new_node->before = position;
  position->next = new_node;
  ++list->size;
}

void linked_list_delete(LinkedList *list, int index) {
  Node *position = traverse(list, index);
  if (index >= list->size) {
    position = list->last;
  }
  if (index < 0) {
    position = list->first;
  }
  if (position == list->first) {
    list->first = position->next;
  }
  if (position == list->last) {
    list->last = position->before;
  }
  if (position->before != NULL) {
    position->before->next = position->next;
    position->next->before = position->before;
  } else {
    if (position->next != NULL) {
      position->next->before = NULL;
    }
  }
  free(position);
  --list->size;
}

void print_list(LinkedList *list, int count) {
  if (count == 1)
    printf("------------------\n");
  printf("Test no.%d\n", count);
  printf("Size: %d\n", list->size);
  if (list->size == 0) {
    printf("First: NULL\n");
    printf("Last: NULL\n");
    printf("Mapping:\n\n");
  } else {
    printf("First: %d\n", *(int *)list->first->value);
    printf("Last: %d\n", *(int *)list->last->value);
    printf("Mapping:\n");
    Node *current = list->first;
    int index = 0;
    while (1) {
      if (current->next == NULL) {
        printf("(%d, %d)\n", index, *(int *)current->value);
        break;
      } else {
        printf("(%d, %d) -> ", index, *(int *)current->value);
        current = current->next;
      }
      ++index;
    }
  }
  printf("------------------\n");
}

void append_test() {
  int data[] = {1, 2, 3};
  LinkedList *list = linked_list_new();
  printf("Append Test\n");
  print_list(list, 1);
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    linked_list_append(list, &data[i]);
    print_list(list, i + 2);
  }
}

void traverse_test() {
  int data[] = {1, 2, 3, 4};
  LinkedList *list = linked_list_new();
  printf("Traverse Test\n");
  printf("------------------\n");
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    linked_list_append(list, &data[i]);
  }
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    printf("Test no.%d\n", i + 1);
    printf("Index: %d\n", i);
    printf("Value: %d\n", *(int *)linked_list_at(list, i));
    printf("------------------\n");
  }
}
void insert_test() {
  int data[] = {1, 2, 3, 4};
  LinkedList *list = linked_list_new();
  printf("Insertion Test\n");
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    linked_list_append(list, &data[i]);
  }

  int insert_data[] = {1, 2, 3, 4};
  for (int i = 0; i < sizeof(insert_data) / sizeof(int); ++i) {
    linked_list_insert(list, &insert_data[i], i);
    print_list(list, i + 1);
  }
}
void delete_test() {
  int data[] = {1, 2, 3, 4};
  LinkedList *list = linked_list_new();
  printf("Deletion Test\n");
  for (int i = 0; i < sizeof(data) / sizeof(int); ++i) {
    linked_list_append(list, &data[i]);
  }

  int insert_data[] = {1, 2, 3, 4};
  for (int i = 0; i < sizeof(insert_data) / sizeof(int); ++i) {
    linked_list_insert(list, &insert_data[i], 0);
  }

  printf("Size: %d\n", list->size);
  printf("Mapping:\n");
  Node *current = list->first;
  int index = 0;
  while (1) {
    if (current->next == NULL) {
      printf("(%d, %d)\n", index, *(int *)current->value);
      break;
    } else {
      printf("(%d, %d) -> ", index, *(int *)current->value);
      current = current->next;
    }
    ++index;
  }

  index = 0;

  for (int i = 0; i < sizeof(insert_data) / sizeof(int); ++i) {
    linked_list_delete(list, i);
    print_list(list, index + 1);
    ++index;
  }

  int size = list->size;
  for (int i = 0; i < size; ++i) {
    linked_list_delete(list, 0);
    print_list(list, index + 1);
    ++index;
  }
}

int main() {
  append_test();
  traverse_test();
  insert_test();
  delete_test();
  return 0;
}
