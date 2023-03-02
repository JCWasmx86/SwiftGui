import CGTUI
import Foundation

open class Application: NativePeer {
  public init(name: NSString) {
    super.init()
    self.nativePtr = gtui_init_application(UnsafePointer<CChar>(name.utf8String))
  }

  open func onActivate() {
  }

  public func run() {
    gtui_run_application(self.nativePtr, unsafeBitCast(self, to: UInt64.self))
  }
}

@_cdecl("application_on_activate_cb")
func application_on_activate_cb(ptr: UnsafeMutableRawPointer, userData: UnsafeMutableRawPointer) {
  let app = Unmanaged<Application>.fromOpaque(userData).takeUnretainedValue()
  app.onActivate()
}
