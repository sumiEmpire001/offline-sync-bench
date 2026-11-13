#include "SyncQueue.h"
#include <cstdlib>
#include <iostream>
using namespace sync;
void check(bool b){if(!b){std::cerr<<"FAIL\n";std::exit(1);}}
int main(){
 Queue<2> q;check(q.enqueue(0,1,4)==Status::Invalid);
 check(q.enqueue(1,1,10)==Status::Ok);
 check(q.enqueue(1,1,10)==Status::Duplicate);
 check(q.enqueue(1,0,10)==Status::Invalid);
 check(q.enqueue(1,2,20)==Status::Ok);
 check(q.acknowledge(1,1)==Status::Conflict);
 check(q.enqueue(2,1,-10)==Status::Ok);
 check(q.enqueue(3,1,0)==Status::Full);
 check(q.pending()==2&&q.next()->id==1);
 check(q.acknowledge(1,2)==Status::Ok);
 check(q.acknowledge(1,2)==Status::Duplicate);
 check(q.acknowledge(3,1)==Status::Missing);
 q.clearAcknowledged();check(q.size()==1&&q.next()->id==2);
 check(q.enqueue(3,1,0)==Status::Ok);
 check(q.enqueue(2,0,0)==Status::Invalid);
 check(q.enqueue(2,1,0)==Status::Duplicate);
 std::cout<<"sync tests passed\n";
}
