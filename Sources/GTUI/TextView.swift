import CGTUI

public class TextView: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_textview()
  }
}
