import CGTUI

public class PreferencesRow: NativeWidgetPeer {
  public func title(_ title: String) -> PreferencesRow {
    gtui_preferencesrow_set_title(self.nativePtr, title.cString)
    return self
  }
}
