import CGTUI

public class TabButton: NativeWidgetPeer {
  var handlers: [() -> Void] = []

  public init(view: TabView) {
    super.init()
    self.nativePtr = gtui_create_tabbutton(view.nativePtr)
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_tabbutton_init_signals(self.nativePtr, selfAddr)
  }

  public func handler(_ handler: @escaping () -> Void) -> TabButton {
    self.handlers.append(handler)
    return self
  }

  public func onClick() {
    for handler in self.handlers {
      handler()
    }
  }
}

@_cdecl("tabbutton_on_click_cb")
func tabbutton_on_click_cb(ptr: UnsafeMutableRawPointer, userData: UnsafeMutableRawPointer) {
  let button = Unmanaged<TabButton>.fromOpaque(userData).takeUnretainedValue()
  button.onClick()
}
