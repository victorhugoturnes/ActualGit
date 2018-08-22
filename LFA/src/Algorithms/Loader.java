package Algorithms;

import Structures.Automata;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Loader {
	public static Automata load(String file) {
		String   directory = System.getProperty("user.dir") + "//inputs//";
		Automata automata  = new Automata();
		try (BufferedReader reader = new BufferedReader(new FileReader(directory + file))) {

			String line = reader.readLine();
			automata.addAlphabet(parseMultiple(line));

			line = reader.readLine();
			automata.addStates(parseMultiple(line));

			line = reader.readLine();
			automata.defineStarter(parseStarter(line));

			line = reader.readLine();
			automata.defineFinals(parseMultiple(line));

			line = reader.readLine();
			while (line != null) {
				automata.addTransitions(parseTransitions(line));
				line = reader.readLine();
			}
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
		return automata;
	}

	private static Collection<String> parseMultiple(String line) {
		ArrayList<String> alpha = new ArrayList<>();
		Matcher           match = Pattern.compile("(?<=[{,])[^,]*(?=[},])").matcher(line);
		while (match.find()) {
			alpha.add(match.group());
		}
		return alpha;
	}

	/**
	 * @param line
	 * @return
	 */
	private static String parseStarter(String line) {
		Matcher match = Pattern.compile("(?<==)(.*)").matcher(line);
		match.find();
		return match.group();
	}


	private static String[] parseTransitions(String line) {
		String[] transition = new String[3];
		Matcher  source     = Pattern.compile("(?<=\\()(.*)(?=,)").matcher(line);
		if (source.find()) {
			transition[0] = source.group();
			Matcher command = Pattern.compile("(?<=,)(.*)(?=\\))").matcher(line);
			if (command.find()) {
				transition[1] = command.group();
				Matcher destiny = Pattern.compile("(?<== )(.*)").matcher(line);
				if (destiny.find()) {
					transition[2] = destiny.group();
					return transition;
				}
			}
		}

		return null;
	}
}
