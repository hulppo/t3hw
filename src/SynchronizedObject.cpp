#include "SynchronizedObject.h"

SynchronizedObject::SynchronizedObject()
{
  mId = 0;
  mRefCount = 0;
}

void
SynchronizedObject::setMapId(long id)
{
  mId = id;
}

long
SynchronizedObject::getMapId()
{
  return mId;
}

void
SynchronizedObject::incReference()
{
  ++mRefCount;
}

void
SynchronizedObject::decReference()
{
  --mRefCount;
}

int
SynchronizedObject::getReferenceCount()
{
  return mRefCount;
}
