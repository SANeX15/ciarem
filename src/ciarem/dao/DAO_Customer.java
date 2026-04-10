package ciarem.dao;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

import ciarem.mdl.Mdl_Customer;

public class DAO_Customer {
	private final String insertQuery = "INSERT INTO customers (id,NAME,PHONE,DOB) VALUES (?,?,?,?);";
	private final String selectQuery = "SELECT * FROM customers;";
	
	public List<Mdl_Customer> read(){
		List<Mdl_Customer> list = new ArrayList<>();
		
		try(Connection conn = DBHelper.getConnection();
				PreparedStatement ps = conn.prepareStatement(selectQuery);
				ResultSet rs = ps.executeQuery()){
			while (rs.next()) {
				Mdl_Customer c = new Mdl_Customer(
					rs.getString("id"),
					rs.getString("NAME"),
					rs.getString("PHONE"),
					LocalDate.parse(rs.getString("DOB"))
				);
				list.add(c);
			}
		}
		catch(Exception e) {
			System.out.println("Select Failed");
		}
		return list;
	}
	
	public boolean create(Mdl_Customer cus) {
		try(Connection conn = DBHelper.getConnection();
			PreparedStatement ps = conn.prepareStatement(insertQuery)){
			
			ps.setString(1, cus.getID());
			ps.setString(2, cus.getName());
			ps.setString(3, cus.getPhone());
			ps.setString(4, cus.getDob().toString());
			
			return ps.executeUpdate() > 0;
		}
		catch(Exception e) {
			return false;
		}
	}
}
