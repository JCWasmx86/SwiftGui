import CGTUI

public class TabView: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_tabview()
  }

  public func append(title: String, _ widget: NativeWidgetPeer, getPage: (UInt64) -> Void = { _ in }) -> TabView {
    let pagePtr = gtui_tabview_append(self.nativePtr, widget.nativePtr, title.cString)
    getPage(pagePtr)
    return self
  }

  public func prepend(title: String, _ widget: NativeWidgetPeer, getPage: (UInt64) -> Void = { _ in }) -> TabView {
    let pagePtr = gtui_tabview_prepend(self.nativePtr, widget.nativePtr, title.cString)
    getPage(pagePtr)
    return self
  }
}
