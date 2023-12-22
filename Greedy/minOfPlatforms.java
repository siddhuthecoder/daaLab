class Event {

  float startTime;
  float endTime;

  public Event(float startTime, float endTime) {
    this.startTime = startTime;
    this.endTime = endTime;
  }
}

public class minOfPlatforms {

  public static void main(String[] args) {
    float[] startTimes = { 9.00f, 9.40f, 9.50f, 11.00f, 15.00f, 18.00f };
    float[] endTimes = { 9.10f, 12.00f, 11.20f, 11.30f, 19.00f, 20.00f };

    Event[] events = new Event[startTimes.length];

    for (int i = 0; i < startTimes.length; i++) {
      events[i] = new Event(startTimes[i], endTimes[i]);
    }
    for (Event event : events) {
      System.out.println(
        "Start Time: " + event.startTime + ", End Time: " + event.endTime
      );
    }
    for (int i = 0; i < events.length; i++) {
      int noOFplatforms = 1;
      for (int j = 0; j < events.length; j++) {
        if (i != j) {
          // if(events[j].startTime)
        }
      }
    }
  }
}
