#include "common/config.h"
#include "common/util.h"

#include "board.h"
#include "queue.h"
#include "core/piece.h"
#include "media/text.h"

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
