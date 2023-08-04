import CGTUI

public class Toast: NativePeer {
  var handlers: [() -> Void] = []

  public init(_ title: String) {
    super.init()
    self.nativePtr = gtui_create_toast(title.cString)
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_toast_init_signals(self.nativePtr, selfAddr)
  }

  public func buttonLabel(_ title: String) -> Toast {
    gtui_toast_set_button(self.nativePtr, title.cString)
    return self
  }

  public func buttonHandler(_ action: @escaping () -> Void) -> Toast {
    handlers.append(action)
    return self
  }

  public func dismiss() {
    gtui_toast_dismiss(self.nativePtr)
  }

  public func onClick() {
    for handler in handlers {
      handler()
    }
  }
}

@_cdecl("toast_on_click_cb")
func toast_on_click_cb(ptr: UnsafeMutableRawPointer, userData: UnsafeMutableRawPointer) {
  let toast = Unmanaged<Toast>.fromOpaque(userData).takeUnretainedValue()
  toast.onClick()
}
