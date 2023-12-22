
import java.util.Arrays;
import java.util.Scanner;

class Node {

  int startTime;
  int finishTime;
}

public class activitySelection {

  public static void main(String[] args) {
    int n = 0;
    System.out.println("Please enter the number of jobs");
    Scanner sc = new Scanner(System.in);
    n = sc.nextInt();
    Node[] Arr = new Node[n];
    for (int i = 0; i < n; i++) {
      Arr[i] = new Node(); // Create a new Node object for each element
      System.out.println("Enter the details for job " + (i + 1));
      System.out.print("Start Time: ");
      int s = sc.nextInt();
      Arr[i].startTime = s;
      System.out.print("Finish Time: ");
      int f = sc.nextInt();
      Arr[i].finishTime = f;
    }

    // Call the sorting method after collecting input data
    Arrays.sort(Arr, (a, b) -> Integer.compare(a.finishTime, b.finishTime));
    // sorting(Arr);

    int i = 0;
    {
      for (int j = 1; j < Arr.length; j++) {
        if (Arr[j].startTime >= Arr[i].finishTime) {
          System.out.println(j + " ");
          i = j;
        }
      }
    }
  }

  public static void sorting(Node[] arr) {}
}
