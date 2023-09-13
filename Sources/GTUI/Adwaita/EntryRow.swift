import CGTUI

public class EntryRow: PreferencesRow {
  var handlers: [() -> Void] = []

  public init(title: String) {
    super.init()
    self.nativePtr = gtui_create_entryrow()
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_entryrow_init_signals(self.nativePtr, selfAddr)
    _ = self.title(title)
  }
  override init() { super.init() }

  public func addPrefix(_ prefix: NativeWidgetPeer) -> EntryRow {
    gtui_entryrow_add_prefix(self.nativePtr, prefix.nativePtr)
    return self
  }

  public func addSuffix(_ suffix: NativeWidgetPeer) -> EntryRow {
    gtui_entryrow_add_suffix(self.nativePtr, suffix.nativePtr)
    return self
  }

  public func submitHandler(_ handler: @escaping () -> Void) -> EntryRow {
    self.handlers.append(handler)
    gtui_entryrow_set_show_apply_button(self.nativePtr, true.cBool)
    return self
  }

  public func contents() -> String {
    let contents = gtui_editable_contents(self.nativePtr)
    return String(cString: contents!)
  }

  public func setContents(_ text: String) {
    gtui_editable_set_contents(self.nativePtr, text.cString)
  }

  public func onSubmit() { for handler in handlers { handler() } }
}

@_cdecl("entryrow_on_submit_cb") func entryrow_on_submit_cb(
  ptr: UnsafeMutableRawPointer,
  userData: UnsafeMutableRawPointer
) {
  let entryrow = Unmanaged<EntryRow>.fromOpaque(userData).takeUnretainedValue()
  entryrow.onSubmit()
}
