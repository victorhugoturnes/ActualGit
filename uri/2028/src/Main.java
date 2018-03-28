import java.util.Scanner;

public class Main{
    public static void main(String[] args)  {
        type num = new type();
        Scanner scan = new Scanner(System.in);

        for (int loop = 1; scan.hasNext(); loop++) {
            num.get();
            System.out.print("Caso "+ loop + ": "+ num.howMany() +" numero" + (num.howMany()>1 ? "s\n" : "\n"));
            num.print();
        }
    }
    static class type{
        int num;
        Scanner scan = new Scanner(System.in);

        void get(){
            num = scan.nextInt();
        }

        int howMany(){
            return (int) (1+(num+1)*num/2.0);
        }

        void printRec(int n) {
            if(n>0)this.printRec(n-1);

            System.out.printf("%d ", n);

            for (int i = 0; i < n-1 ; i++) {
                System.out.printf("%d ", n);
            }
        }

        void print(){
            this.printRec(num);
        }

    }
}