import Foundation

extension Array where Element == String {
  var cArray: UnsafeMutablePointer<UnsafePointer<CChar>?> {
    var cStringPointers: [UnsafePointer<CChar>?] = []
    for string in self {
      let cString = strdup(string)
      cStringPointers.append(cString)
    }
    var result: UnsafeMutablePointer<UnsafePointer<CChar>?>?
    cStringPointers.append(nil)
    cStringPointers.withUnsafeMutableBytes { bufferPtr in
      result = bufferPtr.bindMemory(to: UnsafePointer<CChar>?.self).baseAddress
    }
    return result!
  }
}
