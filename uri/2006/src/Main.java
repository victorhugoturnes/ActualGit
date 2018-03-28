import java.util.Scanner;

public class Main{
    public static void main(String[] args)  {
        Scanner scan = new Scanner(System.in);
        int cur, count = 0, n;

        n = scan.nextInt();

        for (int i = 0; i < 5 ; i++) {
            cur = scan.nextInt();
            if(cur == n) count++;
        }
        System.out.println(count);
    }
}

