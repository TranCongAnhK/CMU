
package EXCERCISE;
    import java.util.Scanner;
public class excercise {
    public static void main(String[] args) {
        Scanner keyboard = new Scanner(System.in);
        System.out.print("Nhap ten: ");
        String name = keyboard.nextLine();
        Scanner number = new Scanner(System.in);
        System.out.print("Nhap tuoi: ");
        String so = number.nextLine();
        System.out.println(name + so);
    }
}
