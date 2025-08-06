import java.util.Scanner;

public class NextFit {
	static void nextFit(int blockSize[], int m, int processSize[], int n) {
		int[] allocation = new int[n];
		for (int i = 0; i < n; i++) {
			allocation[i] = -1;
		}
		int j = 0;
		for (int i = 0; i < n; i++) {
		int count = 0;
		while (count < m) {
			if (blockSize[j] >= processSize[i]) {
				allocation[i] = j;
				blockSize[j] -= processSize[i];
				break;
			}
			j = (j + 1) % m;
			count++;
		}
          }
 		System.out.println("Process No.\tProcess Size\tBlock No.");
		for (int i = 0; i < n; i++) {
			System.out.print("   " + (i + 1) + "\t\t" + processSize[i] + "\t\t");
			if (allocation[i] != -1){
				System.out.println(allocation[i] + 1);
			}
			else{
				System.out.println("Not Allocated");
			}
		}
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		System.out.print("Enter number of memory blocks: ");
		int m = sc.nextInt();
		int[] blockSize = new int[m];
		System.out.println("Enter size of each memory block:");
		for (int i = 0; i < m; i++){
			blockSize[i] = sc.nextInt();
		}
		System.out.print("Enter number of processes: ");
		int n = sc.nextInt();
		int[] processSize = new int[n];
		System.out.println("Enter size of each process:");
		for (int i = 0; i < n; i++){
			processSize[i] = sc.nextInt();
		}
		nextFit(blockSize, m, processSize, n);
	}
}
