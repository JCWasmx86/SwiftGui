import CGTUI

public class ToolbarView: NativeWidgetPeer {
  public init(_ child: NativeWidgetPeer) {
    super.init()
    self.nativePtr = gtui_create_toolbarview(child.nativePtr)
  }

  public func addBottomBar(_ child: NativeWidgetPeer) -> ToolbarView {
    gtui_toolbarview_add_bottom_bar(self.nativePtr, child.nativePtr)
    return self
  }

  public func addTopBar(_ child: NativeWidgetPeer) -> ToolbarView {
    gtui_toolbarview_add_top_bar(self.nativePtr, child.nativePtr)
    return self
  }

  public func setRevealBottomBar(_ revealed: Bool) {
    gtui_toolbarview_set_reveal_bottom_bar(self.nativePtr, revealed.cBool)
  }

  public func setRevealTopBar(_ revealed: Bool) {
    gtui_toolbarview_set_reveal_top_bar(self.nativePtr, revealed.cBool)
  }

  public func bottomBarStyle(_ style: ToolbarStyle) -> ToolbarView {
    gtui_toolbarview_set_top_bar_style(self.nativePtr, style.rawValue.cInt)
    return self
  }

  public func topBarStyle(_ style: ToolbarStyle) -> ToolbarView {
    gtui_toolbarview_set_top_bar_style(self.nativePtr, style.rawValue.cInt)
    return self
  }
}
