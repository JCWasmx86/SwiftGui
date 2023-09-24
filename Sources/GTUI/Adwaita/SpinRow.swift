import CGTUI

public class SpinRow: ActionRow {
  public init(title: String, subtitle: String, min: Double, max: Double, step: Double) {
    super.init()
    self.nativePtr = gtui_create_spinrow(min, max, step)
    _ = self.title(title)
    _ = self.subtitle(subtitle)
  }

  override init() { super.init() }

  public func configuration(min: Double, max: Double, step: Double) -> SpinRow {
    gtui_spinrow_set_configuration(self.nativePtr, min, max, step)
    return self
  }

  public func getValue() -> Double { gtui_spinrow_get_value(self.nativePtr) }

  public func setValue(_ value: Double) { gtui_spinrow_set_value(self.nativePtr, value) }
}
