
package EXCERCISE;
    import java.util.Scanner;
public class exercise3 {
    public static void main(String[] args) {
        Scanner number = new Scanner(System.in);
        System.out.print("nhap a: ");
        int a = number.nextInt();
        Scanner number2 = new Scanner(System.in);
        System.out.print("nhap b: ");
        int b = number2.nextInt();
        System.out.println("Tong: " + (a+b) );
    }
}
