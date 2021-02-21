#include <iostream>
#include <vector>

#include "queue.h"

void Click_Queue::clear() {
  row.clear();
  col.clear();
}

void Click_Queue::enqueue(int row_, int col_) {
  if (row.size() >= 2) {
    row.erase(row.begin());
    col.erase(col.begin());
  }
  row.push_back(row_);
  col.push_back(col_);
}

void Click_Queue::print() {
  printf("Contents:\n");
  for (int i=0;i<row.size();i++)
    printf("(%d, %d)\n", row[i], col[i]);
}
