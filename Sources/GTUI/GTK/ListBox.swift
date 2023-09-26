import CGTUI

public class ListBox: NativeWidgetPeer, InsertableContainer {
  private var peers: [NativeWidgetPeer] = []
  var handlers: [() -> Void] = []

  public override init() {
    super.init()
    self.nativePtr = gtui_create_listbox()
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_listbox_init_signals(self.nativePtr, selfAddr)
  }

  class Row: NativeWidgetPeer {
    public init(_ nativePtr: UInt64) {
      super.init()
      self.nativePtr = nativePtr
    }

    func getChild() -> UInt64? {
      if self.nativePtr != 0 { return gtk_listboxrow_get_child(self.nativePtr) } else { return nil }
    }
  }

  public func insert(_ widget: NativeWidgetPeer, at index: Int) -> Self {
    if index == 0 {
      _ = self.prepend(widget)
    } else if index >= peers.count {
      _ = self.append(widget)
    } else {
      gtui_listbox_insert(self.nativePtr, widget.nativePtr, index.cInt)
      self.peers.insert(widget, at: index)
    }
    return self
  }

  public func append(_ widget: NativeWidgetPeer) -> Self {
    gtui_listbox_append(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func prepend(_ widget: NativeWidgetPeer) -> Self {
    gtui_listbox_prepend(self.nativePtr, widget.nativePtr)
    self.peers.insert(widget, at: 0)
    return self
  }

  public func removeAll() -> Self { removeWidgets(self.peers) }

  public func removeWidgets(_ widgets: [NativeWidgetPeer]) -> Self {
    for p in widgets {
      gtui_listbox_remove(self.nativePtr, p.nativePtr)
      self.peers = self.peers.filter { $0.nativePtr != p.nativePtr }
    }
    return self
  }

  public func getContent() -> [NativeWidgetPeer] { return peers }

  public func selectRow(at index: Int) { gtui_listbox_select_row(self.nativePtr, index.cInt) }

  public func getSelectedRow() -> Int? {
    let ptr = gtui_listbox_get_selected_row(self.nativePtr)
    return peers.firstIndex { $0.nativePtr == Row(ptr).getChild() }
  }

  public func sidebarStyle() -> Self {
    _ = self.addStyle("navigation-sidebar")
    return self
  }

  public func handler(_ handler: @escaping () -> Void) -> Self {
    self.handlers.append(handler)
    return self
  }

  func onSelectRow() { for handler in handlers { handler() } }
}

@_cdecl("listbox_on_select_row_cb") func listbox_on_select_row_cb(
  ptr: UnsafeMutableRawPointer,
  rowPtr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) {
  let box = Unmanaged<ListBox>.fromOpaque(userData).takeUnretainedValue()
  box.onSelectRow()
}
