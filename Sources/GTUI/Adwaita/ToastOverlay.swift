import CGTUI

public class ToastOverlay: NativeWidgetPeer {
  public init(_ child: NativeWidgetPeer) {
    super.init()
    self.nativePtr = gtui_create_toastoverlay(child.nativePtr)
  }

  public func addToast(_ toast: Toast) {
    gtui_toastoverlay_add_toast(self.nativePtr, toast.nativePtr)
  }
}
