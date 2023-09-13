import Foundation

extension String { var cString: UnsafePointer<CChar>? { .init(NSString(string: self).utf8String) } }
