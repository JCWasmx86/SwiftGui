import CGTUI

public class PasswordEntryRow: EntryRow {
  public override init(title: String) {
    super.init()
    self.nativePtr = gtui_create_passwordentryrow()
    _ = self.title(title)
  }
}
