import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        double[] prices = {1.5, 2.5, 3.5, 4.5, 5.5};
        int n, prod, am;
        double price = 0;
        Scanner scan = new Scanner(System.in);

        n = scan.nextInt();

        for (int i = 0; i < n ; i++) {
            prod = scan.nextInt();
            am = scan.nextInt();
//            System.out.println("product" + prod + "amount" + am);
            price += am * prices[(prod-1001)];
        }
        System.out.format("%.2f%n",price);
    }
}
