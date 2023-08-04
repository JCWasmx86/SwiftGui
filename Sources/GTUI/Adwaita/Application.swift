import CGTUI
import Foundation

open class Application: NativePeer {
  public init(name: String) {
    super.init()
    self.nativePtr = gtui_init_application(name.cString)
  }

  open func onActivate() {
  }

  public func run() {
    gtui_run_application(self.nativePtr, unsafeBitCast(self, to: UInt64.self))
  }
  
  public func quit() {
    gtui_quit_application(self.nativePtr)
  }
    
}

@_cdecl("application_on_activate_cb")
func application_on_activate_cb(ptr: UnsafeMutableRawPointer, userData: UnsafeMutableRawPointer) {
  let app = Unmanaged<Application>.fromOpaque(userData).takeUnretainedValue()
  app.onActivate()
}
