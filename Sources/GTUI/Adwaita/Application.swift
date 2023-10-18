import CGTUI
import Foundation

open class Application: NativePeer {
  var handlers: [String: () -> Void] = [:]

  public init(name: String) {
    super.init()
    self.nativePtr = gtui_init_application(name.cString)
  }

  open func onActivate() {}

  public func addKeyboardShortcut(_ shortcut: String, id: String, handler: @escaping () -> Void) {
    self.handlers[id] = handler
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_application_add_keyboard_shortcut(
      self.nativePtr,
      selfAddr,
      shortcut.cString,
      id.cString,
      "app.\(id)".cString
    )
  }

  public func run() { gtui_run_application(self.nativePtr, unsafeBitCast(self, to: UInt64.self)) }
  public func quit() { gtui_quit_application(self.nativePtr) }
}

@_cdecl("application_on_activate_cb") func application_on_activate_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) {
  let app = Unmanaged<Application>.fromOpaque(userData).takeUnretainedValue()
  app.onActivate()
}

@_cdecl("application_on_action_cb") func application_on_action_cb(
  ptr: UnsafeMutableRawPointer,
  id: UnsafePointer<CChar>?,
  userData: UnsafeMutableRawPointer
) {
  if let id {
    let app = Unmanaged<Application>.fromOpaque(userData).takeUnretainedValue()
    app.handlers[String(cString: id)]?()
  }
}
