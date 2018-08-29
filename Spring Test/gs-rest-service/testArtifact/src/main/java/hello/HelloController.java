package hello;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.concurrent.atomic.AtomicInteger;

@RestController
public class HelloController {

	HashMap<Integer, String> userbase;

	public HelloController(){
		userbase = new HashMap<>();
	}

	@RequestMapping("/")
	public String index() {
		return "Greetings from Spring Boot!";
	}

	@RequestMapping("/hi")
	public String hi(@RequestParam(value = "user", defaultValue = "anonimous user") String user,
	                 @RequestParam(value = "id") int id) {
		if(userbase.containsKey(id)) return (userbase.get(id).equals(user)) ? String.format("Hello %s", user) : "Invalid user ID combination";
		userbase.put(id, user);
		return "Hello new user " + user + ", your ID is: " + id;
	}
}