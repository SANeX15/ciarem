package ciarem.mdl;

import java.time.LocalDate;

public class Mdl_Customer {
	private String id;
	private String name;
	private String phone;
	private LocalDate dob;
	
	public Mdl_Customer(String id, String name, String phone, LocalDate dob) {
		this.id = id;
		this.name = name;
		this.phone = phone;
		this.dob = dob;
	}
	
	public String getID() {return this.id;}
	public String getName() {return this.name;}
	public String getPhone() {return this.phone;}
	public LocalDate getDob() {return this.dob;}
}
