import Foundation

extension String {
  var cString: UnsafePointer<CChar>? {
    .init(self.utf8String)
  }
}
