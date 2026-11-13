#pragma once
#include <cstdint>
#include <cstddef>
namespace sync {
enum class Status { Ok, Invalid, Full, Duplicate, Missing, Conflict };
struct Record {uint32_t id=0,version=0;int32_t value=0;bool pending=false;};
template<size_t Capacity> class Queue {
 public:
 static_assert(Capacity>0,"Capacity must be positive");
 Status enqueue(uint32_t id,uint32_t version,int32_t value){
  if(!id||!version)return Status::Invalid;
  for(size_t i=0;i<count_;++i)if(items_[i].id==id){
   if(version<items_[i].version)return Status::Conflict;
   if(version==items_[i].version)return Status::Duplicate;
   items_[i]={id,version,value,true};return Status::Ok;
  }
  if(count_==Capacity)return Status::Full;
  items_[count_++]={id,version,value,true};return Status::Ok;
 }
 Status acknowledge(uint32_t id,uint32_t version){
  if(!id||!version)return Status::Invalid;
  for(size_t i=0;i<count_;++i)if(items_[i].id==id){
   if(items_[i].version!=version)return Status::Conflict;
   if(!items_[i].pending)return Status::Duplicate;
   items_[i].pending=false;return Status::Ok;
  }
  return Status::Missing;
 }
 const Record* next()const{for(size_t i=0;i<count_;++i)if(items_[i].pending)return &items_[i];return nullptr;}
 size_t size()const{return count_;}
 size_t pending()const{size_t n=0;for(size_t i=0;i<count_;++i)if(items_[i].pending)++n;return n;}
 void clearAcknowledged(){
  size_t out=0;for(size_t i=0;i<count_;++i)if(items_[i].pending)items_[out++]=items_[i];count_=out;
 }
 private: Record items_[Capacity]={};size_t count_=0;
};
}
