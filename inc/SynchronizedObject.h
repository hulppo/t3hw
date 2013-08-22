#ifndef SYNCHRONIZEDOBJECT_H_
#define SYNCHRONIZEDOBJECT_H_

/** Class SynchronizedObject.
    A class which is going to be used together with the synchronized
    map has to inherit this class.
*/
class SynchronizedObject {
 public:
  /** Constructor.
   */
  SynchronizedObject();

  /** Setter. Sets the id.
      The mapId has to be unique per synchronized map.
      It is used in garbage collecting.
      @param long
  */
  void setMapId(long id);

  /** Getter.
      @return long
  */
  long getMapId();

  /** Increaser. Increases one to the reference count.
   */
  void incReference();

  /** Decreaser. Decreases one from reference.
   */
  void decReference();

  /** ReferenceCount. Returns the number of references for this
      object.
      @return int
   */
  int getReferenceCount();

 private:
  /// unique id
  long mId;
  /// number of references
  int mRefCount;
};




#endif //  SYNCHRONIZEDOBJECT_H_
