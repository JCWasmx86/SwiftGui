import CGTUI

public class Stack: NativeWidgetPeer {
  private var peers: [(NativeWidgetPeer, Transition)] = []
  private var activePeer: (NativeWidgetPeer, Transition)? {
    get { peers.first }
    set {
      if let newValue {
        self.peers = self.peers.filter { $0.0.nativePtr != newValue.0.nativePtr }
        self.peers.insert(newValue, at: 0)
      }
    }
  }

  public override init() {
    super.init()
    self.nativePtr = gtui_create_stack()
  }

  public func append(_ child: NativeWidgetPeer, transition: Transition = .none) -> Stack {
    gtui_stack_add_child(self.nativePtr, child.nativePtr)
    peers.append((child, transition))
    return self
  }

  public func setVisible(_ child: NativeWidgetPeer) {
    if let peer = peers.first(where: { $0.0.nativePtr == child.nativePtr }) {
      gtui_stack_set_visible_child(self.nativePtr, child.nativePtr, peer.1.rawValue.cInt)
      self.activePeer = peer
    }
  }

  public func removeAll() -> Self { removeWidgets(self.peers.map { $0.0 }) }

  public func removeWidgets(_ widgets: [NativeWidgetPeer]) -> Self {
    for p in widgets {
      gtui_stack_remove(self.nativePtr, p.nativePtr)
      self.peers = self.peers.filter { $0.0.nativePtr != p.nativePtr }
    }
    return self
  }

  public func getContent() -> [(NativeWidgetPeer, Transition?)] { return peers }

  public func getVisible() -> (NativeWidgetPeer, Transition)? { return activePeer }
}
