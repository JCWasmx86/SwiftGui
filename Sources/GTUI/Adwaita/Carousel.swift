import CGTUI

public class Carousel: NativeWidgetPeer, Container {
  private var peers: [NativeWidgetPeer] = []

  public override init() {
    super.init()
    self.nativePtr = gtui_create_carousel()
  }

  public func append(_ widget: NativeWidgetPeer) -> Self {
    gtui_carousel_append(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func prepend(_ widget: NativeWidgetPeer) -> Self {
    gtui_carousel_prepend(self.nativePtr, widget.nativePtr)
    self.peers.append(widget)
    return self
  }

  public func removeWidgets(_ widgets: [NativeWidgetPeer]) -> Self {
    for widget in widgets {
      gtui_carousel_remove(self.nativePtr, widget.nativePtr)
      self.peers = self.peers.filter { $0.nativePtr != widget.nativePtr }
    }
    return self
  }

  public func removeAll() -> Self { removeWidgets(self.peers) }

  public func getContent() -> [NativeWidgetPeer] { self.peers }

  public func addIndicatorDots(top: Bool = false) -> Box {
    let box = Box(horizontal: false)
    let dots = CarouselIndicatorDots(carousel: self)
    if top { _ = box.append(dots).append(self) } else { _ = box.append(self).append(dots) }
    return box
  }
}
