import CGTUI

public class TabOverview: NativeWidgetPeer {
  var handler: (() -> UInt64)?

  public var overviewPresented: Bool { gtui_taboverview_get_open(self.nativePtr) == 1 }

  public override init() {
    super.init()
    self.nativePtr = gtui_create_taboverview()
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_taboverview_init_signals(self.nativePtr, selfAddr)
  }

  public func add(_ child: NativeWidgetPeer, view: TabView) -> TabOverview {
    gtui_taboverview_add(self.nativePtr, child.nativePtr, view.nativePtr)
    return self
  }

  public func createTabHandler(_ handler: @escaping () -> UInt64) -> TabOverview {
    self.handler = handler
    gtui_taboverview_show_create_tab(self.nativePtr)
    return self
  }

  public func showOverview() { gtui_taboverview_set_open(self.nativePtr, true.cBool) }

  public func hideOverview() { gtui_taboverview_set_open(self.nativePtr, false.cBool) }

  public func onCreateTab() -> UInt64 { handler?() ?? 0 }
}

@_cdecl("taboverview_on_create_tab_cb") func taboverview_on_create_tab_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) -> UInt64 {
  let overview = Unmanaged<TabOverview>.fromOpaque(userData).takeUnretainedValue()
  return overview.onCreateTab()
}
