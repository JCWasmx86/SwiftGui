import CGTUI

public class ApplicationWindow: Window {
  var handlers: [String: () -> Void] = [:]
  private var app: Application

  public init(app: Application) {
    self.app = app
    super.init()
    self.nativePtr = gtui_create_application_window(app.nativePtr)
    self.initSignals()
  }
  public required convenience init?(application: Application?) {
    if let application { self.init(app: application) } else { return nil }
  }

  public override func setChild(_ widget: NativeWidgetPeer) {
    gtui_application_window_set_child(self.nativePtr, widget.nativePtr)
  }

  public func addKeyboardShortcut(_ shortcut: String, id: String, handler: @escaping () -> Void) {
    self.handlers[id] = handler
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_application_window_add_keyboard_shortcut(
      self.nativePtr,
      selfAddr,
      app.nativePtr,
      shortcut.cString,
      id.cString,
      "win.\(id)".cString
    )
  }
}

@_cdecl("application_window_on_action_cb") func application_window_on_action_cb(
  ptr: UnsafeMutableRawPointer,
  id: UnsafePointer<CChar>?,
  userData: UnsafeMutableRawPointer
) {
  if let id {
    let window = Unmanaged<ApplicationWindow>.fromOpaque(userData).takeUnretainedValue()
    window.handlers[String(cString: id)]?()
  }
}
