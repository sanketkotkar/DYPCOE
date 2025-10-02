import java.util.*;

public class FIFO {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of frames: ");
        int frames = sc.nextInt();

        System.out.print("Enter number of pages: ");
        int n = sc.nextInt();
        int[] pages = new int[n];

        System.out.println("Enter page reference string:");
        for (int i = 0; i < n; i++) {
            pages[i] = sc.nextInt();
        }

        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> set = new HashSet<>();
        int faults = 0;

        for (int p : pages) {
            if (!set.contains(p)) {
                if (set.size() < frames) {
                    set.add(p);
                    queue.add(p);
                } else {
                    int removed = queue.poll();
                    set.remove(removed);
                    set.add(p);
                    queue.add(p);
                }
                faults++;
            }
            System.out.println("Page: " + p + " -> Frames: " + set);
        }

        System.out.println("Total Page Faults (FIFO): " + faults);
        sc.close();
    }
}

