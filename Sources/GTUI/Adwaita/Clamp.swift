import CGTUI

public class Clamp: NativeWidgetPeer {
  public init(_ widget: NativeWidgetPeer) {
    super.init()
    self.nativePtr = gtui_create_clamp(widget.nativePtr)
  }

  public func maximumSize(_ size: Int) -> Clamp {
    gtui_clamp_set_maximum_size(self.nativePtr, size.cInt)
    return self
  }
}
