import CGTUI
import Foundation

public class HeaderBar: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_headerbar()
  }

  public func titleWidget(_ widget: NativeWidgetPeer) -> HeaderBar {
    gtui_headerbar_set_title_widget(self.nativePtr, widget.nativePtr)
    return self
  }

  public func packStart(_ widget: NativeWidgetPeer) -> HeaderBar {
    gtui_headerbar_pack_start(self.nativePtr, widget.nativePtr)
    return self
  }

  public func packEnd(_ widget: NativeWidgetPeer) -> HeaderBar {
    gtui_headerbar_pack_end(self.nativePtr, widget.nativePtr)
    return self
  }

  public func showTitleButtons(_ enabled: Bool) -> HeaderBar {
    gtui_headerbar_set_show_title_buttons(self.nativePtr, enabled.cBool)
    return self
  }
}
