import CGTUI

public class Carousel: NativeWidgetPeer {
  public override init() {
    super.init()
    self.nativePtr = gtui_create_carousel()
  }

  public func append(_ widget: NativeWidgetPeer) -> Carousel {
    gtui_carousel_append(self.nativePtr, widget.nativePtr)
    return self
  }

  public func prepend(_ widget: NativeWidgetPeer) -> Carousel {
    gtui_carousel_prepend(self.nativePtr, widget.nativePtr)
    return self
  }

  public func addIndicatorDots(top: Bool = false) -> Box {
    let box = Box(horizontal: false)
    let dots = CarouselIndicatorDots(carousel: self)
    if top { _ = box.append(dots).append(self) } else { _ = box.append(self).append(dots) }
    return box
  }
}
