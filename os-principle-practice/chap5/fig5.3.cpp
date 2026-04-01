// Thread-safe queue interface
 const int MAX = 10;
 class TSQueue {
   // Synchronization variables
     Lock lock;
   // State variables
     int items[MAX];
     int front;
     int nextEmpty;
   public:
     TSQueue();
     ~TSQueue(){};
     bool tryInsert(int item);
     bool tryRemove(int *item);
 };
 // Initialize the queue to empty
 // and the lock to free.
 TSQueue::TSQueue() {
     front = nextEmpty = 0;
 }
 // Try to insert an item. If the queue is
 // full, return false; otherwise return true.
 bool
 TSQueue::tryInsert(int item) {
     bool success = false;
     lock.acquire();
     if ((nextEmpty - front) < MAX) {
         items[nextEmpty % MAX] = item;
         nextEmpty++;
         success = true;
     }
     lock.release();
     return success;
 }
 // Try to remove an item. If the queue is
 // empty, return false; otherwise return true.
 bool
 TSQueue::tryRemove(int *item) {
     bool success = false;
     lock.acquire();
     if (front < nextEmpty) {
         *item = items[front % MAX];
         front++;
         success = true;
     }
     lock.release();
     return success;
 }
// Figure 5.3: A thread-safe bounded queue. For implementation simplicity, we assume the queue stores integers (rather than
// arbitrary objects) and the total number of items stored is modest.
