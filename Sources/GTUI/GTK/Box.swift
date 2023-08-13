import CGTUI

public class Box: NativeWidgetPeer, Container {
  private var peers: [NativeWidgetPeer] = []

  public init(horizontal: Bool = true, spacing: Int = 0) {
    super.init()
    self.nativePtr = gtui_create_box(horizontal.cBool, spacing.cInt)
  }

  public func append(_ widget: NativeWidgetPeer) -> Self {
    gtui_box_append(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func prepend(_ widget: NativeWidgetPeer) -> Self {
    gtui_box_prepend(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func removeAll() -> Self { removeWidgets(self.peers) }

  public func removeWidgets(_ widgets: [NativeWidgetPeer]) -> Self {
    for p in widgets {
      gtui_box_remove(self.nativePtr, p.nativePtr)
      self.peers = self.peers.filter { $0.nativePtr != p.nativePtr }
    }
    return self
  }

  public func getContent() -> [NativeWidgetPeer] { return peers }
}
