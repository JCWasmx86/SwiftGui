import CGTUI

public class ExpanderRow: PreferencesRow {
  public init(title: String, subtitle: String) {
    super.init()
    self.nativePtr = gtui_create_expanderrow()
    _ = self.title(title)
    _ = self.subtitle(subtitle)
  }

  public func subtitle(_ subtitle: String) -> ExpanderRow {
    gtui_expanderrow_set_subtitle(self.nativePtr, subtitle.cString)
    return self
  }

  public func addPrefix(_ prefix: NativeWidgetPeer) -> ExpanderRow {
    gtui_expanderrow_add_prefix(self.nativePtr, prefix.nativePtr)
    return self
  }

  public func addRow(_ row: NativeWidgetPeer) -> ExpanderRow {
    gtui_expanderrow_add_row(self.nativePtr, row.nativePtr)
    return self
  }
}
