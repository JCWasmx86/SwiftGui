import CGTUI
import Foundation

public class HeaderBar: NativeWidgetPeer, Container {
  private var peers: [NativeWidgetPeer] = []

  public override init() {
    super.init()
    self.nativePtr = gtui_create_headerbar()
  }

  public func titleWidget(_ widget: NativeWidgetPeer) -> HeaderBar {
    gtui_headerbar_set_title_widget(self.nativePtr, widget.nativePtr)
    return self
  }

  public func append(_ widget: NativeWidgetPeer) -> Self { self.packEnd(widget) }
  public func prepend(_ widget: NativeWidgetPeer) -> Self { self.packStart(widget) }

  public func removeAll() -> Self { removeWidgets(self.peers) }

  public func removeWidgets(_ widgets: [NativeWidgetPeer]) -> Self {
    for p in widgets {
      gtui_headerbar_remove(self.nativePtr, p.nativePtr)
      self.peers = self.peers.filter { $0.nativePtr != p.nativePtr }
    }
    return self
  }

  public func getContent() -> [NativeWidgetPeer] { self.peers }

  public func packStart(_ widget: NativeWidgetPeer) -> Self {
    gtui_headerbar_pack_start(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func packEnd(_ widget: NativeWidgetPeer) -> Self {
    gtui_headerbar_pack_end(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func showTitleButtons(_ enabled: Bool) -> HeaderBar {
    gtui_headerbar_set_show_title_buttons(self.nativePtr, enabled.cBool)
    return self
  }
}
