import java.util.*;

class Student {
    String name;
    int marks;

    Student(String name, int marks) {
        this.name = name;
        this.marks = marks;
    }

    public int getMarks() { 
        return marks;
    }

    public String getName() {
        return name;
    }
}

class Heap {
    Student[] array;
    int size;
    Student[] buffer;
    int[] ascending;

    Heap(Student[] array, int size) {
        this.array = array;
        this.size = size;
    }

    public void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < this.size && this.array[left].getMarks() > this.array[largest].getMarks()) {
            largest = left;
        }
        if (right < this.size && this.array[right].getMarks() > this.array[largest].getMarks()) {
            largest = right;
        }
        if (largest != i) {
            Student temp = this.array[i];
            this.array[i] = this.array[largest];
            this.array[largest] = temp;
            heapify(largest);
        }
    }

    public void buildHeap() {
        for (int i = this.size / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
        this.buffer = Arrays.copyOf(this.array, this.size);

    }

    public void nextTopper() {
        if (this.size > 0) {
            System.out.println(
                    "The Next Topper is : " + this.array[0].getName() + " with marks " + this.array[0].getMarks());
            this.array[0] = this.array[this.size - 1];
            this.size -= 1;
            buildHeap();
        } else {
            System.out.println("No Students Remaining");
        }
    }

    public void ascendingOrder() {
        Stack<Student> stack = new Stack<>();
        int originalSize = this.size;
        Student[] temp = Arrays.copyOf(this.array, this.array.length);
        this.ascending = new int[originalSize];
        buildHeap();
        for (int i = 0; i < originalSize; i++) {
            if (this.size > 0) {
                stack.push(this.array[0]);
                this.array[0] = this.array[this.size - 1];
                this.size--;
                heapify(0);
            }
        }
        this.array = temp;
        this.size = temp.length;
        int index = 0;
        while (!stack.isEmpty()) {
            Student student = stack.pop();
            System.out.println(student.getName() + " : " + student.getMarks());
            ascending[index++] = student.getMarks();
        }
        System.out.println("Ascending marks array: " + Arrays.toString(ascending));
    }

    public void print() {
        for (int i = 0; i < this.size; i++) {
            System.out.print(this.array[i].getMarks() + " ");
        }
    }
}

public class ASS9 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the Number of Students : ");
        int size = sc.nextInt();
        Student[] students = new Student[size];
        for (int i = 0; i < size; i++) {
            sc.nextLine(); // Consume newline
            System.out.print("Enter Name for Student " + (i + 1) + " : ");
            String name = sc.nextLine();
            System.out.print("Enter Marks for Student " + (i + 1) + " : ");
            int marks = sc.nextInt();
            students[i] = new Student(name, marks);
        }
        Heap H = new Heap(students, size);
        int choice;
        do {
            System.out.println("\nEnter the Operation to be performed:");
            System.out.println("1. Next Topper");
            System.out.println("2. Build Heapify");
            System.out.println("3. Ascending Order");
            System.out.println("4. Print Array");
            System.out.println("0. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            switch (choice) {
                case 1:
                    H.nextTopper();
                    break;
                case 2:
                    H.buildHeap();
                    break;
                case 3:
                    H.ascendingOrder();
                    break;
                case 4:
                    H.print();
                    break;
                case 0:
                    System.out.println("ENDED");
                    break;
                default:
                    System.out.println("Invalid choice. Please enter a valid option.");
            }
        } while (choice != 0);
        sc.close();
    }
}
