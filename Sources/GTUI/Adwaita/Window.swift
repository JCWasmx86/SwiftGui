import CGTUI

public class Window: NativePeer {

  public var isMaximized: Bool { gtui_window_is_maximized(self.nativePtr) != 0 }
  private var closeHandler: (() -> Bool)?

  public init(app: Application?) {
    super.init()
    if let addr = app {
      self.nativePtr = gtui_create_window(addr.nativePtr)
    } else {
      self.nativePtr = gtui_create_window(0)
    }
    self.initSignals()
  }

  override init() { super.init() }

  public func show() { gtui_show_window(self.nativePtr) }

  public func setChild(_ widget: NativeWidgetPeer) {
    gtui_window_set_child(self.nativePtr, widget.nativePtr)
  }

  public func setParent(_ window: Window) {
    gtui_window_set_transient_for(self.nativePtr, window.nativePtr)
  }

  public func maximize() { gtui_window_maximize(self.nativePtr) }

  public func unmaximize() { gtui_window_unmaximize(self.nativePtr) }

  public func fullscreen() { gtui_window_enter_fullscreen(self.nativePtr) }

  public func unfullscreen() { gtui_window_leave_fullscreen(self.nativePtr) }

  public func minimize() { gtui_window_minimize(self.nativePtr) }

  public func close() { gtui_window_close(self.nativePtr) }

  public func setDefaultSize(width: Int?, height: Int?) {
    gtui_window_set_default_size(self.nativePtr, width?.cInt ?? -1, height?.cInt ?? -1)
  }

  public func setResizability(_ resizable: Bool) {
    gtui_window_set_resizability(self.nativePtr, resizable.cBool)
  }

  public func setDeletability(_ deletable: Bool) {
    gtui_window_set_deletability(self.nativePtr, deletable.cBool)
  }

  public func observeHide(_ run: @escaping () -> Bool) { self.closeHandler = run }

  func onHide() -> Bool { self.closeHandler?() ?? false }

  func initSignals() {
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_window_init_signals(self.nativePtr, selfAddr)
  }
}

@_cdecl("window_close_cb") func window_close_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) -> Int32 {
  let window = Unmanaged<Window>.fromOpaque(userData).takeUnretainedValue()
  return window.onHide().cBool
}
