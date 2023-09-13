import CGTUI

public class ButtonContent: NativeWidgetPeer {
  public init(icon: Icon, label: String? = nil) {
    super.init()
    self.nativePtr = gtui_create_buttoncontent()
    if let label { setLabel(label) }
    setIcon(icon)
  }

  public func setLabel(_ label: String) {
    gtui_buttoncontent_set_label(self.nativePtr, label.cString)
  }

  public func setIcon(_ icon: Icon) {
    gtui_buttoncontent_set_icon(self.nativePtr, icon.string.cString)
  }
}
