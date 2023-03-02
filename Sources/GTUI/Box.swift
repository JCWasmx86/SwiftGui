import CGTUI

public class Box: NativeWidgetPeer {
  public init(horizontal: Bool = true, spacing: Int = 0) {
    super.init()
    self.nativePtr = gtui_create_box(horizontal ? 1 : 0, Int32(spacing))
  }

  public func append(_ widget: NativeWidgetPeer) -> Box {
    gtui_box_append(self.nativePtr, widget.nativePtr)
    return self
  }

  public func prepend(_ widget: NativeWidgetPeer) -> Box {
    gtui_box_prepend(self.nativePtr, widget.nativePtr)
    return self
  }

  public func show() {
  }
}
