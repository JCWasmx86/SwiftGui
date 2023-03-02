import CGTUI

open class NativeWidgetPeer: NativePeer {
  public func setHexpand(_ enabled: Bool) {
    gtui_set_hexpand(self.nativePtr, enabled ? 1 : 0)
  }

  public func setVexpand(_ enabled: Bool) {
    gtui_set_vexpand(self.nativePtr, enabled ? 1 : 0)
  }
}
