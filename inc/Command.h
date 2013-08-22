#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>

/** Class Command.
    This class is used for bringing the different
    commands together.
*/
class Command {
 public:
  
  /** Constructor
      Constructs the Command object. This constructor should be
      called from every class inheriting this.
      @param s type std::string. Name of the sender of the command
   */
  Command(std::string s) : sender(s) { }; //Sets the const sender

  /// Username of the command sender
  const std::string sender;
};


#endif //  COMMAND_H_
