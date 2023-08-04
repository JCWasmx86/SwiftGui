import CGTUI

public class StatusPage: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_statuspage()
  }

  public func title(_ title: String) -> StatusPage {
    gtui_statuspage_set_title(self.nativePtr, title.cString)
    return self
  }

  public func description(_ description: String) -> StatusPage {
    gtui_statuspage_set_description(self.nativePtr, description.cString)
    return self
  }

  public func icon(_ icon: Icon) -> StatusPage {
    gtui_statuspage_set_icon_name(self.nativePtr, icon.string.cString)
    return self
  }

  public func child(_ widget: NativeWidgetPeer) -> StatusPage {
    gtui_statuspage_set_child(self.nativePtr, widget.nativePtr)
    return self
  }

}
