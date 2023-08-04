import CGTUI

public class PasswordEntryRow: EntryRow {
  public override init(title: String) {
    super.init(title: title)
    self.nativePtr = gtui_create_passwordentryrow()
    _ = self.title(title)
  }
}
