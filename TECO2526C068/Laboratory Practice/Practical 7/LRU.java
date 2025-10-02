import java.util.*;

public class LRU {
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

        List<Integer> list = new ArrayList<>();
        Set<Integer> set = new HashSet<>();
        int faults = 0;

        for (int p : pages) {
            if (!set.contains(p)) {
                if (set.size() < frames) {
                    set.add(p);
                    list.add(p);
                } else {
                    int lru = list.remove(0);
                    set.remove(lru);
                    set.add(p);
                    list.add(p);
                }
                faults++;
            } else {
                list.remove((Integer) p);
                list.add(p);
            }
            System.out.println("Page: " + p + " -> Frames: " + list);
        }

        System.out.println("Total Page Faults (LRU): " + faults);
        sc.close();
    }
}

