import CGTUI

public class PreferencesWindow: Window {
  public init(parent: Window? = nil) {
    super.init()
    self.nativePtr = gtui_create_preferenceswindow()
    if let parent {
      self.setParent(parent)
    }
  }

  public func add(page: PreferencesPage) {
    gtui_preferenceswindow_add(self.nativePtr, page.nativePtr)
  }

  public func add(toast: Toast) {
    gtui_preferenceswindow_add_toast(self.nativePtr, toast.nativePtr)
  }
}
