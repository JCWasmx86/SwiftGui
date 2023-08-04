import CGTUI

public class CarouselIndicatorDots: NativeWidgetPeer {
  public init(carousel: Carousel) {
    super.init()
    self.nativePtr = gtui_create_carouselindicatordots(carousel.nativePtr)
  }
}
