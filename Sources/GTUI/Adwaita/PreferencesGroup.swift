import CGTUI

public class PreferencesGroup: NativeWidgetPeer {
  public init(name: String, description: String) {
    super.init()
    self.nativePtr = gtui_create_preferencesgroup(name.cString, description.cString)
  }

  public func headerSuffix(_ suffix: NativeWidgetPeer) -> PreferencesGroup {
    gtui_preferencesgroup_header_suffix(self.nativePtr, suffix.nativePtr)
    return self
  }

  public func add(_ widget: NativeWidgetPeer) -> PreferencesGroup {
    gtui_preferencesgroup_add(self.nativePtr, widget.nativePtr)
    return self
  }
}
