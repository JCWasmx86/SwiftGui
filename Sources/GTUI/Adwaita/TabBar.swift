import CGTUI

public class TabBar: NativeWidgetPeer {
  public init(view: TabView) {
    super.init()
    self.nativePtr = gtui_create_tabbar(view.nativePtr)
  }
}
