import Foundation

extension String {
  var cString: UnsafePointer<CChar>? { .init(NSString(string: self).utf8String) }

  public func ctrl() -> String { "<Ctrl>\(self)" }
  public func shift() -> String { "<Shift>\(self)" }
  public func alt() -> String { "<Alt>\(self)" }
  public func meta() -> String { "<Meta>\(self)" }
  public func `super`() -> String { "<Super>\(self)" }
  public func hyper() -> String { "<Hyper>\(self)" }
}
