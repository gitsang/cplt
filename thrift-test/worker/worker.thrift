# worker.thrift
# Dean Chen (csfreebird@gmail.com)
#

/**
 * Thrift files can namespace, package, or prefix their output in various
 * target languages.
 */
namespace cpp freebird

/**
 * Defining a removed class named WorkerManager
 */
service WorkerManager {

  /**
   * client calls ping method to make sure service process is active or dead
   */
   void ping()

}
