package Structures;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Set;

public class Automata {

	State                  starter;
	HashMap<String, State> nodes;
	ArrayList<String>      alphabet;
	ArrayList<String>      states;

	public Automata() {
		nodes = new HashMap<>();
		alphabet = new ArrayList<>();
		states = new ArrayList<>();
	}

	public void printGrammar() {
		HashMap<String, Character> conversion = new HashMap<>();
		for (int i = 0; i < states.size(); i++) {
			conversion.put(states.get(i), (char) ('A' + i - 1));
		}
		System.out.print("S -> ");
		State cur = nodes.get(states.get(0));
		cur.getKeys().stream().forEach(key -> System.out.print(key + conversion.get(cur.keyValue(key))));
		System.out.println();
		for (int i = 1; i < states.size(); i++) {
			System.out.print((char) ('A' + i - 1) + " -> ");
			State                      state  = nodes.get(states.get(i));
			Set<String>                keys   = state.getKeys();
			HashMap<Character, String> buffer = new HashMap<>();
			for (String key : keys) {
				buffer.put(conversion.get(state.keyValue(key)), key);
			}
			buffer.keySet().stream().sorted().forEach(key -> System.out.print(buffer.get(key) + key + " "));

			if (state.isFinal) {
				System.out.print(" @");
			}
			System.out.println();
		}
	}


	public void analyze(String chain) {
		State cur = starter;
		while (chain.length() > 0 && cur != null) {
			System.out.println("[" + cur.getName() + "]" + chain);
			cur = nodes.get(cur.get(chain.charAt(0)));
			chain = chain.substring(1);
		}
		if (cur == null) {
			System.out.println("REJEITA");
		} else if (!cur.isFinal) {
			System.out.println("[" + cur.getName() + "]" + "\nREJEITA");
		} else {
			System.out.println("[" + cur.getName() + "]" + "\nACEITA");
		}
	}

	public void addStates(Collection<String> states) {
		this.states.addAll(states);
		this.states.forEach(str -> nodes.put(str, new State(str)));
	}

	public void defineStarter(String starter) {
		this.starter = nodes.get(starter);
	}

	public void defineFinals(Collection<String> finals) {
		finals.forEach(str -> nodes.get(str).setFinal());
	}

	public void addAlphabet(Collection<String> alphabet) {
		this.alphabet.addAll(alphabet);
	}

	public void addTransitions(String[] transition) {
		if (nodes.containsKey(transition[0])) {
			nodes.get(transition[0]).addTransition(transition[1], transition[2]);
		}
	}

	@Override
	public String toString() {
		return "Starter:: (" + starter + ") alphabet:: " + alphabet + " states:: " + states;
	}
}
