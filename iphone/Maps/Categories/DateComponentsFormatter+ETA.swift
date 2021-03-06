extension DateComponentsFormatter {

  static func etaString(from ti: TimeInterval) -> String? {
    let formatter = DateComponentsFormatter()
    formatter.allowedUnits = [.minute, .hour, .day]
    formatter.maximumUnitCount = 2
    formatter.unitsStyle = .abbreviated
    formatter.zeroFormattingBehavior = .dropAll
    return formatter.string(from: ti)
  }
}
