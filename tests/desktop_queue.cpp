#include "../Source/Application/modules/Common/Os/CrossPlatform/CMsgQueue.h"
#include <cassert>
#include <vector>
int main() {
 Ignite::CMsgQueue<int> queue(8);
 std::vector<std::thread> producers;
 std::vector<bool> received(4000, false);
 std::thread consumer([&] {
  for(int i=0;i<4000;++i) {int n=-1; queue.get(n,Ignite::TimeOut::kWaitForever); assert(n>=0 && n<4000); assert(!received[n]); received[n]=true;}
 });
 for(int p=0;p<4;++p) producers.emplace_back([&,p] {for(int i=0;i<1000;++i) assert(queue.put(p*1000+i));});
 for(auto& thread:producers) thread.join(); consumer.join();
 assert(queue.isEmpty());
 for(int i=0;i<8;++i) assert(queue.put(i,Ignite::TimeOut::kNoWait));
 assert(!queue.put(9,Ignite::TimeOut::kNoWait)); queue.reset(); assert(queue.numVacant()==8);
}
