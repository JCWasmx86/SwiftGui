import CGTUI

public class NavigationSplitView: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_navigationsplitview()
  }

  public func sidebar(_ view: NativeWidgetPeer, title: String) -> NavigationSplitView {
    gtui_navigationsplitview_set_sidebar(self.nativePtr, view.nativePtr, title.cString)
    return self
  }

  public func content(_ view: NativeWidgetPeer, title: String) -> NavigationSplitView {
    gtui_navigationsplitview_set_content(self.nativePtr, view.nativePtr, title.cString)
    return self
  }
}
