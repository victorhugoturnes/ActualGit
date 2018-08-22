package Main;

import Algorithms.Loader;
import Structures.Automata;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		File                folder = new File(System.getProperty("user.dir") + "//inputs//");
		ArrayList<Automata> afd    = new ArrayList<>();
		for (File file : folder.listFiles()) {
			afd.add(Loader.load(file.getName()));
		}
		Scanner scan = new Scanner(System.in);
		System.out.println("Please input the chain");
		String chain = scan.nextLine();
		afd.forEach(k -> {
			k.analyze(chain);
			k.printGrammar();
			System.out.println("\n");
		});
	}
}
