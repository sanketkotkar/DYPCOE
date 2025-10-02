import java.util.concurrent.Semaphore;

class SharedData {
    int data = 0; // Shared resource
    int readerCount = 0; // Number of active readers

    // Semaphores
    Semaphore mutex = new Semaphore(1); // Protect readerCount
    Semaphore wrt = new Semaphore(1);   // Protect shared data (writers)
}

// Reader class
class Reader extends Thread {
    SharedData shared;
    int readerId;

    Reader(SharedData shared, int id) {
        this.shared = shared;
        this.readerId = id;
    }

    public void run() {
        try {
            while (true) {
                // Entry section
                shared.mutex.acquire();
                shared.readerCount++;
                if (shared.readerCount == 1)
                    shared.wrt.acquire(); // First reader locks writer
                shared.mutex.release();

                // Critical section
                System.out.println("Reader " + readerId + " is reading: " + shared.data);
                Thread.sleep(500); // Simulate reading time

                // Exit section
                shared.mutex.acquire();
                shared.readerCount--;
                if (shared.readerCount == 0)
                    shared.wrt.release(); // Last reader releases writer
                shared.mutex.release();

                Thread.sleep(500); // Simulate other work
            }
        } catch (InterruptedException e) {
            System.out.println("Reader interrupted");
        }
    }
}

// Writer class
class Writer extends Thread {
    SharedData shared;
    int writerId;

    Writer(SharedData shared, int id) {
        this.shared = shared;
        this.writerId = id;
    }

    public void run() {
        try {
            while (true) {
                shared.wrt.acquire(); // Only writer access
                shared.data += 1;     // Modify shared data
                System.out.println("Writer " + writerId + " is writing: " + shared.data);
                Thread.sleep(1000);   // Simulate writing time
                shared.wrt.release();

                Thread.sleep(500); // Simulate other work
            }
        } catch (InterruptedException e) {
            System.out.println("Writer interrupted");
        }
    }
}

// Main class
public class ReaderWriterProblem {
    public static void main(String[] args) {
        SharedData shared = new SharedData();

        // Create readers and writers
        Reader r1 = new Reader(shared, 1);
        Reader r2 = new Reader(shared, 2);
        Writer w1 = new Writer(shared, 1);
        Writer w2 = new Writer(shared, 2);

        // Start threads
        r1.start();
        r2.start();
        w1.start();
        w2.start();
    }
}

