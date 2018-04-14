/*************************************************************************
	> File Name: lock.cpp
	> Author: silence
	> Mail: boy.sil.encer.god@gmail.com
	> Created Time: 2018年03月01日 星期四 19时21分23秒
 ************************************************************************/
#include "lock.h"

Lock::Lock(QMutex* pm): mutexptr(pm) {
    mutexptr->lock();
}

Lock::~Lock() {
    mutexptr->unlock();
}
