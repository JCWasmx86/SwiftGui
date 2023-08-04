import CGTUI

public class Banner: NativeWidgetPeer {
  var handlers: [() -> Void] = []
  public var isRevealed: Bool { gtui_banner_is_revealed(self.nativePtr) != 0 }

  public init(_ title: String) {
    super.init()
    self.nativePtr = gtui_create_banner(title.cString)
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_banner_init_signals(self.nativePtr, selfAddr)
  }

  public func buttonLabel(_ title: String) -> Banner {
    gtui_banner_set_button(self.nativePtr, title.cString)
    return self
  }

  public func buttonHandler(_ action: @escaping () -> Void) -> Banner {
    handlers.append(action)
    return self
  }

  public func onClick() { for handler in handlers { handler() } }

  public func show() { gtui_banner_set_revealed(self.nativePtr, true.cBool) }

  public func hide() { gtui_banner_set_revealed(self.nativePtr, false.cBool) }
}

@_cdecl("banner_on_click_cb") func banner_on_click_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) {
  let banner = Unmanaged<Banner>.fromOpaque(userData).takeUnretainedValue()
  banner.onClick()
}
