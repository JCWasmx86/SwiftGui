import CGTUI

public class ActionRow: PreferencesRow {
  public init(title: String, subtitle: String) {
    super.init()
    self.nativePtr = gtui_create_actionrow()
    _ = self.title(title)
    _ = self.subtitle(subtitle)
  }

  public func subtitle(_ subtitle: String) -> ActionRow {
    gtui_actionrow_set_subtitle(self.nativePtr, subtitle.cString)
    return self
  }

  public func addPrefix(_ prefix: NativeWidgetPeer) -> ActionRow {
    gtui_actionrow_add_prefix(self.nativePtr, prefix.nativePtr)
    return self
  }

  public func addSuffix(_ suffix: NativeWidgetPeer) -> ActionRow {
    gtui_actionrow_add_suffix(self.nativePtr, suffix.nativePtr)
    return self
  }
}
