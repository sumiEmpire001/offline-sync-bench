#include "../../include/SyncQueue.h"
// Demonstrates pending/acknowledged state in RAM; no network or flash persistence.
sync::Queue<8> queue;
void setup(){Serial.begin(115200);queue.enqueue(1,1,42);
 const sync::Record* item=queue.next();
 if(item){Serial.println(item->value);queue.acknowledge(item->id,item->version);}
}
void loop(){}
