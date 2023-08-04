import CGTUI

public class Box: NativeWidgetPeer {
  private var peers: [NativeWidgetPeer] = []
  public init(horizontal: Bool = true, spacing: Int = 0) {
    super.init()
    self.nativePtr = gtui_create_box(horizontal.cBool, spacing.cInt)
  }

  public func append(_ widget: NativeWidgetPeer) -> Box {
    gtui_box_append(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func prepend(_ widget: NativeWidgetPeer) -> Box {
    gtui_box_prepend(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func removeAll() -> Box {
    for p in self.peers {
      gtui_box_remove(self.nativePtr, p.nativePtr)
    }
    self.peers = []
    return self
  }
}
