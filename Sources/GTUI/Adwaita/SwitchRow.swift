import CGTUI

public class SwitchRow: ActionRow {
  public override init(title: String, subtitle: String) {
    super.init()
    self.nativePtr = gtui_create_switchrow()
    _ = self.title(title)
    _ = self.subtitle(subtitle)
  }

  override init() { super.init() }

  public func getActive() -> Bool { gtui_switchrow_get_active(self.nativePtr) != 0 }

  public func setActive(_ active: Bool) { gtui_switchrow_set_active(self.nativePtr, active.cBool) }
}
