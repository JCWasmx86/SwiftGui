import CGTUI

public class ButtonContent: NativeWidgetPeer {
  public init(icon: Icon, label: String? = nil) {
    super.init()
    self.nativePtr = gtui_create_buttoncontent()
    if let label {
      gtui_buttoncontent_set_label(self.nativePtr, label.cString)
    }
    gtui_buttoncontent_set_icon(self.nativePtr, icon.string.cString)
  }
}
