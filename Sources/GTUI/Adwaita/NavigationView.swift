import CGTUI

public class NavigationView: NativeWidgetPeer {
  private var peers: [UInt64] = []

  public override init() {
    super.init()
    self.nativePtr = gtui_create_navigationview()
  }

  public func add(_ widget: NativeWidgetPeer, title: String) -> NavigationView {
    peers.append(gtui_navigationview_add(self.nativePtr, widget.nativePtr, title.cString))
    return self
  }

  public func pop() -> NavigationView { removeWidgets([peers.last ?? 0], pop: true) }

  public func removeAll() -> NavigationView { removeWidgets(self.peers) }

  public func removeWidgets(_ widgets: [UInt64], pop: Bool = false) -> NavigationView {
    for p in widgets {
      gtui_navigationview_remove(self.nativePtr, p, pop.cBool)
      self.peers = self.peers.filter { $0 != p }
    }
    return self
  }

  public func getContent() -> [UInt64] { return peers }
}
