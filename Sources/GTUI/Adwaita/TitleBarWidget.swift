import CGTUI
import Foundation

public class TitleBarWidget: NativeWidgetPeer {
  public init(_ title: String, _ subtitle: String) {
    super.init()
    self.nativePtr = gtui_create_title_bar_widget(title.cString, subtitle.cString)
  }
}
