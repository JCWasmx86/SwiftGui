public enum Transition: Int {
  case none
  case crossfade
  case slideRight, slideLeft, slideUp, slideDown, slideLeftRight, slideUpDown
  case coverUp, coverDown, coverLeft, coverRight
  case uncoverUp, uncoverDown, uncoverLeft, uncoverRight
  case coverUpDown, coverDownUp, coverLeftRight, coverRightLeft
  case rotateLeft, rotateRight, rotateLeftRight
}
