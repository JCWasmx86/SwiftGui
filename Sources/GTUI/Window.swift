import CGTUI

public class Window: NativePeer {

  public init(app: Application?) {
    super.init()
    if let addr = app {
      self.nativePtr = gtui_create_window(addr.nativePtr)
    } else {
      self.nativePtr = gtui_create_window(0)
    }
  }

  public func show() {
    gtui_show_window(self.nativePtr)
  }

  public func setChild(_ widget: NativeWidgetPeer) {
    gtui_window_set_child(self.nativePtr, widget.nativePtr)
  }

  public func maximize() {
    gtui_window_maximize(self.nativePtr)
  }
}
