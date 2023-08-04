import CGTUI

public class MessageDialog: NativePeer {
  var handlers: [String: () -> Void] = [:]

  public init(parent: Window? = nil, heading: String? = nil, body: String? = nil) {
    super.init()
    self.nativePtr = gtui_create_messagedialog(
      parent?.nativePtr ?? 0,
      heading?.cString,
      body?.cString
    )
    let selfAddr = unsafeBitCast(self, to: UInt64.self)
    gtui_messagedialog_init_signals(self.nativePtr, selfAddr)
  }

  public enum ResponseAppearance: Int {
    case `default`
    case suggested
    case destructive
  }

  public enum ResponseType: Int {
    case `default`
    case closeResponse
    case defaultResponse
  }

  public func response(
    id: String,
    label: String,
    appearance: ResponseAppearance = .default,
    enabled: Bool = true,
    type: ResponseType = .default,
    handler: @escaping () -> Void
  ) -> MessageDialog {
    gtui_messagedialog_add_response(
      self.nativePtr,
      id.cString,
      label.cString,
      appearance.rawValue.cInt,
      enabled.cBool,
      type.rawValue.cInt
    )
    handlers[id] = handler
    return self
  }

  public func child(_ child: NativeWidgetPeer) -> MessageDialog {
    gtui_messagedialog_set_extra_child(self.nativePtr, child.nativePtr)
    return self
  }

  public func show() { gtui_messagedialog_present(self.nativePtr) }

  public func close() { gtui_window_close(self.nativePtr) }

  public func onClick(_ response: String) { handlers[response]?() }
}

@_cdecl("messagedialog_on_click_cb") func messagedialog_on_click_cb(
  ptr: UnsafeMutableRawPointer,
  response: UnsafePointer<CChar>?,
  userData: UnsafeMutableRawPointer
) {
  if let response {
    let messagedialog = Unmanaged<MessageDialog>.fromOpaque(userData).takeUnretainedValue()
    messagedialog.onClick(.init(cString: response))
  }
}
