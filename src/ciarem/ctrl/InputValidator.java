package ciarem.ctrl;

import java.time.LocalDate;

public class InputValidator {
	public static boolean isAadharValid(String id) {
		if(id == null || id.trim().isEmpty()) return false;
		if(!id.matches("\\d{12}")) return false;
		return true;
	}
	
	public static boolean isNameValid(String name) {
		if(name == null || name.trim().isEmpty()) return false;
		if(!name.matches("[a-zA-Z ]+")) return false;
		return true;
	}
	
	public static boolean isPhoneValid(String phone) {
		if(phone == null || phone.trim().isEmpty()) return false;
		if(!phone.matches("\\d{10}")) return false;
		return true;
	}
	
	public static boolean isDobValid(LocalDate dob) {
		if(dob == null) return false;
		if (dob.isAfter(LocalDate.now())) return false;
		return true;
	}
}
