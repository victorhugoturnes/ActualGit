import java.util.Scanner;

public class Main{
    public static void main(String[] args)  {
        Scanner scan = new Scanner(System.in).useDelimiter("[^0-9]+");
        int hour, min;

        while(scan.hasNext()){
            hour = scan.nextInt();
            min = scan.nextInt();
            hour -= 6;
            min += hour*60-60;
            System.out.println("Atraso maximo: " + (hour > 0 ? min : 0));
        }
    }
}

