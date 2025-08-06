import java.util.Scanner;

public class WorstFit{
	public static int maxBlock(int[] memory, int sizeReq){
	int maxIndex = -1;
	int maxSize = -1;
	
	for(int i=0; i<memory.length; i++){
		if(memory[i] > maxSize && memory[i] >= sizeReq){
			maxIndex = i;
			maxSize = memory[i];
		}
	}
	return maxIndex;
}


    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter number of processes: ");
        int numP = sc.nextInt();
        int arr[] = new int[numP];
        for(int i=0; i<numP; i++){
            System.out.println("Enter memory requirement of process " + (i+1)+": " );
            arr[i] = sc.nextInt();
        }
        
        
        System.out.println("Enter number of memory blocks: ");
        int numB = sc.nextInt();
        int memory[] = new int[numB];
        for(int i=0; i<numB; i++){
            System.out.println("Enter size of memory block " + (i+1)+": " );
            memory[i] = sc.nextInt();
        }
        
        System.out.println();
        System.out.println("Initial available memory blocks: ");
        for(int i=0; i<numB; i++){
            System.out.println(memory[i] + " ");
        }
        
        //allocating memory
        for(int i=0; i<numP; i++){
        	int index = maxBlock(memory, arr[i]);
        	if(index != -1){
        		memory[index] -= arr[i];
        		System.out.println("Memory allocation for Process P" + (i+1) + " is successful in memory block: " + (index+1));
        	}
        	else{
        		System.out.println("Memory allocation for Process P" + (i + 1 ) + " is unsuccessful ");
        	}
        }
        
        System.out.println();
        System.out.println("Fragmented memory blocks: ");
        for(int i=0; i<numB; i++){
            System.out.println(memory[i] + " ");
        }
       }
}
