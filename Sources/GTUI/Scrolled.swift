import CGTUI

public class Scrolled: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_scrolled()
  }

  public func setChild(_ widget: NativeWidgetPeer) -> Scrolled {
    gtui_scrolled_set_child(self.nativePtr, widget.nativePtr)
    return self
  }
}
