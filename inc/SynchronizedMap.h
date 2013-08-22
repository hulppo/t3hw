#ifndef SYNCHRONIZEDMAP_H_
#define SYNCHRONIZEDMAP_H_

#include <map>
#include "SynchronizedObject.h"

#include "pthread.h"

/**
   Class SynchronizedMap. This class is used for creating a thread-safe and
   garbage collecting map structure. The target has to be inherited from
   the class SynchronizedObject. This map works only on pointers.

*/
template<class K, class T> class SynchronizedMap;

template<class K, class T>
class SynchronizedMap<K, T*>
{ // Cannot be declared in cpp file, because export command not implemented in g++
 private:
  typedef SynchronizedObject SynchObj;
  typedef std::map<long,T*> RemovedList;
 public:
  
  typedef std::map<K,T*> ActiveList;
  
  /** Constructor.
   */
  SynchronizedMap() {
    mIdCounter = 0;
    //mLock = new MutualExclusion();
    pthread_mutex_init(&mLock, NULL);
  };

  /** Destructor. Frees all pointers and lock.
   */
  ~SynchronizedMap() {
    pthread_mutex_lock(&mLock);
    RemovedList::iterator p = mRemovedObjs.begin();
    for(; p != mRemovedObjs.end(); ++p) {
      T* elem = p->second;
      mRemovedObjs.erase(p);
      delete(elem);
    }
    ActiveList::iterator k = mActiveObjs.begin();
    for(; k != mActiveObjs.end(); ++k) {
      T* elem = k->second;
      mActiveObjs.erase(k);
      delete(elem);
    }
    pthread_mutex_unlock(&mLock);
    //    pthread_mutex_destroy(&mLock);
  };

  /** Inserts the obj under the Key key.
      Synchronized.
      @param key Under which key to insert
      @param obj What to insert, has to be subtype of SynchronizedObject
      @return bool Was the insertion successful
  */
  bool insert(K key, T* obj) {
    pthread_mutex_lock(&mLock);
    bool ok = false;
    if(SynchObj* pSynchObj = dynamic_cast<SynchObj*>(obj)) {
      ActiveList::iterator p = mActiveObjs.find(key);
      if(p == mActiveObjs.end()) { // No such element found
	mActiveObjs[key] = obj;
	pSynchObj->setMapId(mIdCounter++);
	ok = true;
      }
      else {
	// K already existed
      }
    }
    
    pthread_mutex_unlock(&mLock);
    return ok;
  };

  /** Returns the object specified by the key otherwise returns 0.
      Synchronized
      @param key Iden
      @return T Object from map
  */
  T* acquire(K key) {
    pthread_mutex_lock(&mLock);
    T* objToReturn = 0;
    ActiveList::iterator p = mActiveObjs.find(key);
    if(p != mActiveObjs.end()) { // Object found
      objToReturn = p->second;
      SynchObj* pSynchObj = (SynchObj*) objToReturn;
      pSynchObj->incReference();
    }
    pthread_mutex_unlock(&mLock);
    return objToReturn;
  };
  
  /** Tells the map that this object is no longer used.
      Synchronized
      $param obj The object to release
      $return bool Was release successful
  */
  bool release(T* obj) {
    pthread_mutex_lock(&mLock);
    bool ok = false;
    if(obj != 0) {
      SynchObj* pSynchObj = (SynchObj*) obj; //Maybe dynamic cast?
      pSynchObj->decReference();
      ok = true;
      long key = pSynchObj->getMapId();
      RemovedList::iterator p = mRemovedObjs.find(key);
      if(p != mRemovedObjs.end()) {
	if(pSynchObj->getReferenceCount() == 0) {
	  delete(obj);
	}
      }
    }
    pthread_mutex_unlock(&mLock);
    return ok;
  };
  
  /** Removes the obj from the map
      Synchronized
      @param key Key for object to remove
      @return bool Was an object for this key found and was it successful
  */
  bool remove(K key) {
    pthread_mutex_lock(&mLock);
    bool ok = false;
    ActiveList::iterator p = mActiveObjs.find(key);
    if(p != mActiveObjs.end()) {
      T* obj = p->second;
      mActiveObjs.erase(p);
      SynchObj* pSynchObj = (SynchObj*) obj;
      int refCount = pSynchObj->getReferenceCount();
      if(refCount == 0) // Nobody is using this object
	delete(obj);
      else
	mRemovedObjs[pSynchObj->getMapId()] = obj; // MapId is unique
      ok = true;
    }
    pthread_mutex_unlock(&mLock);
    return ok;
  };


  /** Amount of objects stored.
      Not synchronized
      @return int 
  */
  int size() {
    return mActiveObjs.size(); // No need to synchronize?
  };

  /** Gets an iterator pointing to the begin of the map.
      Locks all other methods till returnIterator() gets called.
      getIterator() should only be used to traversing the objects in the map.
      @return ActiveList::iterator 
  */
  ActiveList::iterator getIterator() {
    pthread_mutex_lock(&mLock); //Gets unlocked in returnIterator
    return mActiveObjs.begin();
  };

  /** Tells the SynchronizedMap that you have stopped to use the
      iterator.
  */
  void returnIterator() {
    pthread_mutex_unlock(&mLock);
  };

  /** Gets an iterator to the end of the map.
      @return ActiveList::iterator
  */
  ActiveList::iterator end() {
    return mActiveObjs.end();
  };
  
 private:

  /// List of active objects
  ActiveList mActiveObjs;

  /// List of objects waiting removal
  RemovedList mRemovedObjs;

  /// used to generate map wide unique id
  long mIdCounter;
  
  /// Lock for methods
  pthread_mutex_t mLock;
  //MutualExclusion* mLock;
    
};

#endif //SYNCHRONIZEDMAP_H_
