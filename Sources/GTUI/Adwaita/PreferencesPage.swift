import CGTUI

public class PreferencesPage: NativeWidgetPeer {
  public init(name: String, icon: Icon, description: String) {
    super.init()
    self.nativePtr = gtui_create_preferencespage(
      name.cString,
      icon.string.cString,
      description.cString
    )
  }

  public func add(group: PreferencesGroup) -> PreferencesPage {
    gtui_preferencespage_add(self.nativePtr, group.nativePtr)
    return self
  }
}
