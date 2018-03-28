import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String num;
        Scanner scan = new Scanner(System.in);
        StringBuilder builder;

        num = scan.next();

        builder = new StringBuilder(num);
        num = builder.reverse().toString();

        System.out.println(num);
    }
}



