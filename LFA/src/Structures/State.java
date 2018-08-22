package Structures;

import java.util.HashMap;
import java.util.Set;

public class State {
	private String                  name;
	private HashMap<String, String> transition;
	boolean                 isFinal;

	public State(String name) {
		this.transition = new HashMap<>();
		this.isFinal = false;
		this.name = name;
	}

	public void setFinal() {
		isFinal = true;
	}

	/**
	 * @param key
	 * @param value
	 */
	public void addTransition(String key, String value) {
		transition.put(key, value);
	}

	public Set<String> getKeys() {
		return transition.keySet();
	}


	public String keyValue(String key) {
		return transition.get(key);
	}

	@Override
	public String toString() {
		return transition.values().toString();
	}

	public String getName() {
		return name;
	}

	public String get(char c) {
		return transition.get(c + "");
	}
}
