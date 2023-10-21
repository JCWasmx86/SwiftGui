import CGTUI

public class CheckButton: NativeWidgetPeer {
  var handlers: [() -> Void] = []

  public init(_ label: String) {
    super.init()
    self.nativePtr = gtui_create_checkbutton(label.cString)
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_checkbutton_init_signals(self.nativePtr, selfAddr)
  }

  public func handler(_ handler: @escaping () -> Void) -> CheckButton {
    self.handlers.append(handler)
    return self
  }

  public func setLabel(_ text: String) { gtui_checkbutton_set_label(self.nativePtr, text.cString) }

  public func setActive(_ active: Bool) {
    gtui_checkbutton_set_active(self.nativePtr, active.cBool)
  }

  public func setInconsistent(_ inconsistent: Bool) {
    gtui_checkbutton_set_inconsistent(self.nativePtr, inconsistent.cBool)
  }

  public func onClick() { for handler in self.handlers { handler() } }
}

@_cdecl("checkbutton_on_toggle_cb") func checkbutton_on_toggle_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) {
  let button = Unmanaged<CheckButton>.fromOpaque(userData).takeUnretainedValue()
  button.onClick()
}
