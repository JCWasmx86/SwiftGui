import CGTUI

public class ComboRow: ActionRow {
  private let stringListPtr: UInt64

  public override init(title: String, subtitle: String) {
    self.stringListPtr = gtui_create_stringlist()
    super.init(title: title, subtitle: subtitle)
    self.nativePtr = gtui_create_comborow(self.stringListPtr)
    _ = self.title(title)
    _ = self.subtitle(subtitle)
  }

  public func append(_ string: String) -> ComboRow {
    gtui_stringlist_append(self.stringListPtr, string.cString)
    return self
  }

  public func selected() -> String {
    let str = gtui_stringlist_get_selected(self.nativePtr, self.stringListPtr)
    return String(cString: str!)
  }
}
