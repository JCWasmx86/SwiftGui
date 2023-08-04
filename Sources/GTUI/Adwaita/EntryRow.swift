import CGTUI

public class EntryRow: PreferencesRow {
  public init(title: String) {
    super.init()
    self.nativePtr = gtui_create_entryrow()
    _ = self.title(title)
  }
  override init() { super.init() }

  public func addPrefix(_ prefix: NativeWidgetPeer) -> EntryRow {
    gtui_entryrow_add_prefix(self.nativePtr, prefix.nativePtr)
    return self
  }

  public func addSuffix(_ suffix: NativeWidgetPeer) -> EntryRow {
    gtui_entryrow_add_suffix(self.nativePtr, suffix.nativePtr)
    return self
  }

  public func contents() -> String {
    let contents = gtui_editable_contents(self.nativePtr)
    return String(cString: contents!)
  }
}
