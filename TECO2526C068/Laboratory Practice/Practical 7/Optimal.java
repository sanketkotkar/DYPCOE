import java.util.*;

public class Optimal {
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

        List<Integer> memory = new ArrayList<>();
        int faults = 0;

        for (int i = 0; i < pages.length; i++) {
            int p = pages[i];

            if (!memory.contains(p)) {
                if (memory.size() < frames) {
                    memory.add(p);
                } else {
                    int farthest = -1, indexToReplace = -1;
                    for (int j = 0; j < memory.size(); j++) {
                        int page = memory.get(j);
                        int nextUse = Integer.MAX_VALUE;
                        for (int k = i + 1; k < pages.length; k++) {
                            if (pages[k] == page) {
                                nextUse = k;
                                break;
                            }
                        }
                        if (nextUse > farthest) {
                            farthest = nextUse;
                            indexToReplace = j;
                        }
                    }
                    memory.set(indexToReplace, p);
                }
                faults++;
            }
            System.out.println("Page: " + p + " -> Frames: " + memory);
        }

        System.out.println("Total Page Faults (Optimal): " + faults);
        sc.close();
    }
}

